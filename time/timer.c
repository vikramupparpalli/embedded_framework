#include <stdbool.h>
#include <stddef.h>
#include "timer.h"

#include "interfaces/i_timesource.h"
#include "linked_list.h"
#include "uassert.h"
#include "utilities.h"

#define MAX_TICKS ((timer_ticks_t)(-1))

typedef struct
{
   timer_module_t *module;
   timer_ticks_t expirationTicks;
   size_t index;
} find_insertion_index_context_t;

static bool ForEach_FindInsertionIndex(linked_list_node_t *node, void *_context, const size_t index)
{
   REINTERPRET(context, _context, find_insertion_index_context_t *);
   REINTERPRET(timer, node, timer_t *);

   if(timer->paused || timer->expired)
   {
      return true;
   }
   else
   {
      timer_ticks_t remainingTicksForCurrentTimer = timer->ticks.expiration - context->module->lastTicks;
      timer_ticks_t remainingTicksForTimerToInsert = context->expirationTicks - context->module->lastTicks;

      if(remainingTicksForCurrentTimer > remainingTicksForTimerToInsert)
      {
         context->index = index;
         return false;
      }

      return true;
   }
}

static void AddTimer(timer_module_t *module, timer_t *timer)
{
   find_insertion_index_context_t context;
   context.module = module;
   context.expirationTicks = timer->ticks.expiration;
   context.index = linked_list_count(&module->timers);
   linked_list_for_each(&module->timers, ForEach_FindInsertionIndex, &context);

   linked_list_insert(&module->timers, &timer->node, context.index);
}

static void RemoveTimer(timer_module_t *module, timer_t *timer)
{
   linked_list_remove(&module->timers, &timer->node);
}

void timer_module_stop(timer_module_t *module, timer_t *timer)
{
   RemoveTimer(module, timer);
}

static timer_ticks_t PendingTicks(timer_module_t *module)
{
   timesource_tick_count_t newTickCount = timesource_get_ticks(module->timeSource);
   return (timer_ticks_t)((timesource_tick_count_t)(newTickCount - module->lastTimeSourceTickCount));
}

static void StartTimer(timer_module_t *module, timer_t *timer, const timer_ticks_t ticks, timer_callback_t callback, void *context)
{
   timer_ticks_t timerDuration = TRUNCATE_UNSIGNED_ADDITION(ticks, PendingTicks(module), MAX_TICKS);

   timer_module_stop(module, timer);

   timer->startTicks = ticks;
   timer->ticks.expiration = module->lastTicks + timerDuration;
   timer->context = context;
   timer->callback = callback;
   timer->paused = false;
   timer->expired = false;

   AddTimer(module, timer);
}

void timer_module_start_oneshot(timer_module_t *module, timer_t *timer, const timer_ticks_t ticks, timer_callback_t callback, void *context)
{
   uassert(callback);

   timer->autoReload = false;
   StartTimer(module, timer, ticks, callback, context);
}

void timer_module_start_periodic(timer_module_t *module, timer_t *timer, const timer_ticks_t ticks, timer_callback_t callback, void *context)
{
   uassert(callback);

   timer->autoReload = true;
   StartTimer(module, timer, ticks, callback, context);
}

bool timer_module_is_running(timer_module_t *module, timer_t *timer)
{
   return linked_list_contains(&module->timers, (const linked_list_node_t *)timer);
}

void timer_module_pause(timer_module_t *module, timer_t *timer)
{
   if(timer_module_is_running(module, timer))
   {
      timer->ticks.pause = timer_module_remaining_ticks(module, timer);
      timer->paused = true;
   }
}

void timer_module_resume(timer_module_t *module, timer_t *timer)
{
   if(timer_module_is_paused(module, timer))
   {
      timer_ticks_t remainingTicks = TRUNCATE_UNSIGNED_ADDITION(timer->ticks.pause, PendingTicks(module), MAX_TICKS);
      timer->paused = false;

      RemoveTimer(module, timer);
      timer->ticks.expiration = module->lastTicks + remainingTicks;
      AddTimer(module, timer);
   }
}

bool timer_module_is_paused(timer_module_t *module, timer_t *timer)
{
   if(timer_module_is_running(module, timer))
   {
      return timer->paused;
   }
   else
   {
      return false;
   }
}

timer_ticks_t timer_module_start_ticks(timer_module_t *module, timer_t *timer)
{
   if(timer_module_is_running(module, timer))
   {
      return timer->startTicks;
   }
   else
   {
      return 0;
   }
}

timer_ticks_t timer_module_remaining_ticks(timer_module_t *module, timer_t *timer)
{
   if(timer_module_is_running(module, timer))
   {
      if(timer_module_is_paused(module, timer))
      {
         return timer->ticks.pause;
      }
      else
      {
         timer_ticks_t expiration = timer->ticks.expiration;
         timer_ticks_t lastTicks = module->lastTicks;
         timer_ticks_t pending = PendingTicks(module);
         timer_ticks_t remainingWithoutPending = expiration - lastTicks;
         return TRUNCATE_UNSIGNED_SUBTRACTION(remainingWithoutPending, pending);
      }
   }
   else
   {
      return 0;
   }
}

timer_ticks_t timer_module_ticks_since_last_started(timer_module_t *module, timer_t *timer)
{
   uassert(!timer_module_is_paused(module, timer));
   return module->lastTicks - (timer->ticks.expiration - timer->startTicks) + PendingTicks(module);
}

timer_ticks_t timer_module_elapsed_ticks(timer_module_t *module, timer_t *timer)
{
   if(timer_module_is_running(module, timer))
   {
      return timer->startTicks - timer_module_remaining_ticks(module, timer);
   }
   else
   {
      return 0;
   }
}

void timer_module_init(timer_module_t *module, i_timesource_t *timeSource)
{
   module->timeSource = timeSource;
   module->lastTimeSourceTickCount = timesource_get_ticks(timeSource);
   linked_list_init(&module->timers);
}

typedef struct
{
   timer_module_t *module;
   timer_ticks_t newTicks;
   timer_ticks_t lastTicks;
} UpdateExpiredContext_t;

static bool ForEach_UpdateExpired(linked_list_node_t *node, void *_context, const size_t index)
{
   REINTERPRET(context, _context, UpdateExpiredContext_t *);
   REINTERPRET(timer, node, timer_t *);

   IGNORE_ARG(index);

   if(!timer->paused)
   {
      timer_ticks_t elapsedTicks = (context->newTicks - context->lastTicks);
      timer_ticks_t remainingTicksForTimer = (timer->ticks.expiration - context->lastTicks);

      if(elapsedTicks >= remainingTicksForTimer)
      {
         timer->expired = true;
      }
   }

   return (bool)(timer->expired || timer->paused);
}

static void ExecuteTimer(timer_module_t *module, timer_t *timer)
{
   if(!timer->autoReload)
   {
      timer_module_stop(module, timer);
   }

   timer->callback(timer->context);

   // If the timer was stopped in the callback we should not restart the timer
   if(timer_module_is_running(module, timer) && timer->autoReload)
   {
      RemoveTimer(module, timer);
      timer->expired = false;
      timer->ticks.expiration = module->lastTicks + timer->startTicks;
      AddTimer(module, timer);
   }
}

typedef struct
{
   timer_module_t *module;
   bool executedTimer;
} ExecuteContext_t;

static bool ForEach_Execute(linked_list_node_t *node, void *_context, const size_t index)
{
   REINTERPRET(timer, node, timer_t *);
   REINTERPRET(context, _context, ExecuteContext_t *);

   IGNORE_ARG(index);

   if(!timer->paused && timer->expired)
   {
      ExecuteTimer(context->module, timer);
      context->executedTimer = true;
   }

   return (bool)!context->executedTimer;
}

bool timer_module_run(timer_module_t *module)
{
   {
      timesource_tick_count_t newTickCount = timesource_get_ticks(module->timeSource);
      timer_ticks_t deltaTicks = (timer_ticks_t)((timesource_tick_count_t)(newTickCount - module->lastTimeSourceTickCount));
      timer_ticks_t newTicks = module->lastTicks + deltaTicks;

      UpdateExpiredContext_t context;
      context.newTicks = newTicks;
      context.module = module;
      context.lastTicks = module->lastTicks;

      module->lastTicks = newTicks;
      module->lastTimeSourceTickCount = newTickCount;

      linked_list_for_each(&module->timers, ForEach_UpdateExpired, &context);
   }

   {
      ExecuteContext_t context;
      context.module = module;
      context.executedTimer = false;

      linked_list_for_each(&module->timers, ForEach_Execute, &context);

      return context.executedTimer;
   }
}

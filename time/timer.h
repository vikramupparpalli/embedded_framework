#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include "interfaces/i_timesource.h"
#include "linked_list.h"

/*!
 * Timer duration/tick count.
 */
typedef uint32_t timer_ticks_t;

/*!
 * Callback invoked when a timer expires.
 * @param context Callback context.
 */
typedef void (*timer_callback_t)(void *context);

/*!
 * Timer definition.  Struct members should be considered private.
 */
typedef struct
{
   linked_list_node_t node;
   timer_callback_t callback;
   void *context;
   timer_ticks_t startTicks;
   union
   {
      timer_ticks_t expiration;
      timer_ticks_t pause;
   } ticks;
   bool autoReload :1;
   bool paused :1;
   bool expired :1;
} timer_t;

typedef struct
{
   i_timesource_t *timeSource;
   linked_list_t timers;
   timer_ticks_t lastTicks;
   timesource_tick_count_t lastTimeSourceTickCount;
} timer_module_t;

void timer_module_init(timer_module_t *module, i_timesource_t *timeSource);

void timer_module_start_oneshot(timer_module_t *module, timer_t *timer, const timer_ticks_t ticks, timer_callback_t callback, void *context);

void timer_module_start_periodic(timer_module_t *module, timer_t *timer, const timer_ticks_t ticks, timer_callback_t callback, void *context);

void timer_module_stop(timer_module_t *module, timer_t *timer);

bool timer_module_is_running(timer_module_t *module, timer_t *timer);
void timer_module_pause(timer_module_t *module, timer_t *timer);

void timer_module_resume(timer_module_t *module, timer_t *timer);

bool timer_module_is_paused(timer_module_t *module, timer_t *timer);

timer_ticks_t timer_module_start_ticks(timer_module_t *module, timer_t *timer);

timer_ticks_t timer_module_remaining_ticks(timer_module_t *module, timer_t *timer);

timer_ticks_t timer_module_elapsed_ticks(timer_module_t *module, timer_t *timer);

timer_ticks_t timer_module_ticks_since_last_started(timer_module_t *module, timer_t *timer);

bool timer_module_run(timer_module_t *module);

#endif

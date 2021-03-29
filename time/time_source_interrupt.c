#include "time_source_interrupt.h"
#include "event_subscription.h"
#include "uassert.h"
#include "utilities.h"

static timesource_tick_count_t GetTicks(i_timesource_t *_instance)
{
   REINTERPRET(instance, _instance, TimeSource_Interrupt_t *);

   timesource_tick_count_t last;
   timesource_tick_count_t current;

   current = instance->_private.tickCount;

   // Note: this provides interrupt-safety and means that we do not ever have to disable interrupts.
   // Keep reading the tick count until it reads the same two times in a row so that we know the value
   // is correct.
   // Unless the interrupt is coming so fast that the few cycles of the loop don't guarantee that we
   // can do two reads without the ISR coming this will work.  If the interrupt comes so fast that we
   // can't execute a few cycles in between invocations then we have a bigger problem.
   do
   {
      last = current;
      current = instance->_private.tickCount;
   } while(last != current);

   return current;
}

static const i_timesource_api_t api =
   { GetTicks };

static void InterruptCallback(void *_instance, const void *args)
{
   REINTERPRET(instance, _instance, TimeSource_Interrupt_t *);
   IGNORE_ARG(args);
   instance->_private.tickCount++;
}

void TimeSource_Interrupt_Init(TimeSource_Interrupt_t *instance, i_interrupt_t *interrupt)
{
   instance->interface.api = &api;
   instance->_private.tickCount = 0;

   event_subscription_init(&instance->_private.interruptEventSubscription, instance, InterruptCallback);
   event_subscribe(interrupt, &instance->_private.interruptEventSubscription);
}

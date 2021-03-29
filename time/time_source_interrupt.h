#ifndef TIMESOURCE_INTERRUPT_H
#define TIMESOURCE_INTERRUPT_H

#include "i_interrupt.h"
#include "interfaces/i_timesource.h"

typedef struct
{
   i_timesource_t interface;

   struct
   {
      timesource_tick_count_t tickCount;
      event_subscription_t interruptEventSubscription;
   } _private;
} TimeSource_Interrupt_t;

/*!
 * Initialize an interrupt-driven time source.  The time source tick count will be zero after init.
 * @param instance The time source.
 * @param interrupt The interrupt to use as the 'tick'.
 */
void TimeSource_Interrupt_Init(TimeSource_Interrupt_t *instance, i_interrupt_t *interrupt);

#endif

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
} timesource_interrupt_t;

/*!
 * Initialize an interrupt-driven time source.  The time source tick count will be zero after init.
 * @param instance The time source.
 * @param interrupt The interrupt to use as the 'tick'.
 */
void timesource_interrupt_init(timesource_interrupt_t *instance, i_interrupt_t *interrupt);

#endif

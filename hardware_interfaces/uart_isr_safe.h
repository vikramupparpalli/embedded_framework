/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#ifndef UART_ISR_SAFE_H
#define UART_ISR_SAFE_H

#include <stdbool.h>
#include <stddef.h>
#include "ringbuffer.h"
#include "i_uart.h"
#include "event_synchronous.h"

typedef struct
{
   i_uart_t interface;

   struct
   {
      i_uart_t *inner;
      ringbuffer_t ringBuffer;
      event_synchronous_t OnReceive;
      event_synchronous_t OnTransmit;
      event_synchronous_t OnError;
      event_subscription_t onReceiveSubscription;
      event_subscription_t onTransmitSubscription;
      event_subscription_t onErrorSubscription;
      bool errorOccurred :1;
      bool transmitOccurred :1;
   } _private;
} uart_isr_safe_t;

void uart_isr_safe_init(uart_isr_safe_t *instance, i_uart_t *inner, void *queueBuffer, size_t queueBufferSize);

void uart_isr_safe_run(uart_isr_safe_t *instance);

#endif

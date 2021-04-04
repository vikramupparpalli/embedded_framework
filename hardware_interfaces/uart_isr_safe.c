/*!
 * @file
 * @brief Implementation of an ISR-safe UART wrapper.  Uses a ring buffer queue received bytes and
 * then consumes from the queue in the background.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "uart_isr_safe.h"
#include "uassert.h"
#include "utilities.h"

static void receive_callback(void *context, const void *args)
{
   REINTERPRET(instance, context, uart_isr_safe_t *);
   REINTERPRET(onReceiveArgs, args, const uart_on_receive_args_t *);

   // Cannot allow the ring buffer to get full or ISR safety cannot be guaranteed
   if(ringbuffer_count(&instance->_private.ringBuffer) < (ringbuffer_capacity(&instance->_private.ringBuffer) - 1))
   {
      ringbuffer_add(&instance->_private.ringBuffer, (const void *)&onReceiveArgs->byte);
   }
}

static void transmit_callback(void *context, const void *args)
{
   REINTERPRET(instance, context, uart_isr_safe_t *);
   instance->_private.transmitOccurred = true;
   IGNORE_ARG(args);
}

static void error_callback(void *context, const void *args)
{
   REINTERPRET(instance, context, uart_isr_safe_t *);
   instance->_private.errorOccurred = true;
   IGNORE_ARG(args);
}

static void send(i_uart_t *_instance, const uint8_t byte)
{
   REINTERPRET(instance, _instance, uart_isr_safe_t *);
   uart_send(instance->_private.inner, byte);
}

static i_event_t * get_on_receive_event(i_uart_t *_instance)
{
   REINTERPRET(instance, _instance, uart_isr_safe_t *);
   return &instance->_private.OnReceive.interface;
}

static i_event_t * get_on_transmit_event(i_uart_t *_instance)
{
   REINTERPRET(instance, _instance, uart_isr_safe_t *);
   return &instance->_private.OnTransmit.interface;
}

static i_event_t * get_on_error_event(i_uart_t *_instance)
{
   REINTERPRET(instance, _instance, uart_isr_safe_t *);
   return &instance->_private.OnError.interface;
}

static const i_uart_api_t api =
   { send, get_on_receive_event, get_on_transmit_event, get_on_error_event };

void uart_isr_safe_init(uart_isr_safe_t *instance, i_uart_t *inner, void *queueBuffer, size_t queueBufferSize)
{
   uassert(queueBuffer);

   instance->interface.api = &api;
   instance->_private.inner = inner;

   event_synchronous_init(&instance->_private.OnReceive);
   event_synchronous_init(&instance->_private.OnError);
   event_synchronous_init(&instance->_private.OnTransmit);

   // Needs to happen first in case we get a byte while we're in init
   ringbuffer_init(&instance->_private.ringBuffer, queueBuffer, (unsigned)queueBufferSize, (unsigned)sizeof(uint8_t));

   event_subscription_init(&instance->_private.onReceiveSubscription, instance, receive_callback);
   event_subscription_init(&instance->_private.onTransmitSubscription, instance, transmit_callback);
   event_subscription_init(&instance->_private.onErrorSubscription, instance, error_callback);

   event_subscribe(uart_get_on_receive_event(inner), &instance->_private.onReceiveSubscription);
   event_subscribe(uart_get_on_transmit_event(inner), &instance->_private.onTransmitSubscription);
   event_subscribe(uart_get_on_error_event(inner), &instance->_private.onErrorSubscription);
}

void uart_isr_safe_run(uart_isr_safe_t *instance)
{
   size_t queueCount;
   queueCount = ringbuffer_count(&instance->_private.ringBuffer);

   if(instance->_private.errorOccurred)
   {
      instance->_private.errorOccurred = false;
      event_synchronous_publish(&instance->_private.OnError, NULL);
   }

   if(instance->_private.transmitOccurred)
   {
      instance->_private.transmitOccurred = false;
      event_synchronous_publish(&instance->_private.OnTransmit, NULL);
   }

   while(queueCount)
   {
      uint8_t byte;

      ringbuffer_remove(&instance->_private.ringBuffer, (void *)&byte);

      {
         uart_on_receive_args_t args =
            { byte };
         event_synchronous_publish(&instance->_private.OnReceive, &args);
      }

      queueCount--;
   }
}


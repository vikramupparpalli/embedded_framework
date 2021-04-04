/*!
 * @file
 * @brief
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

extern "C"
{
#include "uart_isr_safe.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "uart_testdouble.h"
#include "uassert_test.h"
#include "utilities.h"

TEST_GROUP(uart_isr_safe_init)
{
   uart_isr_safe_t isrSafeUart;
   uart_testdouble_t uartTestDouble;
   i_uart_t *inner;

   uint8_t queueBuffer[10];

   void setup()
   {
      mock().disable();

      inner = (i_uart_t *)&uartTestDouble;
      uart_testdouble_init(&uartTestDouble);
   }

   void teardown()
   {
   }
};

static void ReceiveCallback(void *context, const void *args)
{
   REINTERPRET(onReceiveArgs, args, const uart_on_receive_args_t *);
   mock().actualCall("ReceiveCallback")
      .withParameter("context", context)
      .withParameter("byte", onReceiveArgs->byte);
}

static void TransmitCallback(void *context, const void *args)
{
   IGNORE_ARG(args);
   mock().actualCall("TransmitCallback")
      .withParameter("context", context);
}

static void ErrorCallback(void *context, const void *args)
{
   IGNORE_ARG(args);
   mock().actualCall("ErrorCallback")
      .withParameter("context", context);
}

TEST_GROUP(uart_isr_safe)
{
   uart_isr_safe_t isrSafeUart;
   uart_testdouble_t uartTestDouble;
   i_uart_t *inner;
   i_uart_t *instance;

   event_subscription_t onReceiveSubscription;
   event_subscription_t onTransmitSubscription;
   event_subscription_t onErrorSubscription;

   uint8_t receiveContext;
   uint8_t transmitContext;
   uint8_t errorContext;

   uint8_t queueBuffer[10];

   void setup()
   {
      instance = (i_uart_t *)&isrSafeUart;

      inner = (i_uart_t *)&uartTestDouble;
      uart_testdouble_init(&uartTestDouble);

      event_subscription_init(&onReceiveSubscription, &receiveContext, ReceiveCallback);
      event_subscription_init(&onTransmitSubscription, &transmitContext, TransmitCallback);
      event_subscription_init(&onErrorSubscription, &errorContext, ErrorCallback);

      mock().disable();
      uart_isr_safe_init(&isrSafeUart, inner, (uint8_t *)queueBuffer, sizeof(queueBuffer));
      mock().enable();
   }

   void teardown()
   {
   }
};

TEST(uart_isr_safe, Send)
{
   for(uint8_t byte = 0; byte < 4; byte++)
   {
      mock().expectOneCall("Send")
         .onObject(inner)
         .withParameter("byte", byte);

      uart_send(instance, byte);
   }
}

TEST(uart_isr_safe, ErrorNotification)
{
   event_subscribe(uart_get_on_error_event(instance), &onErrorSubscription);
   uart_testdouble_trigger_error(&uartTestDouble);

   mock().expectOneCall("ErrorCallback")
      .withParameter("context", (void *)&errorContext);

   // Call twice to make sure we only get one notification
   uart_isr_safe_run(&isrSafeUart);
   uart_isr_safe_run(&isrSafeUart);
}

TEST(uart_isr_safe, TransmitNotification)
{
   event_subscribe(uart_get_on_transmit_event(instance), &onTransmitSubscription);
   uart_testdouble_trigger_transmit(&uartTestDouble);

   mock().expectOneCall("TransmitCallback")
      .withParameter("context", (void *)&transmitContext);

   // Call twice to make sure we only get one notification
   uart_isr_safe_run(&isrSafeUart);
   uart_isr_safe_run(&isrSafeUart);
}

TEST(uart_isr_safe, ReceiveNotification_NoOverflow)
{
   event_subscribe(uart_get_on_receive_event(instance), &onReceiveSubscription);

   // Fill the queue
   for(uint8_t byte = 0; byte < sizeof(queueBuffer) - 1; byte++)
   {
      uart_testdouble_trigger_receive(&uartTestDouble, byte);
   }

   for(uint8_t byte = 0; byte < sizeof(queueBuffer) - 1; byte++)
   {
      mock().expectOneCall("ReceiveCallback")
         .withParameter("context", (void *)&receiveContext)
         .withParameter("byte", byte);
   }

   uart_isr_safe_run(&isrSafeUart);
}

TEST(uart_isr_safe, ReceiveNotification_Overflow)
{
   event_subscribe(uart_get_on_receive_event(instance), &onReceiveSubscription);

   // Fill the queue and then have extra bytes that will get discarded
   for(uint8_t byte = 0; byte < 2 * sizeof(queueBuffer); byte++)
   {
      uart_testdouble_trigger_receive(&uartTestDouble, byte);
   }

   for(uint8_t byte = 0; byte < sizeof(queueBuffer) - 1; byte++)
   {
      mock().expectOneCall("ReceiveCallback")
         .withParameter("context", (void *)&receiveContext)
         .withParameter("byte", byte);
   }

   uart_isr_safe_run(&isrSafeUart);
}

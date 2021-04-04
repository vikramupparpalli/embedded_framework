/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#include <stdint.h>
#include <stddef.h>
#include "CppUTestExt/MockSupport.h"
#include "uart_testdouble.h"

extern "C"
{
#include "i_uart.h"
#include "utilities.h"
}

static void Send(i_uart_t *_instance, const uint8_t byte)
{
   REINTERPRET(instance, _instance, uart_testdouble_t *);

   mock().actualCall("Send")
      .onObject(instance)
      .withParameter("byte", byte);

   if(instance->_private.automaticTransmission)
   {
      uart_testdouble_trigger_transmit(instance);
   }

   if(instance->_private.echo)
   {
      uart_testdouble_trigger_receive(instance, byte);
   }
}

static i_event_t * GetOnReceiveEvent(i_uart_t *_instance)
{
   REINTERPRET(instance, _instance, uart_testdouble_t *);
   return &instance->OnReceive.interface;
}

static i_event_t * GetOnTransmitEvent(i_uart_t *_instance)
{
   REINTERPRET(instance, _instance, uart_testdouble_t *);
   return &instance->OnTransmit.interface;
}

static i_event_t * GetOnErrorEvent(i_uart_t *_instance)
{
   REINTERPRET(instance, _instance, uart_testdouble_t *);
   return &instance->OnError.interface;
}

static const i_uart_api_t uartApi =
   { Send, GetOnReceiveEvent, GetOnTransmitEvent, GetOnErrorEvent };

void uart_testdouble_init(uart_testdouble_t *instance)
{
   instance->_private.echo = false;
   instance->_private.automaticTransmission = true;
   instance->interface.api = &uartApi;

   event_synchronous_init(&instance->OnReceive);
   event_synchronous_init(&instance->OnTransmit);
   event_synchronous_init(&instance->OnError);
}

void uart_testdouble_trigger_receive(uart_testdouble_t *instance, const uint8_t byte)
{
   uart_on_receive_args_t args =
      { byte };
   event_synchronous_publish(&instance->OnReceive, &args);
}

void uart_testdouble_trigger_transmit(uart_testdouble_t *instance)
{
   event_synchronous_publish(&instance->OnTransmit, NULL);
}

void uart_testdouble_trigger_error(uart_testdouble_t *instance)
{
   event_synchronous_publish(&instance->OnError, NULL);
}

void uart_testdouble_enable_echo(uart_testdouble_t *instance)
{
   instance->_private.echo = true;
}

void uart_testdouble_disable_echo(uart_testdouble_t *instance)
{
   instance->_private.echo = false;
}

void uart_testdouble_enable_automatic_transmission(uart_testdouble_t *instance)
{
   instance->_private.automaticTransmission = true;
}

void uart_testdouble_disable_automatic_transmission(uart_testdouble_t *instance)
{
   instance->_private.automaticTransmission = false;
}

#ifndef UART_TESTDOUBLE_H
#define UART_TESTDOUBLE_H

#include <stdint.h>
#include <stdbool.h>

extern "C"
{
#include "i_uart.h"
#include "event_synchronous.h"
}

typedef struct
{
   i_uart_t interface;
   event_synchronous_t OnReceive;
   event_synchronous_t OnTransmit;
   event_synchronous_t OnError;

   struct
   {
      bool echo;
      bool automaticTransmission;
   } _private;
} uart_testdouble_t;

void uart_testdouble_init(uart_testdouble_t *instance);
void uart_testdouble_trigger_receive(uart_testdouble_t *instance, const uint8_t byte);
void uart_testdouble_trigger_transmit(uart_testdouble_t *instance);
void uart_testdouble_trigger_error(uart_testdouble_t *instance);
void uart_testdouble_enable_echo(uart_testdouble_t *instance);
void uart_testdouble_disable_echo(uart_testdouble_t *instance);
void uart_testdouble_enable_automatic_transmission(uart_testdouble_t *instance);
void uart_testdouble_disable_automatic_transmission(uart_testdouble_t *instance);

#endif

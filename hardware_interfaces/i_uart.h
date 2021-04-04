/*!
 * @file
 * @brief
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#ifndef I_UART_H
#define I_UART_H

#include <stdint.h>
#include "i_event.h"

typedef struct
{
   const uint8_t byte;
} uart_on_receive_args_t;

struct i_uart_api_t;

typedef struct
{
   const struct i_uart_api_t *api;
} i_uart_t;

typedef struct i_uart_api_t
{
   void (*send)(i_uart_t *instance, const uint8_t byte);

   i_event_t * (*get_on_receive_event)(i_uart_t *instance);

   i_event_t * (*get_on_transmit_event)(i_uart_t *instance);

   i_event_t * (*get_on_error_event)(i_uart_t *instance);
} i_uart_api_t;

#define uart_send(instance, byte) \
   (instance)->api->send((instance), (byte))

#define uart_get_on_receive_event(instance) \
   (instance)->api->get_on_receive_event((instance))

#define uart_get_on_transmit_event(instance) \
   (instance)->api->get_on_transmit_event((instance))

#define uart_get_on_error_event(instance) \
   (instance)->api->get_on_error_event((instance))

#endif

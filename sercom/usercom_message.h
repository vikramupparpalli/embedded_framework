/*!
 * @file
 * @brief usercom Protocol Message format
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#ifndef USERCOM_MESSAGE_H
#define USERCOM_MESSAGE_H

#include <stdint.h>
#include "usercom_packet.h"
#include "utilities.h"

typedef struct
{
   struct
   {
      usercom_packet_t packet;
   } _private;
} usercom_message_t;

#define USERCOM_MESSAGE_MAXPAYLOAD (usercom_PACKET_MAXPAYLOAD - 1)

#define USERCOM_MESSAGE_OVERHEAD (usercom_PACKET_OVERHEAD + 1)

#define STACK_ALLOC_USERCOM_MESSAGE(_name, _payloadLength) \
   uint8_t MACRO_SAFE_CONCATENATE(_name, Storage)[_payloadLength + USERCOM_MESSAGE_OVERHEAD] = {0, _payloadLength + 1}; \
   usercom_message_t * const _name = (usercom_message_t *)MACRO_SAFE_CONCATENATE(_name, Storage)

#define STACK_ALLOC_USERCOM_MESSAGE_TYPE(_messageName, _payloadName, _command, _payloadType) \
   STACK_ALLOC_USERCOM_MESSAGE(_messageName, sizeof(_payloadType)); \
   _payloadType *_payloadName; \
   usercom_message_set_command(_messageName, _command); \
   _payloadName = (_payloadType *)usercom_message_get_payload(_messageName)

#define STATIC_ALLOC_USERCOM_MESSAGE(_name, _payloadLength) \
   static uint8_t _name##Storage[_payloadLength + USERCOM_MESSAGE_OVERHEAD] = {0, _payloadLength + 1}; \
   static usercom_message_t * const _name = (usercom_message_t *)_name##Storage

uint8_t usercom_message_get_source(const usercom_message_t *instance);
uint8_t usercom_message_get_destination(const usercom_message_t *instance);
uint8_t usercom_message_get_command(const usercom_message_t *instance);
uint8_t usercom_message_get_payload_length(const usercom_message_t *instance);
uint8_t * usercom_message_get_payload(usercom_message_t *instance);
const uint8_t * usercom_message_get_const_payload(const usercom_message_t *instance);
void usercom_message_set_destination(usercom_message_t *instance, uint8_t destination);
void usercom_message_set_source(usercom_message_t *instance, uint8_t source);
void usercom_message_set_command(usercom_message_t *instance, uint8_t command);
void usercom_message_set_payload_length(usercom_message_t *instance, uint8_t payloadLength);

#endif

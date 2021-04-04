/*!
 * @file
 * @brief usercom message layer
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#include "usercom_message.h"
#include "uassert.h"

uint8_t usercom_message_get_source(const usercom_message_t *instance)
{
   return instance->_private.packet.source;
}

uint8_t usercom_message_get_destination(const usercom_message_t *instance)
{
   return instance->_private.packet.destination;
}

uint8_t usercom_message_get_command(const usercom_message_t *instance)
{
   return instance->_private.packet.payload[0];
}

uint8_t usercom_message_get_payload_length(const usercom_message_t *instance)
{
   return instance->_private.packet.payloadLength - 1;
}

uint8_t * usercom_message_get_payload(usercom_message_t *instance)
{
   return instance->_private.packet.payload + 1;
}

const uint8_t * usercom_message_get_const_payload(const usercom_message_t *instance)
{
   return instance->_private.packet.payload + 1;
}

void usercom_message_set_destination(usercom_message_t *instance, uint8_t destination)
{
   instance->_private.packet.destination = destination;
}

void usercom_message_set_source(usercom_message_t *instance, uint8_t source)
{
   instance->_private.packet.source = source;
}

void usercom_message_set_command(usercom_message_t *instance, uint8_t command)
{
   instance->_private.packet.payload[0] = command;
}

void usercom_message_set_payload_length(usercom_message_t *instance, uint8_t payloadLength)
{
   instance->_private.packet.payloadLength = payloadLength + 1;
}

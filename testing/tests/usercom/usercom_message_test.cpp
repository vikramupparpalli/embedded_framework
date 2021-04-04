/*!
 * @file
 * @brief test file for usercom
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

extern "C"
{
#include "usercom_message.h"
#include "utilities.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "uassert_test.h"

TEST_GROUP(usercom_message)
{
};

TEST(usercom_message, get_source)
{
   const uint8_t source = 0x45;
   STACK_ALLOC_USERCOM_MESSAGE(message, 0);
   message->_private.packet.source = source;

   CHECK(source == usercom_message_get_source(message));
}

TEST(usercom_message, get_destination)
{
   const uint8_t destination = 0x45;
   STACK_ALLOC_USERCOM_MESSAGE(message, 0);
   message->_private.packet.destination = destination;

   CHECK(destination == usercom_message_get_destination(message));
}

TEST(usercom_message, get_command)
{
   const uint8_t command = 0x45;
   STACK_ALLOC_USERCOM_MESSAGE(message, 0);
   message->_private.packet.payload[0] = command;

   CHECK(command == usercom_message_get_command(message));
}

TEST(usercom_message, get_payload)
{
   STACK_ALLOC_USERCOM_MESSAGE(message, 0);
   CHECK(&message->_private.packet.payload[1] == usercom_message_get_payload(message));
}

TEST(usercom_message, get_const_payload)
{
   STACK_ALLOC_USERCOM_MESSAGE(message, 0);
   CHECK((const uint8_t *)&message->_private.packet.payload[1] == usercom_message_get_const_payload(message));
}

TEST(usercom_message, get_payload_length_empty)
{
   STACK_ALLOC_USERCOM_MESSAGE(message, 0);
   CHECK(1 == message->_private.packet.payloadLength);
   CHECK(0 == usercom_message_get_payload_length(message));
}

TEST(usercom_message, get_payload_length_non_empty)
{
   STACK_ALLOC_USERCOM_MESSAGE(message, 3);
   CHECK(4 == message->_private.packet.payloadLength);
   CHECK(3 == usercom_message_get_payload_length(message));
}

TEST(usercom_message, set_destination)
{
   const uint8_t destination = 0x34;
   STACK_ALLOC_USERCOM_MESSAGE(message, 0);
   usercom_message_set_destination(message, destination);
   CHECK(message->_private.packet.destination == destination);
}

TEST(usercom_message, set_command)
{
   const uint8_t command = 0x34;
   STACK_ALLOC_USERCOM_MESSAGE(message, 0);
   usercom_message_set_command(message, command);
   CHECK(message->_private.packet.payload[0] == command);
}

TEST(usercom_message, set_payload_length)
{
   const uint8_t newPayloadLength = 3;
   STACK_ALLOC_USERCOM_MESSAGE(message, 4);
   usercom_message_set_payload_length(message, newPayloadLength);
   CHECK(message->_private.packet.payloadLength == newPayloadLength + 1);
}

typedef struct
{
   uint8_t data1;
   uint8_t data2;
   uint8_t data3;
} some_message_t;

TEST(usercom_message, MessageTypeAllocator)
{
   STACK_ALLOC_USERCOM_MESSAGE_TYPE(message, payload, 0x54, some_message_t);
   payload->data1 = 0x11;
   payload->data2 = 0x22;
   payload->data3 = 0x33;

   CHECK(usercom_message_get_command(message) == 0x54);
   CHECK(usercom_message_get_payload(message)[OFFSET_OF(some_message_t, data1)] == 0x11);
   CHECK(usercom_message_get_payload(message)[OFFSET_OF(some_message_t, data2)] == 0x22);
   CHECK(usercom_message_get_payload(message)[OFFSET_OF(some_message_t, data3)] == 0x33);
}


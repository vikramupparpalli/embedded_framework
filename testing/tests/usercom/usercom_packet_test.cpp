/*!
 * @file
 * @brief
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */
extern "C"
{
#include "usercom_packet.h"
#include "utilities.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "uassert_test.h"

TEST_GROUP(usercom_packet)
{
   void setup()
   {
   }
};

typedef struct
{
   uint8_t data1;
   uint8_t data2;
   uint8_t data3;
} some_packet_t;

TEST(usercom_packet, PacketTypeAllocator)
{
   STACK_ALLOC_USERCOM_TYPE(packet, payload, some_packet_t);
   payload->data1 = 0x11;
   payload->data2 = 0x22;
   payload->data3 = 0x33;

   CHECK(packet->payload[OFFSET_OF(some_packet_t, data1)] == 0x11);
   CHECK(packet->payload[OFFSET_OF(some_packet_t, data2)] == 0x22);
   CHECK(packet->payload[OFFSET_OF(some_packet_t, data3)] == 0x33);
}

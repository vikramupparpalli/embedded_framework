/*!
 * @file
 * @brief usercom packet format
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#ifndef USERCOM_PACKET_H
#define USERCOM_PACKET_H

#include <stdint.h>

typedef struct
{
   uint8_t destination;
   uint8_t payloadLength;
   uint8_t source;
   uint8_t payload[1];
} usercom_packet_t;

#define USERCOM_PACKET_OVERHEAD (3)
#define USERCOM_TRANSMISSION_OVERHEAD (7)
#define USERCOM_MAXPAYLOAD (UINT8_MAX - USERCOM_TRANSMISSION_OVERHEAD)

#define STACK_ALLOC_USERCOM(_name, _payloadLength) \
   uint8_t _name##Storage[_payloadLength + USERCOM_PACKET_OVERHEAD] = {0, _payloadLength}; \
   usercom_packet_t * const _name = (usercom_packet_t *)_name##Storage

#define STACK_ALLOC_USERCOM_TYPE(_packetName, _payloadName, _payloadType) \
   STACK_ALLOC_USERCOM(_packetName, sizeof(_payloadType)); \
   _payloadType *_payloadName; \
   _payloadName = (_payloadType *)_packetName->payload;

#define STATIC_ALLOC_USERCOM(_name, _payloadLength) \
   static uint8_t _name##Storage[_payloadLength + USERCOM_PACKET_OVERHEAD] = {0, _payloadLength}; \
   static usercom_packet_t * const _name = (usercom_packet_t *)_name##Storage

#endif

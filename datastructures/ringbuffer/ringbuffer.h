/*!
 * @file
 * @brief ring buffer support
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
   uint8_t *buffer;
   unsigned capacity;
   unsigned elementSize;
   unsigned head;
   unsigned tail;
   bool full;
} ringbuffer_t;

void ringbuffer_init(ringbuffer_t *rbuf, void *buffer, const unsigned capacity, const unsigned elementSize);

void ringbuffer_add(ringbuffer_t *rbuf, const void *element);

void ringbuffer_remove(ringbuffer_t *rbuf, void *element);

void ringbuffer_discard(ringbuffer_t *rbuf);

void ringbuffer_at(const ringbuffer_t *rbuf, void *element, const unsigned index);

unsigned ringbuffer_count(const ringbuffer_t *rbuf);

unsigned ringbuffer_capacity(const ringbuffer_t *rbuf);

void ringbuffer_clear(ringbuffer_t *rbuf);

#endif

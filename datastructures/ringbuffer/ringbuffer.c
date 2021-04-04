/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#include <string.h>
#include "ringbuffer.h"
#include "uassert.h"

void ringbuffer_clear(ringbuffer_t *rbuf)
{
   uassert(rbuf);

   rbuf->full = false;
   rbuf->head = 0;
   rbuf->tail = 0;
}

void ringbuffer_init(ringbuffer_t *rbuf, void *buffer, const unsigned capacity, const unsigned elementSize)
{
   uassert(rbuf);
   uassert(buffer);
   uassert(elementSize);
   uassert(capacity);

   rbuf->buffer = (uint8_t *)buffer;
   rbuf->elementSize = elementSize;
   rbuf->capacity = capacity;

   ringbuffer_clear(rbuf);
}

void ringbuffer_add(ringbuffer_t *rbuf, const void *element)
{
   uassert(rbuf);
   uassert(element);

   (void)memcpy(rbuf->buffer + rbuf->head * rbuf->elementSize, element, (size_t)rbuf->elementSize);

   if(!rbuf->full)
   {
      if(((rbuf->head + 1) % rbuf->capacity) == rbuf->tail)
      {
         rbuf->full = true;
      }
   }
   else
   {
      rbuf->tail = (rbuf->tail + 1) % rbuf->capacity;
   }

   rbuf->head = (rbuf->head + 1) % rbuf->capacity;
}

void ringbuffer_at(const ringbuffer_t *rbuf, void *element, const unsigned index)
{
   void *from;

   uassert(rbuf);
   uassert(element);
   uassert(index < ringbuffer_count(rbuf));

   from = rbuf->buffer + ((rbuf->tail + index) % rbuf->capacity) * rbuf->elementSize;
   (void)memcpy(element, from, (size_t)rbuf->elementSize);
}

void ringbuffer_remove(ringbuffer_t *rbuf, void *element)
{
   ringbuffer_at(rbuf, element, 0);

   rbuf->full = false;
   rbuf->tail = (rbuf->tail + 1) % rbuf->capacity;
}

void ringbuffer_discard(ringbuffer_t *rbuf)
{
   uassert(ringbuffer_count(rbuf) > 0);

   rbuf->full = false;
   rbuf->tail = (rbuf->tail + 1) % rbuf->capacity;
}

unsigned ringbuffer_count(const ringbuffer_t *rbuf)
{
   uassert(rbuf);

   if(rbuf->full)
   {
      return rbuf->capacity;
   }
   else
   {
      unsigned head = rbuf->head;
      unsigned tail = rbuf->tail;

      if(head >= tail)
      {
         return head - tail;
      }
      else
      {
         return rbuf->capacity - (tail - head);
      }
   }
}

unsigned ringbuffer_capacity(const ringbuffer_t *rbuf)
{
   uassert(rbuf);

   return rbuf->capacity;
}

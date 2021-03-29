/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#ifndef EVENT_SYNCHRONOUS_H
#define EVENT_SYNCHRONOUS_H

#include "i_event.h"
#include "linked_list.h"

typedef struct
{
   i_event_t interface;

   struct
   {
      linked_list_t subscription_list;
   } _private;
} event_synchronous_t;

/*!
 * @param instance
 */
void event_synchronous_init(event_synchronous_t *instance);

/*!
 * @param instance
 * @param args
 */
void event_synchronous_publish(event_synchronous_t *instance, const void *args);

#endif

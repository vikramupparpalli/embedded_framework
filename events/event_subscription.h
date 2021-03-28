/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#ifndef EVENT_SUBSCRIPTION_H
#define EVENT_SUBSCRIPTION_H

#include "linked_list.h"

typedef void (*event_subscription_callback_t)(void *context, const void *args);

typedef struct
{
   struct
   {
      linked_list_node_t node;
      event_subscription_callback_t callback;
      void *context;
   } _private;
} event_subscription_t;


void event_subscription_init(event_subscription_t *instance, void *context, event_subscription_callback_t callback);

void event_subscription_publish(event_subscription_t *instance, const void *args);

#endif

/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#include <stdbool.h>
#include "event_synchronous.h"
#include "utilities.h"

typedef struct
{
   const void *args;
} publish_context_t;

static bool for_each_publish(linked_list_node_t *node, void *context, const size_t index)
{
   event_subscription_t *subscription = (event_subscription_t *)node;
   REINTERPRET(publishContext, context, publish_context_t *);
   IGNORE_ARG(index);

   event_subscription_publish(subscription, publishContext->args);

   return true;
}

void event_synchronous_publish(event_synchronous_t *instance, const void *args)
{
   publish_context_t publishContext;

   publishContext.args = args;

   linked_list_for_each(&instance->_private.subscription_list, for_each_publish, &publishContext);
}

static void subscribe(i_event_t *_instance, event_subscription_t *subscription)
{
   REINTERPRET(instance, _instance, event_synchronous_t *);

   if(false == linked_list_contains(&instance->_private.subscription_list, (linked_list_node_t *)subscription))
   {
      linked_list_push_front(&instance->_private.subscription_list, (linked_list_node_t *)subscription);
   }
}

static void unsubscribe(i_event_t *_instance, event_subscription_t *subscription)
{
   REINTERPRET(instance, _instance, event_synchronous_t *);
   linked_list_remove(&instance->_private.subscription_list, (linked_list_node_t *)subscription);
}

static const i_event_api_t api =
   { subscribe, unsubscribe };

void event_synchronous_init(event_synchronous_t *instance)
{
   linked_list_init(&instance->_private.subscription_list);
   instance->interface.api = &api;
}

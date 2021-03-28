/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#include "event_subscription.h"

void event_subscription_init(event_subscription_t *instance, void *context, event_subscription_callback_t callback)
{
   instance->_private.callback = callback;
   instance->_private.context = context;
}

void event_subscription_publish(event_subscription_t *instance, const void *args)
{
   instance->_private.callback(instance->_private.context, args);
}

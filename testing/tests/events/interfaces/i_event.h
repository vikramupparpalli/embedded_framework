/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#ifndef I_EVENT_H
#define I_EVENT_H

#include "event_subscription.h"

struct i_event_api_t;

typedef struct
{
   const struct i_event_api_t *api;
} i_event_t;

typedef struct i_event_api_t
{
   /*!
    * @pre The subscription must not already be subscribed.
    * @param instance
    * @param subscription
    */
   void (*subscribe)(i_event_t *instance, event_subscription_t *subscription);

   /*!
    * @param instance
    * @param subscription
    */
   void (*unsubscribe)(i_event_t *instance, event_subscription_t *subscription);
} i_event_api_t;

#define event_subscribe(instance, subscription) \
   (instance)->api->subscribe((instance), (subscription))

#define event_unsubscribe(instance, subscription) \
   (instance)->api->unsubscribe((instance), (subscription))

#endif

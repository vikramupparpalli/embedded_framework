/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

extern "C"
{
#include "event_subscription.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "uassert_test.h"

TEST_GROUP(event_subscription)
{
   event_subscription_t instance;
   int context;
   int args;

   static void mock_callback(void *context, const void *args)
   {
      mock()
         .actualCall("mock_callback")
         .withParameter("context", context)
         .withParameter("args", args);
   }

   void setup()
   {
      event_subscription_init(&instance, &context, mock_callback);
   }
};

TEST(event_subscription, ShouldPublishWithPublisherProvidedArgsAndSubscriberProvidedContext)
{
   mock()
      .expectOneCall("mock_callback")
      .withParameter("context", &context)
      .withParameter("args", (const void *)&args);

   event_subscription_publish(&instance, &args);
}

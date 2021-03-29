/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

extern "C"
{
#include "event_synchronous.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "uassert_test.h"

TEST_GROUP(event_synchronous)
{
   event_synchronous_t self;

   event_subscription_t subscription1;
   event_subscription_t subscription2;

   void setup()
   {
      event_synchronous_init(&self);
      event_subscription_init(&subscription1, NULL, Subscriber1);
      event_subscription_init(&subscription2, NULL, Subscriber2);
   }

   static void Subscriber1(void *context, const void *args)
   {
      (void)context;
      mock().actualCall("Subscriber1").withParameter("args", args);
   }

   static void Subscriber2(void *context, const void *args)
   {
      (void)context;
      mock().actualCall("Subscriber2").withParameter("args", args);
   }
};

TEST(event_synchronous, ShouldDoNothingWhenPublishedWithNoSubscribers)
{
   event_synchronous_publish(&self, (const void *)0x1234);
}

TEST(event_synchronous, ShouldPublishToAllSubscribers)
{
   event_subscribe(&self.interface, &subscription1);
   event_subscribe(&self.interface, &subscription2);

   mock().expectOneCall("Subscriber1").withParameter("args", (const void *)0x1234);
   mock().expectOneCall("Subscriber2").withParameter("args", (const void *)0x1234);
   event_synchronous_publish(&self, (const void *)0x1234);
}

TEST(event_synchronous, ShouldNotPublishToSubscribersThatHaveUnsubscribed)
{
   event_subscribe(&self.interface, &subscription1);
   event_subscribe(&self.interface, &subscription2);
   event_unsubscribe(&self.interface, &subscription1);

   mock().expectOneCall("Subscriber2").withParameter("args", (const void *)0x5678);
   event_synchronous_publish(&self, (const void *)0x5678);
}

TEST(event_synchronous, ShouldAllowSubscribersToResubscribe)
{
   event_subscribe(&self.interface, &subscription1);
   event_subscribe(&self.interface, &subscription2);
   event_subscribe(&self.interface, &subscription1);

   mock().expectOneCall("Subscriber1").withParameter("args", (const void *)0x5678);
   mock().expectOneCall("Subscriber2").withParameter("args", (const void *)0x5678);
   event_synchronous_publish(&self, (const void *)0x5678);
}

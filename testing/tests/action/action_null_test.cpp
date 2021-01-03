extern "C"
{
#include "action_null.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(action_null)
{
   void NothingShouldHappen()
   {
   }

   void WhenNullActionIsInvoked()
   {
      action_run(action_null_get_pointer());
   }
};

TEST(action_null, IsASingleton)
{
   CHECK(action_null_get_pointer() == action_null_get_pointer());
}

TEST(action_null, DoesNothingWhenInvoked)
{
   NothingShouldHappen();
   WhenNullActionIsInvoked();
}

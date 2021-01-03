/*!
 * @file
 * @brief Tests for the memory clearing action
 *
 * Absolutely Non-Confidential - No rights reserved.
 */

extern "C"
{
#include <string.h>
#include "action_clear_memory.h"
#include "uassert_test.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

static char sampleString[] = "Yeah.. you wish";

TEST_GROUP(action_clear_memory)
{
   action_clear_memory_t instance;

   void GivenModuleInitialized(void *pointer, size_t blockSize)
   {
	   action_clear_memory_initialization(&instance, pointer, blockSize);
   }

   void WhenActionIsInvoked(void)
   {
      action_run(&instance.interface);
   }

   void BlockShouldContainData(void)
   {
      for(size_t i = 0; i < sizeof(sampleString) - 1; i++)
      {
         uassert(sampleString[i] != 0);
      }
   }

   void BlockShouldBeCleared(void)
   {
      for(size_t i = 0; i < sizeof(sampleString) - 1; i++)
      {
         uassert(sampleString[i] == 0);
      }
   }
};

TEST(action_clear_memory, ShouldClearSpecifiedMemoryBlock)
{
   GivenModuleInitialized(sampleString, strlen(sampleString) * sizeof(sampleString[0]));
   BlockShouldContainData();

   WhenActionIsInvoked();
   BlockShouldBeCleared();
}

/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */


extern "C"
{
#include "ringbuffer.h"
#include "utilities.h"
}

#include <stddef.h>
#include <stdint.h>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "uassert_test.h"
#include "memoryutils.h"

enum
{
   MaxElements = 3,
   BigBufferMaxElements = 10
};

TEST_GROUP(ringbuffer)
{
   uint16_t buffer[MaxElements];
   uint16_t bigBuffer[BigBufferMaxElements];
   ringbuffer_t instance;
   uint16_t removedElement;

   void setup()
   {
      ASSUME_UNINITIALIZED(buffer);
      ringbuffer_init(&instance, buffer, NUM_ELEMENTS(buffer), ELEMENT_SIZE(buffer));
      ASSUME_UNINITIALIZED(removedElement);
   }

   void GivenThisManyIncrementingElementsHaveBeenAddedToTheringbuffer(const uint16_t numberOfElements)
   {
      for(uint16_t element = 0; element < numberOfElements; element++)
      {
         ringbuffer_add(&instance, &element);
      }
   }

   void GivenTheringbufferIsEmpty()
   {

   }

   void GivenTheringbufferIsInitializedWithCapacity(const uint16_t capacity)
   {
      ringbuffer_init(&instance, buffer, capacity, ELEMENT_SIZE(buffer));
   }

   void WhenAnElementIsAddedToAnInvalidBuffer()
   {
      uint16_t element = 1;
      ringbuffer_add(NULL, &element);
   }

   void WhenAnInvalidElementIsAddedToTheringbuffer()
   {
      ringbuffer_add(&instance, NULL);
   }

   void GivenTheringbufferHasOneElementWithValue(uint16_t element)
   {
      ringbuffer_add(&instance, &element);
   }

   void WhenOneElementIsRemoved()
   {
      ringbuffer_remove(&instance, &removedElement);
   }

   void WhenAllElementsAreRemoved()
   {
      for(size_t i = 0; i < MaxElements; i++)
      {
         ringbuffer_remove(&instance, &removedElement);
      }
   }

   void WhenAnElementIsDiscarded()
   {
      ringbuffer_discard(&instance);
   }

   void WhenAllElementsAreDiscarded()
   {
      for(size_t i = 0; i < MaxElements; i++)
      {
         ringbuffer_discard(&instance);
      }
   }

   void AfterringbufferIsCleared()
   {
      ringbuffer_clear(&instance);
   }

   void TheringbufferElementCountShouldBe(const uint16_t count)
   {
      CHECK_EQUAL(count, ringbuffer_count(&instance));
   }

   void ThenTheringbufferShouldContainThisElementAtIndex(const uint16_t expectedElement, const uint16_t index)
   {
      uint16_t actualElement;
      ringbuffer_at(&instance, &actualElement, index);
      CHECK_EQUAL(expectedElement, actualElement);
   }

   void TheRemovedElementShouldBe(uint16_t expectedElement)
   {
      CHECK_EQUAL(expectedElement, removedElement);
   }

   void ThenTheCapacityShouldBe(uint16_t capacity)
   {
      CHECK_EQUAL(capacity, ringbuffer_capacity(&instance));
   }

   void TheringbufferShouldBeFilledWithIncrementingElementsTo(const uint16_t numberOfElements)
   {
      for(size_t i = 0; i < numberOfElements; i++)
      {
         WhenOneElementIsRemoved();
         TheRemovedElementShouldBe(i);
      }
   }
};

TEST(ringbuffer, ShouldFailWhenBufferIsInitializedWithInvalidringbuffer)
{
   ShouldFailAssertion(ringbuffer_init(NULL, bigBuffer, NUM_ELEMENTS(bigBuffer), ELEMENT_SIZE(bigBuffer)));
}

TEST(ringbuffer, ShouldFailWhenBufferIsInitializedWithInvalidStorageBuffer)
{
   ShouldFailAssertion(ringbuffer_init(&instance, NULL, NUM_ELEMENTS(bigBuffer), ELEMENT_SIZE(bigBuffer)));
}

TEST(ringbuffer, ShouldFailWhenBufferIsInitializedWithNoElements)
{
   ShouldFailAssertion(ringbuffer_init(&instance, bigBuffer, NUM_ELEMENTS(bigBuffer), 0));
}

TEST(ringbuffer, ShouldFailWhenBufferIsInitializedWithInvalidCapacity)
{
   ShouldFailAssertion(ringbuffer_init(&instance, bigBuffer, 0, ELEMENT_SIZE(bigBuffer)));
}

TEST(ringbuffer, ShouldFailWhenAnElementIsAddedToANullringbuffer)
{
   ShouldFailAssertion(WhenAnElementIsAddedToAnInvalidBuffer());
}

TEST(ringbuffer, ShouldFailWhenANullElementIsAdded)
{
   ShouldFailAssertion(WhenAnInvalidElementIsAddedToTheringbuffer());
}

TEST(ringbuffer, ShouldInitializeWithZeroCount)
{
   TheringbufferElementCountShouldBe(0);
}

TEST(ringbuffer, ShouldIncrementCountAfterAddingOneElement)
{
   GivenTheringbufferHasOneElementWithValue(0);
   TheringbufferElementCountShouldBe(1);
}

TEST(ringbuffer, ShouldIncrementCountAfterAddingAllElements)
{
   GivenThisManyIncrementingElementsHaveBeenAddedToTheringbuffer(MaxElements);
   TheringbufferElementCountShouldBe(MaxElements);
}

TEST(ringbuffer, ShouldContainAnElementAfterAddingOneElement)
{
   GivenTheringbufferHasOneElementWithValue(0);
   ThenTheringbufferShouldContainThisElementAtIndex(0, 0);
}

TEST(ringbuffer, ShouldIncrementCountAfterAddingMultipleElements)
{
   GivenTheringbufferHasOneElementWithValue(0);
   GivenTheringbufferHasOneElementWithValue(1);

   ThenTheringbufferShouldContainThisElementAtIndex(0, 0);
   ThenTheringbufferShouldContainThisElementAtIndex(1, 1);
}

TEST(ringbuffer, ShouldMaintainMaxSizeAfterAddingOneExtraElement)
{
   GivenThisManyIncrementingElementsHaveBeenAddedToTheringbuffer(MaxElements + 1);
   TheringbufferElementCountShouldBe(MaxElements);
}

TEST(ringbuffer, ShouldWrapToStartOfBufferAfterAddingOneExtraElement)
{
   GivenThisManyIncrementingElementsHaveBeenAddedToTheringbuffer(MaxElements + 1);
   ThenTheringbufferShouldContainThisElementAtIndex(1, 0);
}

TEST(ringbuffer, ShouldWrapAndOverwriteEntireBuffer)
{
   GivenThisManyIncrementingElementsHaveBeenAddedToTheringbuffer(3 * MaxElements);
   ThenTheringbufferShouldContainThisElementAtIndex(8, 2);
}

TEST(ringbuffer, ShouldNotBeAbleToRemoveAnElementFromANullringbuffer)
{
   uint16_t element = 1;
   GivenTheringbufferHasOneElementWithValue(0);
   ShouldFailAssertion(ringbuffer_remove(NULL, &element));
}

TEST(ringbuffer, ShouldNotBeAbleToRemoveANullElement)
{
   GivenTheringbufferHasOneElementWithValue(0);
   ShouldFailAssertion(ringbuffer_remove(&instance, NULL));
}

TEST(ringbuffer, ShouldNotBeAbleToRemoveFromAnEmptyringbuffer)
{
   uint16_t element = 1;
   ShouldFailAssertion(ringbuffer_remove(&instance, &element));
}

TEST(ringbuffer, ShouldDecrementCountAfterRemovingOneElement)
{
   GivenTheringbufferHasOneElementWithValue(0);
   WhenOneElementIsRemoved();
   TheringbufferElementCountShouldBe(0);
}

TEST(ringbuffer, ShouldDecrementCountAfterRemovingAllElements)
{
   GivenThisManyIncrementingElementsHaveBeenAddedToTheringbuffer(MaxElements);
   WhenAllElementsAreRemoved();
   TheringbufferElementCountShouldBe(0);
}

TEST(ringbuffer, ShouldBeAbleToRemoveOneElement)
{
   GivenTheringbufferHasOneElementWithValue(0);
   WhenOneElementIsRemoved();
   TheRemovedElementShouldBe(0);
}

TEST(ringbuffer, ShouldBeAbleToRemoveAllElements)
{
   GivenThisManyIncrementingElementsHaveBeenAddedToTheringbuffer(MaxElements);
   TheringbufferShouldBeFilledWithIncrementingElementsTo(MaxElements);
}

TEST(ringbuffer, ShouldBeAbleToRemoveAllElementsAfterAddingOneExtraElement)
{
   GivenThisManyIncrementingElementsHaveBeenAddedToTheringbuffer(MaxElements + 1);
   WhenAllElementsAreRemoved();
   TheringbufferElementCountShouldBe(0);
}

TEST(ringbuffer, ShouldNotBeAbleToDiscardFromAnEmptyringbuffer)
{
   ShouldFailAssertion(ringbuffer_discard(&instance));
}

TEST(ringbuffer, ShouldDecrementCountAfterDiscardingOneElement)
{
   GivenTheringbufferHasOneElementWithValue(0);
   WhenAnElementIsDiscarded();
   TheringbufferElementCountShouldBe(0);
}

TEST(ringbuffer, ShouldDecreaseCountAfterDiscardingManyElements)
{
   GivenThisManyIncrementingElementsHaveBeenAddedToTheringbuffer(MaxElements);
   WhenAllElementsAreDiscarded();
   TheringbufferElementCountShouldBe(0);
}

TEST(ringbuffer, ShouldNotBeAbleToGetElementFromNullringbuffer)
{
   uint16_t element = 1;
   ShouldFailAssertion(ringbuffer_at(NULL, &element, 0));
}

TEST(ringbuffer, ShouldNotBeAbleToGetNullElementFromringbuffer)
{
   GivenTheringbufferHasOneElementWithValue(0);
   ShouldFailAssertion(ringbuffer_at(&instance, NULL, 0));
}

TEST(ringbuffer, ShouldNotBeAbleToGetElementFromEmptyringbuffer)
{
   GivenTheringbufferIsEmpty();
   uint16_t element;
   ShouldFailAssertion(ringbuffer_at(&instance, &element, 0));
}

TEST(ringbuffer, ShouldNotBeAbleToGetOutOfBoundsElement)
{
   GivenTheringbufferHasOneElementWithValue(0);
   uint16_t element;
   ShouldFailAssertion(ringbuffer_at(&instance, &element, 1));
}

TEST(ringbuffer, ShouldNotBeAbleToCountANullringbuffer)
{
   GivenTheringbufferIsEmpty();
   ShouldFailAssertion(ringbuffer_count(NULL));
}

TEST(ringbuffer, ShouldNotBeAbleToClearANullringbuffer)
{
   ShouldFailAssertion(ringbuffer_clear(NULL));
}

TEST(ringbuffer, ShouldResetCountAfterClearingringbuffer)
{
   GivenThisManyIncrementingElementsHaveBeenAddedToTheringbuffer(MaxElements);
   AfterringbufferIsCleared();
   TheringbufferElementCountShouldBe(0);
}

TEST(ringbuffer, ShouldBeAbleToFullyRefillAndRemoveFromBufferAfterClearing)
{
   GivenThisManyIncrementingElementsHaveBeenAddedToTheringbuffer(MaxElements);
   AfterringbufferIsCleared();
   GivenThisManyIncrementingElementsHaveBeenAddedToTheringbuffer(MaxElements);
   TheringbufferShouldBeFilledWithIncrementingElementsTo(MaxElements);
}

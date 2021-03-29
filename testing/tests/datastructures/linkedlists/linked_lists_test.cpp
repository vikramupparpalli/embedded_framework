/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

extern "C"
{
#include "linked_list.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <stddef.h>
#include <stdint.h>
#include "uassert_test.h"
#include "utilities.h"

TEST_GROUP(linked_list_init)
{
};

TEST(linked_list_init, Can_Init)
{
   linked_list_t list;
   linked_list_init(&list);
}

TEST(linked_list_init, Empty_After_Init)
{
   linked_list_t list;
   linked_list_init(&list);
   CHECK(0 == linked_list_count(&list));
}

TEST(linked_list_init, Init_With_Null_List)
{
   CHECK_ASSERTION_FAILED(linked_list_init(NULL));
}

TEST_GROUP(linked_list)
{
   linked_list_t list;
   linked_list_node_t node1, node2, node3;
   uint8_t context;

   void setup()
   {
      linked_list_init(&list);
   }
};

TEST(linked_list, Count_Null_List)
{
   CHECK_ASSERTION_FAILED(linked_list_count(NULL));
}

TEST(linked_list, At_Null_List)
{
   CHECK_ASSERTION_FAILED(linked_list_at(NULL, 0));
}

TEST(linked_list, At_Out_Of_Range)
{
   CHECK_ASSERTION_FAILED(linked_list_at(&list, 0));

   linked_list_push_front(&list, &node1);

   CHECK_ASSERTION_FAILED(linked_list_at(&list, 1));
}

TEST(linked_list, IndexOf_Null_List)
{
   linked_list_push_front(&list, &node1);

   CHECK_ASSERTION_FAILED(linked_list_index_of(NULL, &node1));
}

TEST(linked_list, IndexOf_Null_Node)
{
   CHECK_ASSERTION_FAILED(linked_list_index_of(&list, NULL));
}

TEST(linked_list, IndexOf_Not_In_List)
{
   linked_list_push_front(&list, &node1);

   CHECK_ASSERTION_FAILED(linked_list_index_of(&list, &node2));
}

TEST(linked_list, IndexOf)
{
   linked_list_push_front(&list, &node1);
   CHECK(0 == linked_list_index_of(&list, &node1));

   linked_list_push_front(&list, &node2);
   CHECK(0 == linked_list_index_of(&list, &node2));
   CHECK(1 == linked_list_index_of(&list, &node1));

   linked_list_push_front(&list, &node3);
   CHECK(0 == linked_list_index_of(&list, &node3));
   CHECK(1 == linked_list_index_of(&list, &node2));
   CHECK(2 == linked_list_index_of(&list, &node1));
}

TEST(linked_list, Contains_Null_List)
{
   CHECK_ASSERTION_FAILED(linked_list_contains(NULL, &node1));
}

TEST(linked_list, Contains_Null_Node)
{
   CHECK_ASSERTION_FAILED(linked_list_contains(&list, NULL));
}

TEST(linked_list, PushFront_Null_List)
{
   CHECK_ASSERTION_FAILED(linked_list_push_front(NULL, &node1));
}

TEST(linked_list, PushFront_Null_Node)
{
   CHECK_ASSERTION_FAILED(linked_list_push_front(&list, NULL));
}

TEST(linked_list, PushFront_Already_In_List)
{
   linked_list_push_front(&list, &node1);
   linked_list_push_front(&list, &node2);
   CHECK_ASSERTION_FAILED(linked_list_push_front(&list, &node1));
}

TEST(linked_list, PushFront)
{
   linked_list_push_front(&list, &node1);
   CHECK(1 == linked_list_count(&list));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(linked_list_contains(&list, &node1));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(!linked_list_contains(&list, &node3));

   linked_list_push_front(&list, &node2);
   CHECK(2 == linked_list_count(&list));
   CHECK(&node2 == linked_list_at(&list, 0));
   CHECK(&node1 == linked_list_at(&list, 1));
   CHECK(linked_list_contains(&list, &node1));
   CHECK(linked_list_contains(&list, &node2));
   CHECK(!linked_list_contains(&list, &node3));

   linked_list_push_front(&list, &node3);
   CHECK(3 == linked_list_count(&list));
   CHECK(&node3 == linked_list_at(&list, 0));
   CHECK(&node2 == linked_list_at(&list, 1));
   CHECK(&node1 == linked_list_at(&list, 2));
   CHECK(linked_list_contains(&list, &node1));
   CHECK(linked_list_contains(&list, &node2));
   CHECK(linked_list_contains(&list, &node3));
}

TEST(linked_list, PushBack_Null_List)
{
   CHECK_ASSERTION_FAILED(linked_list_push_back(NULL, &node1));
}

TEST(linked_list, PushBack_Null_Node)
{
   CHECK_ASSERTION_FAILED(linked_list_push_back(&list, NULL));
}

TEST(linked_list, PushBack_Already_In_List)
{
   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);
   CHECK_ASSERTION_FAILED(linked_list_push_back(&list, &node1));
}

TEST(linked_list, PushBack)
{
   linked_list_push_back(&list, &node1);
   CHECK(1 == linked_list_count(&list));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(linked_list_contains(&list, &node1));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(!linked_list_contains(&list, &node3));

   linked_list_push_back(&list, &node2);
   CHECK(2 == linked_list_count(&list));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node2 == linked_list_at(&list, 1));
   CHECK(linked_list_contains(&list, &node1));
   CHECK(linked_list_contains(&list, &node2));
   CHECK(!linked_list_contains(&list, &node3));

   linked_list_push_back(&list, &node3);
   CHECK(3 == linked_list_count(&list));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node2 == linked_list_at(&list, 1));
   CHECK(&node3 == linked_list_at(&list, 2));
   CHECK(linked_list_contains(&list, &node1));
   CHECK(linked_list_contains(&list, &node2));
   CHECK(linked_list_contains(&list, &node3));
}

TEST(linked_list, PopFront_Null_List)
{
   CHECK_ASSERTION_FAILED(linked_list_pop_front(NULL));
}

TEST(linked_list, PopFront_Empty)
{
   CHECK_ASSERTION_FAILED(linked_list_pop_front(&list));
}

TEST(linked_list, PopFront)
{
   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);
   linked_list_push_back(&list, &node3);

   CHECK(&node1 == linked_list_pop_front(&list));
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(linked_list_contains(&list, &node2));
   CHECK(linked_list_contains(&list, &node3));

   CHECK(&node2 == linked_list_pop_front(&list));
   CHECK(1 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(linked_list_contains(&list, &node3));

   CHECK(&node3 == linked_list_pop_front(&list));
   CHECK(0 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(!linked_list_contains(&list, &node3));
}

TEST(linked_list, PopBack_Null_List)
{
   CHECK_ASSERTION_FAILED(linked_list_pop_back(NULL));
}

TEST(linked_list, PopBack_Empty)
{
   CHECK_ASSERTION_FAILED(linked_list_pop_back(&list));
}

TEST(linked_list, PopBack)
{
   linked_list_push_front(&list, &node1);
   linked_list_push_front(&list, &node2);
   linked_list_push_front(&list, &node3);

   CHECK(&node1 == linked_list_pop_back(&list));
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(linked_list_contains(&list, &node2));
   CHECK(linked_list_contains(&list, &node3));

   CHECK(&node2 == linked_list_pop_back(&list));
   CHECK(1 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(linked_list_contains(&list, &node3));

   CHECK(&node3 == linked_list_pop_back(&list));
   CHECK(0 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(!linked_list_contains(&list, &node3));
}

TEST(linked_list, Insert_Null_List)
{
   CHECK_ASSERTION_FAILED(linked_list_insert(NULL, &node1, 0));
}

TEST(linked_list, Insert_Null_Element)
{
   CHECK_ASSERTION_FAILED(linked_list_insert(&list, NULL, 0));
}

TEST(linked_list, Insert_Out_Of_Range)
{
   CHECK_ASSERTION_FAILED(linked_list_insert(&list, &node1, 1));
}

TEST(linked_list, Insert_Already_In_List)
{
   linked_list_insert(&list, &node1, 0);
   linked_list_insert(&list, &node2, 1);
   CHECK_ASSERTION_FAILED(linked_list_insert(&list, &node1, 1));
}

TEST(linked_list, Insert_Empty)
{
   linked_list_insert(&list, &node1, 0);
   CHECK(1 == linked_list_count(&list));
   CHECK(&node1 == linked_list_at(&list, 0));
}

TEST(linked_list, Insert_Front)
{
   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);

   linked_list_insert(&list, &node3, 0);

   CHECK(3 == linked_list_count(&list));
   CHECK(&node3 == linked_list_at(&list, 0));
   CHECK(&node1 == linked_list_at(&list, 1));
   CHECK(&node2 == linked_list_at(&list, 2));
}

TEST(linked_list, Insert_Middle)
{
   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);

   linked_list_insert(&list, &node3, 1);

   CHECK(3 == linked_list_count(&list));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node3 == linked_list_at(&list, 1));
   CHECK(&node2 == linked_list_at(&list, 2));
}

TEST(linked_list, Insert_Back)
{
   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);

   linked_list_insert(&list, &node3, 2);

   CHECK(3 == linked_list_count(&list));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node2 == linked_list_at(&list, 1));
   CHECK(&node3 == linked_list_at(&list, 2));
}

TEST(linked_list, Remove_Null_List)
{
   CHECK_ASSERTION_FAILED(linked_list_remove(NULL, 0));
}

TEST(linked_list, Remove_Null_Node)
{
   CHECK_ASSERTION_FAILED(linked_list_remove(&list, NULL));
}

TEST(linked_list, Remove_Node_Not_In_List)
{
   // This is allowed, should not uassert
   linked_list_remove(&list, &node1);
}

TEST(linked_list, Remove_Front)
{
   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);
   linked_list_push_back(&list, &node3);

   linked_list_remove(&list, &node1);
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(&node2 == linked_list_at(&list, 0));
   CHECK(&node3 == linked_list_at(&list, 1));
}

TEST(linked_list, Remove_Middle)
{
   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);
   linked_list_push_back(&list, &node3);

   linked_list_remove(&list, &node2);
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node3 == linked_list_at(&list, 1));
}

TEST(linked_list, Remove_Back)
{
   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);
   linked_list_push_back(&list, &node3);

   linked_list_remove(&list, &node3);
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node3));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node2 == linked_list_at(&list, 1));
}

TEST(linked_list, RemoveAt_Null_List)
{
   linked_list_push_back(&list, &node1);

   CHECK_ASSERTION_FAILED(linked_list_remove_at(NULL, 0));
}

TEST(linked_list, RemoveAt_Out_Of_Range)
{
   CHECK_ASSERTION_FAILED(linked_list_remove_at(&list, 0));

   linked_list_push_back(&list, &node1);

   CHECK_ASSERTION_FAILED(linked_list_remove_at(NULL, 1));
}

TEST(linked_list, RemoveAt_Front)
{
   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);
   linked_list_push_back(&list, &node3);

   linked_list_remove_at(&list, 0);
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(&node2 == linked_list_at(&list, 0));
   CHECK(&node3 == linked_list_at(&list, 1));
}

TEST(linked_list, RemoveAt_Middle)
{
   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);
   linked_list_push_back(&list, &node3);

   linked_list_remove_at(&list, 1);
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node3 == linked_list_at(&list, 1));
}

TEST(linked_list, RemoveAt_Back)
{
   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);
   linked_list_push_back(&list, &node3);

   linked_list_remove_at(&list, 2);
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node3));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node2 == linked_list_at(&list, 1));
}

static bool ForEach_Mock(linked_list_node_t *node, void *context, const size_t index)
{
   return mock().actualCall("ForEach_Mock")
      .withParameter("node", node)
      .withParameter("context", context)
      .withParameter("index", (int)index)
      .returnValue().getIntValue();
}

TEST(linked_list, ForEach_Null_List)
{
   CHECK_ASSERTION_FAILED(linked_list_for_each(NULL, ForEach_Mock, (void *)&context));
}

TEST(linked_list, ForEach_Null_Function)
{
   CHECK_ASSERTION_FAILED(linked_list_for_each(&list, NULL, (void *)&context));
}

TEST(linked_list, ForEach_Null_Context)
{
   // Should NOT assert, NULL context is allowed
   linked_list_for_each(&list, ForEach_Mock, NULL);
}

TEST(linked_list, ForEach_Empty)
{
   // Mock will puke if we call the for each function, success means no calls
   linked_list_for_each(&list, ForEach_Mock, (void *)&context);
}

IGNORE_TEST(linked_list, ForEach_VisitAll)
{
   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);
   linked_list_push_back(&list, &node3);

   mock().expectOneCall("ForEach_Mock")
      .withParameter("node", &node1)
      .withParameter("context", (void *)&context)
      .withParameter("index", 0)
      .andReturnValue(true);

   mock().expectOneCall("ForEach_Mock")
      .withParameter("node", &node2)
      .withParameter("context", (void *)&context)
      .withParameter("index", 1)
      .andReturnValue(true);

   mock().expectOneCall("ForEach_Mock")
      .withParameter("node", &node3)
      .withParameter("context", (void *)&context)
      .withParameter("index", 2)
      .andReturnValue(true);

   linked_list_for_each(&list, ForEach_Mock, (void *)&context);
}

IGNORE_TEST(linked_list, ForEach_VisitSome)
{
   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);
   linked_list_push_back(&list, &node3);

   mock().expectOneCall("ForEach_Mock")
      .withParameter("node", &node1)
      .withParameter("context", (void *)&context)
      .withParameter("index", 0)
      .andReturnValue(true);

   mock().expectOneCall("ForEach_Mock")
      .withParameter("node", &node2)
      .withParameter("context", (void *)&context)
      .withParameter("index", 1)
      .andReturnValue(false);

   linked_list_for_each(&list, ForEach_Mock, (void *)&context);

   mock().expectOneCall("ForEach_Mock")
      .withParameter("node", &node1)
      .withParameter("context", (void *)&context)
      .withParameter("index", 0)
      .andReturnValue(false);

   linked_list_for_each(&list, ForEach_Mock, (void *)&context);
}

typedef struct
{
   linked_list_t *list;
   linked_list_node_t *nodeToRemove;
} for_each_mock_with_removal_context;

static bool ForEach_MockWithRemoval(linked_list_node_t *node, void *_context, const size_t index)
{
   REINTERPRET(context, _context, for_each_mock_with_removal_context *);

   if(node == context->nodeToRemove)
   {
      linked_list_remove(context->list, context->nodeToRemove);

      // Blow away the nodeToRemove to simulate the fact that it's now out of our control and can
      // change under our feet
      context->nodeToRemove->next = NULL;
   }

   return mock().actualCall("ForEach_MockWithRemoval")
      .withParameter("node", node)
      .withParameter("context", context)
      .withParameter("index", (int)index)
      .returnValue().getIntValue();
}

IGNORE_TEST(linked_list, ForEach_Unsubscribe_RemovalDuringCallbackDoesNotPreventOtherNodesFromBeingVisited)
{
   for_each_mock_with_removal_context context =
      {
         &list, &node2
      };

   linked_list_push_back(&list, &node1);
   linked_list_push_back(&list, &node2);
   linked_list_push_back(&list, &node3);

   mock().expectOneCall("ForEach_MockWithRemoval")
      .withParameter("node", &node1)
      .withParameter("context", (void *)&context)
      .withParameter("index", 0)
      .andReturnValue(true);

   mock().expectOneCall("ForEach_MockWithRemoval")
      .withParameter("node", &node2)
      .withParameter("context", (void *)&context)
      .withParameter("index", 1)
      .andReturnValue(true);

   mock().expectOneCall("ForEach_MockWithRemoval")
      .withParameter("node", &node3)
      .withParameter("context", (void *)&context)
      .withParameter("index", 2)
      .andReturnValue(true);

   linked_list_for_each(&list, ForEach_MockWithRemoval, &context);
}

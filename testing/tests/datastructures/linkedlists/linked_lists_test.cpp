
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

TEST_GROUP(linked_list_init){};

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

TEST(linked_list, At_Out_Of_Range)
{
   CHECK_ASSERTION_FAILED(linked_list_at(&list, 0));

   linked_list_pushFront(&list, &node1);

   CHECK_ASSERTION_FAILED(linked_list_at(&list, 1));
}

TEST(linked_list, IndexOf_Not_In_List)
{
   linked_list_pushFront(&list, &node1);

   CHECK_ASSERTION_FAILED(linked_list_indexOf(&list, &node2));
}

TEST(linked_list, IndexOf)
{
   linked_list_pushFront(&list, &node1);
   CHECK(0 == linked_list_indexOf(&list, &node1));

   linked_list_pushFront(&list, &node2);
   CHECK(0 == linked_list_indexOf(&list, &node2));
   CHECK(1 == linked_list_indexOf(&list, &node1));

   linked_list_pushFront(&list, &node3);
   CHECK(0 == linked_list_indexOf(&list, &node3));
   CHECK(1 == linked_list_indexOf(&list, &node2));
   CHECK(2 == linked_list_indexOf(&list, &node1));
}

TEST(linked_list, PushFront_Already_In_List)
{
   linked_list_pushFront(&list, &node1);
   linked_list_pushFront(&list, &node2);
   CHECK_ASSERTION_FAILED(linked_list_pushFront(&list, &node1));
}

TEST(linked_list, PushFront)
{
   linked_list_pushFront(&list, &node1);
   CHECK(1 == linked_list_count(&list));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(linked_list_contains(&list, &node1));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(!linked_list_contains(&list, &node3));

   linked_list_pushFront(&list, &node2);
   CHECK(2 == linked_list_count(&list));
   CHECK(&node2 == linked_list_at(&list, 0));
   CHECK(&node1 == linked_list_at(&list, 1));
   CHECK(linked_list_contains(&list, &node1));
   CHECK(linked_list_contains(&list, &node2));
   CHECK(!linked_list_contains(&list, &node3));

   linked_list_pushFront(&list, &node3);
   CHECK(3 == linked_list_count(&list));
   CHECK(&node3 == linked_list_at(&list, 0));
   CHECK(&node2 == linked_list_at(&list, 1));
   CHECK(&node1 == linked_list_at(&list, 2));
   CHECK(linked_list_contains(&list, &node1));
   CHECK(linked_list_contains(&list, &node2));
   CHECK(linked_list_contains(&list, &node3));
}

TEST(linked_list, PushBack_Already_In_List)
{
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);
   CHECK_ASSERTION_FAILED(linked_list_pushBack(&list, &node1));
}

TEST(linked_list, PushBack)
{
   linked_list_pushBack(&list, &node1);
   CHECK(1 == linked_list_count(&list));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(linked_list_contains(&list, &node1));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(!linked_list_contains(&list, &node3));

   linked_list_pushBack(&list, &node2);
   CHECK(2 == linked_list_count(&list));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node2 == linked_list_at(&list, 1));
   CHECK(linked_list_contains(&list, &node1));
   CHECK(linked_list_contains(&list, &node2));
   CHECK(!linked_list_contains(&list, &node3));

   linked_list_pushBack(&list, &node3);
   CHECK(3 == linked_list_count(&list));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node2 == linked_list_at(&list, 1));
   CHECK(&node3 == linked_list_at(&list, 2));
   CHECK(linked_list_contains(&list, &node1));
   CHECK(linked_list_contains(&list, &node2));
   CHECK(linked_list_contains(&list, &node3));
}

TEST(linked_list, PopFront_Empty)
{
   CHECK_ASSERTION_FAILED(linked_list_popFront(&list));
}

TEST(linked_list, PopFront)
{
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);
   linked_list_pushBack(&list, &node3);

   CHECK(&node1 == linked_list_popFront(&list));
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(linked_list_contains(&list, &node2));
   CHECK(linked_list_contains(&list, &node3));

   CHECK(&node2 == linked_list_popFront(&list));
   CHECK(1 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(linked_list_contains(&list, &node3));

   CHECK(&node3 == linked_list_popFront(&list));
   CHECK(0 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(!linked_list_contains(&list, &node3));
}

TEST(linked_list, PopBack_Empty)
{
   CHECK_ASSERTION_FAILED(linked_list_popBack(&list));
}

TEST(linked_list, PopBack)
{
   linked_list_pushFront(&list, &node1);
   linked_list_pushFront(&list, &node2);
   linked_list_pushFront(&list, &node3);

   CHECK(&node1 == linked_list_popBack(&list));
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(linked_list_contains(&list, &node2));
   CHECK(linked_list_contains(&list, &node3));

   CHECK(&node2 == linked_list_popBack(&list));
   CHECK(1 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(linked_list_contains(&list, &node3));

   CHECK(&node3 == linked_list_popBack(&list));
   CHECK(0 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(!linked_list_contains(&list, &node3));
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
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);

   linked_list_insert(&list, &node3, 0);

   CHECK(3 == linked_list_count(&list));
   CHECK(&node3 == linked_list_at(&list, 0));
   CHECK(&node1 == linked_list_at(&list, 1));
   CHECK(&node2 == linked_list_at(&list, 2));
}

TEST(linked_list, Insert_Middle)
{
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);

   linked_list_insert(&list, &node3, 1);

   CHECK(3 == linked_list_count(&list));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node3 == linked_list_at(&list, 1));
   CHECK(&node2 == linked_list_at(&list, 2));
}

TEST(linked_list, Insert_Back)
{
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);

   linked_list_insert(&list, &node3, 2);

   CHECK(3 == linked_list_count(&list));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node2 == linked_list_at(&list, 1));
   CHECK(&node3 == linked_list_at(&list, 2));
}

TEST(linked_list, Remove_Node_Not_In_List)
{
   // This is allowed, should not uassert
   linked_list_remove(&list, &node1);
}

TEST(linked_list, Remove_Front)
{
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);
   linked_list_pushBack(&list, &node3);

   linked_list_remove(&list, &node1);
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(&node2 == linked_list_at(&list, 0));
   CHECK(&node3 == linked_list_at(&list, 1));
}

TEST(linked_list, Remove_Middle)
{
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);
   linked_list_pushBack(&list, &node3);

   linked_list_remove(&list, &node2);
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node3 == linked_list_at(&list, 1));
}

TEST(linked_list, Remove_Back)
{
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);
   linked_list_pushBack(&list, &node3);

   linked_list_remove(&list, &node3);
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node3));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node2 == linked_list_at(&list, 1));
}

TEST(linked_list, RemoveAt_Out_Of_Range)
{
   CHECK_ASSERTION_FAILED(linked_list_removeAt(&list, 0));

   linked_list_pushBack(&list, &node1);

   CHECK_ASSERTION_FAILED(linked_list_removeAt(&list, 1));
}

TEST(linked_list, RemoveAt_Front)
{
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);
   linked_list_pushBack(&list, &node3);

   linked_list_removeAt(&list, 0);
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node1));
   CHECK(&node2 == linked_list_at(&list, 0));
   CHECK(&node3 == linked_list_at(&list, 1));
}

TEST(linked_list, RemoveAt_Middle)
{
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);
   linked_list_pushBack(&list, &node3);

   linked_list_removeAt(&list, 1);
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node2));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node3 == linked_list_at(&list, 1));
}

TEST(linked_list, RemoveAt_Back)
{
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);
   linked_list_pushBack(&list, &node3);

   linked_list_removeAt(&list, 2);
   CHECK(2 == linked_list_count(&list));
   CHECK(!linked_list_contains(&list, &node3));
   CHECK(&node1 == linked_list_at(&list, 0));
   CHECK(&node2 == linked_list_at(&list, 1));
}

TEST(linked_list, ForEach_ShouldAllowEmptyLists)
{
   linked_list_forEach(&list, linked_list_node_t, node, {
      IGNORE(node);
      FAIL("There are no nodes in the list");
   });
}

TEST(linked_list, ForEach_ShouldVisitAllNodes)
{
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);
   linked_list_pushBack(&list, &node3);

   mock().expectOneCall("ForEach").withParameter("node", &node1);
   mock().expectOneCall("ForEach").withParameter("node", &node2);
   mock().expectOneCall("ForEach").withParameter("node", &node3);

   linked_list_forEach(&list, linked_list_node_t, node, {
      mock().actualCall("ForEach").withParameter("node", node);
   });
}

TEST(linked_list, ForEach_ShouldBeAbleToBreakBeforeTheFullListHasBeenVisited)
{
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);
   linked_list_pushBack(&list, &node3);

   mock().expectOneCall("ForEach").withParameter("node", &node1);
   mock().expectOneCall("ForEach").withParameter("node", &node2);

   linked_list_forEach(&list, linked_list_node_t, node, {
      mock().actualCall("ForEach").withParameter("node", node);

      if(node == &node2)
      {
         break;
      }
   });
}

TEST(linked_list, ForEach_ShouldAllowTheCurrentNodeToRemovedDuringIteration)
{
   linked_list_pushBack(&list, &node1);
   linked_list_pushBack(&list, &node2);
   linked_list_pushBack(&list, &node3);

   mock().expectOneCall("ForEach").withParameter("node", &node1);
   mock().expectOneCall("ForEach").withParameter("node", &node2);
   mock().expectOneCall("ForEach").withParameter("node", &node3);

   linked_list_forEach(&list, linked_list_node_t, node, {
      if(node == &node2)
      {
         linked_list_remove(&list, node);

         // Blow away the current node to simulate the memory being reused after being removed
         node->_private.next = NULL;
      }

      mock().actualCall("ForEach").withParameter("node", node);
   });
}

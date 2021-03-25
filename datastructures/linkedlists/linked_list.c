/*!
 * @file
 * @brief description
 *
 */

#include <stddef.h>
#include <stdbool.h>
#include "linked_list.h"
#include "uassert.h"

void linked_list_init(linked_list_t *list)
{
   list->_private.head = NULL;
}

size_t linked_list_count(const linked_list_t *list)
{
   linked_list_node_t *current = list->_private.head;
   size_t count = 0;

   while(current)
   {
      current = current->_private.next;
      count++;
   }

   return count;
}

linked_list_node_t *linked_list_at(const linked_list_t *list, const size_t index)
{
   linked_list_node_t *current = list->_private.head;
   uassert(current);

   for(size_t i = 0; i < index; i++)
   {
      current = current->_private.next;
      uassert(current);
   }

   return current;
}

size_t linked_list_indexOf(const linked_list_t *list, const linked_list_node_t *node)
{
   linked_list_node_t *current = list->_private.head;
   size_t index = 0;

   while(current)
   {
      if(current == node)
      {
         return index;
      }

      current = current->_private.next;
      index++;
   }

   uassert(!"node not in the list!");
   return 0;
}

bool linked_list_contains(const linked_list_t *list, const linked_list_node_t *node)
{
   linked_list_node_t *current = list->_private.head;

   if(current == node)
   {
      return true;
   }

   while(current)
   {
      current = (current->_private.next);

      if(current == node)
      {
         return true;
      }
   }

   return false;
}

void linked_list_pushFront(linked_list_t *list, linked_list_node_t *node)
{
   uassert(!linked_list_contains(list, node));

   node->_private.next = list->_private.head;
   list->_private.head = node;
}

void linked_list_pushBack(linked_list_t *list, linked_list_node_t *node)
{
   uassert(!linked_list_contains(list, node));

   linked_list_node_t *current = list->_private.head;

   node->_private.next = NULL;

   if(current)
   {
      while(current->_private.next)
      {
         current = current->_private.next;
      }

      current->_private.next = node;
   }
   else
   {
      list->_private.head = node;
   }
}

void linked_list_insert(linked_list_t *list, linked_list_node_t *node, size_t index)
{
   uassert(!linked_list_contains(list, node));

   if(index > 0)
   {
      linked_list_node_t *before = linked_list_at(list, index - 1);
      node->_private.next = before->_private.next;
      before->_private.next = node;
   }
   else
   {
      linked_list_pushFront(list, node);
   }
}

linked_list_node_t *linked_list_popFront(linked_list_t *list)
{
   uassert(list->_private.head);

   linked_list_node_t *popped = list->_private.head;
   list->_private.head = list->_private.head->_private.next;

   return popped;
}

linked_list_node_t *linked_list_popBack(linked_list_t *list)
{
   uassert(list->_private.head);

   linked_list_node_t *popped;
   linked_list_node_t *current = list->_private.head;

   if(current->_private.next)
   {
      while(current->_private.next->_private.next)
      {
         current = current->_private.next;
      }

      popped = current->_private.next;
      current->_private.next = NULL;
   }
   else
   {
      popped = list->_private.head;
      list->_private.head = NULL;
   }

   return popped;
}

void linked_list_removeAt(linked_list_t *list, const size_t index)
{
   linked_list_node_t *previous = NULL;
   linked_list_node_t *current = list->_private.head;

   for(size_t i = 0; i < index; i++)
   {
      uassert(current);
      previous = current;
      current = current->_private.next;
   }

   uassert(current);

   if(previous)
   {
      previous->_private.next = current->_private.next;
   }
   else
   {
      list->_private.head = current->_private.next;
   }
}

void linked_list_remove(linked_list_t *list, linked_list_node_t *node)
{
   if(list->_private.head == node)
   {
      list->_private.head = node->_private.next;
   }
   else
   {
      linked_list_node_t *current = list->_private.head;

      while(current)
      {
         if(current->_private.next == node)
         {
            current->_private.next = node->_private.next;
            break;
         }

         current = current->_private.next;
      }
   }
}

void linked_list_iterator_init(linked_list_iterator_t *instance, linked_list_t *list)
{
   instance->_private.current = list->_private.head;
}

linked_list_node_t *linked_list_iterator_next(linked_list_iterator_t *instance)
{
   if(!instance->_private.current)
   {
      return NULL;
   }

   linked_list_node_t *item = instance->_private.current;
   instance->_private.current = instance->_private.current->_private.next;
   return item;
}

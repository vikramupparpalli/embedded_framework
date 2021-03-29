/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */


#include <stddef.h>
#include <stdbool.h>
#include "linked_list.h"
#include "uassert.h"

void linked_list_init(linked_list_t *list)
{
   uassert(list);

   list->head = NULL;
}

size_t linked_list_count(const linked_list_t *list)
{
   size_t count = 0;
   linked_list_node_t *current;

   uassert(list);

   current = list->head;

   while(current)
   {
      current = current->next;
      count++;
   }

   return count;
}

linked_list_node_t * linked_list_at(const linked_list_t *list, const size_t index)
{
   size_t i;
   linked_list_node_t *current;

   uassert(list);

   current = list->head;
   uassert(current);

   for(i = 0; i < index; i++)
   {
      current = current->next;
      uassert(current);
   }

   return current;
}

size_t linked_list_index_of(const linked_list_t *list, const linked_list_node_t *node)
{
   linked_list_node_t *current;
   size_t index = 0;

   uassert(list);
   uassert(node);

   current = list->head;

   while(current)
   {
      if(current == node)
      {
         return index;
      }

      current = current->next;
      index++;
   }

   uassert(!"node not in the list!");
   return 0;
}

bool linked_list_contains(const linked_list_t *list, const linked_list_node_t *node)
{
   linked_list_node_t *current;

   uassert(list);
   uassert(node);

   current = list->head;

   if(current == node)
   {
      return true;
   }

   while(current)
   {
      current = (current->next);

      if(current == node)
      {
         return true;
      }
   }

   return false;
}

void linked_list_push_front(linked_list_t *list, linked_list_node_t *node)
{
   uassert(list);
   uassert(node);
   uassert(!linked_list_contains(list, node));

   node->next = list->head;
   list->head = node;
}

void linked_list_push_back(linked_list_t *list, linked_list_node_t *node)
{
   linked_list_node_t *current;

   uassert(list);
   uassert(node);
   uassert(!linked_list_contains(list, node));

   current = list->head;

   node->next = NULL;

   if(current)
   {
      while(current->next)
      {
         current = current->next;
      }

      current->next = node;
   }
   else
   {
      list->head = node;
   }
}

void linked_list_insert(linked_list_t *list, linked_list_node_t *node, size_t index)
{
   uassert(list);
   uassert(node);
   uassert(!linked_list_contains(list, node));

   if(index > 0)
   {
      linked_list_node_t *before = linked_list_at(list, index - 1);
      node->next = before->next;
      before->next = node;
   }
   else
   {
      linked_list_push_front(list, node);
   }
}

linked_list_node_t * linked_list_pop_front(linked_list_t *list)
{
   linked_list_node_t *popped;

   uassert(list);
   uassert(list->head);

   popped = list->head;
   list->head = list->head->next;

   return popped;
}

linked_list_node_t * linked_list_pop_back(linked_list_t *list)
{
   linked_list_node_t *popped;
   linked_list_node_t *current;

   uassert(list);
   uassert(list->head);

   current = list->head;

   if(current->next)
   {
      while(current->next->next)
      {
         current = current->next;
      }

      popped = current->next;
      current->next = NULL;
   }
   else
   {
      popped = list->head;
      list->head = NULL;
   }

   return popped;
}

void linked_list_remove_at(linked_list_t *list, const size_t index)
{
   size_t i;
   linked_list_node_t *previous = NULL;
   linked_list_node_t *current;

   uassert(list);

   current = list->head;

   for(i = 0; i < index; i++)
   {
      uassert(current);
      previous = current;
      current = current->next;
   }

   uassert(current);

   if(previous)
   {
      previous->next = current->next;
   }
   else
   {
      list->head = current->next;
   }
}

void linked_list_remove(linked_list_t *list, linked_list_node_t *node)
{
   uassert(list);
   uassert(node);

   if(list->head == node)
   {
      list->head = node->next;
   }
   else
   {
      linked_list_node_t *current = list->head;

      while(current)
      {
         if(current->next == node)
         {
            current->next = node->next;
            break;
         }

         current = current->next;
      }
   }
}

void linked_list_for_each(const linked_list_t *list, linked_list_for_each_call_t each, void *context)
{
   linked_list_node_t *current;
   size_t index = 0;

   uassert(list);
   uassert(each);

   current = list->head;

   while(current)
   {
      linked_list_node_t *next = current->next;

      if(!each(current, context, index))
      {
         break;
      }

      current = next;
      index++;
   }
}

/*!
 * @file
 * @brief
 *
 *
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct linked_list_node_t
{
   struct
   {
      struct linked_list_node_t *next;
   } _private;
} linked_list_node_t;

typedef struct
{
   struct
   {
      linked_list_node_t *head;
   } _private;
} linked_list_t;

typedef struct
{
   struct
   {
      linked_list_node_t *current;
   } _private;
} linked_list_iterator_t;


void linked_list_init(linked_list_t *list);

size_t linked_list_count(const linked_list_t *list);

linked_list_node_t *linked_list_at(const linked_list_t *list, const size_t index);

size_t linked_list_indexOf(const linked_list_t *list, const linked_list_node_t *node);

bool linked_list_contains(const linked_list_t *list, const linked_list_node_t *node);

void linked_list_pushFront(linked_list_t *list, linked_list_node_t *node);

void linked_list_pushBack(linked_list_t *list, linked_list_node_t *node);

void linked_list_insert(linked_list_t *list, linked_list_node_t *node, size_t index);

linked_list_node_t *linked_list_popFront(linked_list_t *list);

linked_list_node_t *linked_list_popBack(linked_list_t *list);

void linked_list_remove(linked_list_t *list, linked_list_node_t *node);

void linked_list_removeAt(linked_list_t *list, const size_t index);

void linked_list_iterator_init(linked_list_iterator_t *instance, linked_list_t *list);

linked_list_node_t *linked_list_iterator_next(linked_list_iterator_t *instance);

#define linked_list_forEach(_list, _type, _item, ...)          \
   do                                                         \
   {                                                          \
      linked_list_iterator_t _it;                               \
      linked_list_iterator_init(&_it, _list);                   \
      _type *_item;                                           \
      while((_item = (_type *)linked_list_iterator_next(&_it))) \
      {                                                       \
         __VA_ARGS__                                          \
      }                                                       \
   } while(0)

#endif

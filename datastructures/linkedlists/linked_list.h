/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#ifndef linked_list_h
#define linked_list_h

#include <stdbool.h>
#include <stddef.h>
typedef struct linked_list_node_t
{
   struct linked_list_node_t *next;
} linked_list_node_t;

typedef bool (*linked_list_for_each_call_t)(linked_list_node_t *node, void *context, const size_t index);

typedef struct LinkedList
{
   linked_list_node_t *head;
} linked_list_t;

void linked_list_init(linked_list_t *list);
size_t linked_list_count(const linked_list_t *list);
linked_list_node_t * linked_list_at(const linked_list_t *list, const size_t index);
size_t linked_list_index_of(const linked_list_t *list, const linked_list_node_t *node);
bool linked_list_contains(const linked_list_t *list, const linked_list_node_t *node);
void linked_list_push_front(linked_list_t *list, linked_list_node_t *node);
void linked_list_push_back(linked_list_t *list, linked_list_node_t *node);
void linked_list_insert(linked_list_t *list, linked_list_node_t *node, size_t index);
linked_list_node_t * linked_list_pop_front(linked_list_t *list);
linked_list_node_t * linked_list_pop_back(linked_list_t *list);
void linked_list_remove(linked_list_t *list, linked_list_node_t *node);
void linked_list_remove_at(linked_list_t *list, const size_t index);
void linked_list_for_each(const linked_list_t *list, linked_list_for_each_call_t each, void *context);

#endif

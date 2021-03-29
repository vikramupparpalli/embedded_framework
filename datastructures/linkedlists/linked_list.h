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

/*!
 * A linked list node.  Struct members should be considered private.
 * @note This will generally be used within another struct to make that struct a linked list node.
 */
typedef struct linked_list_node_t
{
   struct linked_list_node_t *next;
} linked_list_node_t;

/*!
 * Function called at each node when using ForEach()
 * @param node Current node.
 * @param context ForEach context.
 * @param index Node index.
 * @return True if iteration should continue, false otherwise.
 */
typedef bool (*linked_list_for_each_call_t)(linked_list_node_t *node, void *context, const size_t index);

/*!
 * A singly-linked list.  Struct members should be considered private.
 */
typedef struct LinkedList
{
   linked_list_node_t *head;
} linked_list_t;

/*!
 * Initialize a linked list to an empty list.
 * @pre list != NULL
 * @param list The list.
 */
void linked_list_init(linked_list_t *list);

/*!
 * Count the nodes in a list.
 * @pre list != NULL
 * @pre Initialized(list)
 * @param list The list.
 * @returns The number of nodes in the list.
 */
size_t linked_list_count(const linked_list_t *list);

/*!
 * Get the node at a specific location in a list.
 * @pre list != NULL
 * @pre Initialized(list)
 * @pre index < Count(list)
 * @param list The list.
 * @param index The specified index.
 * @returns The node at the specified location..
 */
linked_list_node_t * linked_list_at(const linked_list_t *list, const size_t index);

/*!
 * Get the index of a node within a list.
 * @pre list != NULL
 * @pre node != NULL
 * @pre Initialized(list)
 * @pre Contains(list, node)
 * @param list The list..
 * @param node The node..
 * @returns The index of the node within the list.
 */
size_t linked_list_index_of(const linked_list_t *list, const linked_list_node_t *node);

/*!
 * Determine whether a node is contained in a list.
 * @pre list != NULL
 * @pre node != NULL
 * @pre Initialized(list)
 * @param list The list.
 * @param node The node.
 * @returns True if the node is contained in the list, false otherwise.
 */bool linked_list_contains(const linked_list_t *list, const linked_list_node_t *node);

/*!
 * Add a node to the front (head) of a list.
 * @pre list != NULL
 * @pre node != NULL
 * @pre Initialized(list)
 * @pre !Contains(list, node)
 * @param list The list.
 * @param node The node.
 */
void linked_list_push_front(linked_list_t *list, linked_list_node_t *node);

/*!
 * Add a node to the back (tail) of a list.
 * @pre list != NULL
 * @pre node != NULL
 * @pre Initialized(list)
 * @pre !Contains(list, node)
 * @param list The list.
 * @param node The node.
 */
void linked_list_push_back(linked_list_t *list, linked_list_node_t *node);

/*!
 * Add a node at the specified index in the list.
 * @pre list != NULL
 * @pre node != NULL
 * @pre Initialized(list)
 * @pre !Contains(list, node)
 * @pre index <= Count(list)
 * @param list The list.
 * @param node The node.
 */
void linked_list_insert(linked_list_t *list, linked_list_node_t *node, size_t index);

/*!
 * Remove a node from the front (head) of a list.
 * @pre list != NULL
 * @pre Initialized(list)
 * @pre Count(list) > 0
 * @param list The list.
 * @returns The removed node.
 */
linked_list_node_t * linked_list_pop_front(linked_list_t *list);

/*!
 * Remove a node from the back (tail) of a list.
 * @pre list != NULL
 * @pre Initialized(list)
 * @pre Count(list) > 0
 * @param list The list.
 * @returns The removed node.
 */
linked_list_node_t * linked_list_pop_back(linked_list_t *list);

/*!
 * Remove a specific node from a list.
 * @pre list != NULL
 * @pre node != NULL
 * @pre Initialized(list)
 * @param list The list.
 * @param node The node.
 */
void linked_list_remove(linked_list_t *list, linked_list_node_t *node);

/*!
 * Remove the node at a specific index from a list.
 * @pre list != NULL
 * @pre Initialized(list)
 * @pre index < Count(list)
 * @param list The list.
 * @param index The index.
 */
void linked_list_remove_at(linked_list_t *list, const size_t index);

/*!
 * Iterate through a list (front to back) and call a function for each node in the list.  More efficient than iterating manually.
 * @pre list != NULL
 * @pre each != NULL
 * @pre Initialized(list)
 * @param list The list.
 * @param each The function.
 * @param context Context passed for each function invocation.
 * @note If Each returns true then iteration continues, otherwise iteration terminates.
 */
void linked_list_for_each(const linked_list_t *list, linked_list_for_each_call_t each, void *context);

#endif

/*!
 * @file
 * @brief Action that clears a section of memory by setting its contents to 0. 
 *
 * Absolutely Non-Confidential - No rights reserved.
 */

#ifndef ACTION_CLEARMEMORY_H
#define ACTION_CLEARMEMORY_H

#include <stddef.h>
#include <stdio.h>
#include "action_interface.h"

typedef struct
{
   action_t interface;

   struct
   {
      void *pointer;
      size_t blockSize;
   } _private;
} action_clear_memory_t;

/*!
* @param instance
* @param pointer
* @param blockSize
*/
void action_clear_memory_initialization(action_clear_memory_t *instance, void *pointer, size_t blockSize);

#endif

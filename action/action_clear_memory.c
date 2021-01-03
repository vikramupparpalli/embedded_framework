/*!
 * @file
 * @brief
 *
 * Absolutely Non-Confidential - No rights reserved.
 */

#include <string.h>
#include "action_clear_memory.h"
#include "utilities.h"

static void run(action_t *_instance)
{
   REINTERPRET(instance, _instance, action_clear_memory_t *);

   memset(instance->_private.pointer, 0, instance->_private.blockSize);
}

static const action_interface_t api =
   { run };

void action_clear_memory_initialization(action_clear_memory_t *instance, void *pointer, size_t blockSize)
{
   instance->interface.api = &api;
   instance->_private.pointer = pointer;
   instance->_private.blockSize = blockSize;
}

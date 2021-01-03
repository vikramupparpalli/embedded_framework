/*!
 * @file
 * @brief Helpful testing utilities for working with memory.
 *
 * Absolutely Non-Confidential - No rights reserved.
 */

#ifndef MEMORYUTILS_H
#define MEMORYUTILS_H

#include <string.h>

// Note that this needs an object, not a reference
#define ASSUME_UNINITIALIZED(object) \
   memset(&(object), 0xA5, sizeof(object))

// Note that this needs an object, not a reference
#define ASSUME_UNINITIALIZED_VALUE(object, value) \
   memset(&(object), value, sizeof(object))

#endif

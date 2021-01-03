/*!
 * @file
 * @brief
 *
 * Absolutely Non-Confidential - No rights reserved.
 */

#include "action_null.h"

static void run(action_t *instance)
{
   (void)(instance);
}

static const action_interface_t api =
   { run };

action_t * action_null_get_pointer(void)
{
   static action_t instance;

   instance.api = &api;

   return &instance;
}

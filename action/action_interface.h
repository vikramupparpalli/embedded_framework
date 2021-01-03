/*!
 * @file
 * @brief description
 *
 * Absolutely Non-Confidential - No rights reserved.
 */

#ifndef ACTION_INTERFACE_H
#define ACTION_INTERFACE_H

struct action_interface_t;

typedef struct
{
   const struct action_interface_t *api;
} action_t;

typedef struct action_interface_t
{
   void (*Invoke)(action_t *instance);
} action_interface_t;

#define action_run(instance) \
   (instance)->api->Invoke((instance))

#define action_secure_run(instance) \
   if(instance){action_run(instance);}

#endif

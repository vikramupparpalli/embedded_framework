/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#ifndef I_TIMER_SOURCE_H
#define I_TIMER_SOURCE_H

#include <stdint.h>

typedef uint16_t timer_source_tick_count_t;

struct i_time_source_api_t;

typedef struct
{
   const struct i_time_source_api_t *api;
} i_time_source_t;

typedef struct i_time_source_api_t
{
   /*!
    * @param instance.
    * @return The current tick count.
    */
   timer_source_tick_count_t (*get_ticks)(i_time_source_t *instance);
} i_time_source_api_t;

#define time_source_get_ticks(instance) \
   (instance)->api->get_ticks((instance))

#endif

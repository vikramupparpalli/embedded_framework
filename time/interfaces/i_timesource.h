#ifndef I_TIME_SOURCE_H
#define I_TIME_SOURCE_H

#include <stdint.h>

/*!
 * Tick count.
 */
typedef uint16_t timesource_tick_count_t;

struct i_timesource_api_t;

/*!
 * Time source object.
 */
typedef struct
{
   /*!
    * Time source API used to interact with the time source object.
    */
   const struct i_timesource_api_t *api;
} i_timesource_t;

/*!
 * Interface for interacting with a timer.  API should be accessed using wrapper calls below.
 */
typedef struct i_timesource_api_t
{
   /*!
    * Get the current tick count from a time source.
    * @pre instance != NULL
    * @param instance The time source.
    * @return The current tick count.
    */
   timesource_tick_count_t (*get_ticks)(i_timesource_t *instance);
} i_timesource_api_t;

#define timesource_get_ticks(instance) \
   (instance)->api->get_ticks((instance))

#endif

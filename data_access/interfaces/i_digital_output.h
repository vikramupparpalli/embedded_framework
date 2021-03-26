/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#ifndef I_DIGITAL_OUTPUT_H
#define I_DIGITAL_OUTPUT_H

struct i_digital_output_api_t;

typedef struct
{
   const struct i_digital_output_api_t *api;
} i_digital_output_t;

typedef struct i_digital_output_api_t
{
   void (*write)(i_digital_output_t *instance, const bool state);
} i_digital_output_api_t;

#define digital_output_write(instance, state) \
   (instance)->api->write((instance), (state))

#endif

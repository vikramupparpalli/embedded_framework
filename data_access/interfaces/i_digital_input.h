/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#ifndef I_DIGITAL_INPUT_H
#define I_DIGITAL_INPUT_H

struct i_digital_input_api_t;

typedef struct
{
   const struct i_digital_input_api_t *api;
} i_digital_input_t;

typedef struct i_digital_input_api_t
{
   void (*read)(i_digital_input_t *instance);
} i_digital_input_api_t;

#define digital_output_read(instance) \
   (instance)->api->read((instance))

#endif

/*!
 * @file
 * @brief description
 *
 * Copyright KissMyAss - Confidential - No rights reserved.
 */

#ifndef I_INTERRUPT_H
#define I_INTERRUPT_H

#include "i_event.h"

typedef i_event_t i_interrupt_t;
typedef i_event_api_t i_interrupt_api_t;

#define interrupt_subscribe event_subscribe
#define interrupt_unsubscribe event_unsubscribe

#endif

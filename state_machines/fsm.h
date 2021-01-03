/*!
 * @file
 * @brief state machines
 *
 * i write bad code!!
 */

#ifndef FSM_H
#define FSM_H

enum
{

} fsm_state_t;

typedef struct
{
   uint8_t currentState;
} fsm_t;

void fsm_Init(fsm_t *instance, uint8_t initialState);

#endif

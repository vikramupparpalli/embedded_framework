/*!
 * @file
 * @brief Types Definition for this framework
 *
 * Absolutely Non-Confidential - No rights reserved.
 */

#ifndef CLTYPES_H
#define CLTYPES_H

#define ARM_NOP      __asm("NOP\n")

#define RET_SUCCESS           (     0x00 )    /* Successful */
#define RET_BAD_PARAM         (     0x01 )    /* One or more invalid parameters */
#define RET_INVALID_OBJECT    (     0x02 )    /* Invalid object specified */
#define RET_MEMORY            (     0x03 )    /* Memory related failure */
#define RET_LOCKED            (     0x04 )    /* Resource lock failure */
#define RET_EMPTY             (     0x05 )    /* No more objects available */
#define RET_BAD_DATA          (     0x06 )    /* Bad data received (CRC or other error check) */
#define RET_STARTED           (     0x07 )    /* Operation started, but not necessarily completed yet */
#define RET_FINISHED          (     0x08 )    /* Operation completed */
#define RET_CANCELED          (     0x09 )    /* Operation canceled */
#define RET_TIMEOUT           (     0x10 )    /* Operation timed out */
#define RET_INVALID_STATE     (     0x11 )    /* Operation not setup or is in an improper state */
#define RET_UNKNOWN           (0xFFFFFFFF)    /* Unknown failure */

#endif

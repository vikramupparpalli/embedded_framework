/*!
 @brief User-defined assert mechanism
 Absolutely Non-Confidential - No rights reserved.
 */

#ifndef UASSERT_TEST_H
#define UASSERT_TEST_H

extern "C"
{
#include "uassert.h"
}

#define CHECK_ASSERTION_FAILED(code) \
   uassert_ExpectAssertion(); \
   try { code; } catch(...) { } \
   CHECK(uassert_Asserted())

#define ShouldFailAssertionWhen(code) \
   uassert_ExpectAssertion(); \
   try { code; } catch(...) { } \
   CHECK(uassert_Asserted())

#define ShouldFailAssertion(code) \
   uassert_ExpectAssertion(); \
   try { code; } catch(...) { } \
   CHECK(uassert_Asserted())

#define CHECK_ASSERTION_PASSED(code) \
   uassert_ExpectAssertion(); \
   try { code; } catch(...) { } \
   CHECK(!uassert_Asserted())

extern void uassert_ExpectAssertion(void);
extern bool uassert_Asserted(void);

#endif

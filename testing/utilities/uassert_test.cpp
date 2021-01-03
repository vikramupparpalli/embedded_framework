/*!
 * @file
 * @brief User-defined assert implementation for TDD
 *
 * Absolutely Non-Confidential - No rights reserved.
 */

#include <stdexcept>
#include <sstream>
#include "uassert_test.h"

typedef struct
{
   bool asserted;
} Module_t;

static Module_t module;

extern "C" void __uassert_func(
   const char * fileName,
   const int lineNumber,
   const bool condition,
   const char *conditionString)
{
   (void) fileName;
   (void) lineNumber;
   (void) conditionString;

   if(!condition)
   {
      module.asserted = true;
      std::stringstream ss;
      ss << "\nFailed assertion:\n" << fileName << ":" << lineNumber << " " << conditionString << std::endl;
      throw ss.str();
   }
}

void uassert_ExpectAssertion(void)
{
   module.asserted = false;
}

bool uassert_Asserted(void)
{
   return module.asserted;
}

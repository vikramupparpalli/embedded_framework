/*!
 * @file
 * @brief TDD test runner.
 */

#include <iostream>
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestRegistry.h"
#include "CppUTestExt/MockSupportPlugin.h"

int main(int argc, char** argv)
{
   MockSupportPlugin mockPlugin;
   TestRegistry::getCurrentRegistry()->installPlugin(&mockPlugin);

   int result = 0;

   try
   {
      result = RUN_ALL_TESTS(argc, argv);
   }
   catch(std::string &s)
   {
      std::cout << s << std::endl;
      throw s;
   }

   return result;
}

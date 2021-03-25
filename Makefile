# Set this to @ to keep the makefile quiet
SILENCE ?= @

PROJECT_HOME_DIR ?= .
LIB_DIR ?= $(PROJECT_HOME_DIR)
LIB_TEST_DIR = $(LIB_DIR)/testing
LIB_TESTS_DIR = $(LIB_TEST_DIR)/tests

PROJECT_NAME ?= common_code
COMPONENT_NAME ?= $(PROJECT_NAME)

OUTPUT_DIR ?= $(PROJECT_HOME_DIR)/testing

CPPUTEST_LCOV_DIR = $(OUTPUT_DIR)/lcov
CPPUTEST_OBJS_DIR = $(OUTPUT_DIR)/build
CPPUTEST_LIB_DIR = $(CPPUTEST_OBJS_DIR)/lib/

TEST_TARGET = $(CPPUTEST_OBJS_DIR)/$(COMPONENT_NAME)_tests

CPPUTEST_HOME = $(LIB_TEST_DIR)/cpputest
CPP_PLATFORM ?= gcc

# Default to building applcommon and running applcommon tests
BUILD_LIB_SOURCE ?= Y
RUN_LIB_TESTS ?= Y

CPPUTEST_USE_EXTENSIONS = Y

ifeq ($(RELEASE), Y)
CPPUTEST_WARNINGFLAGS += -Werror
endif

ifndef CPPUTEST_WARNINGFLAGS
CPPUTEST_WARNINGFLAGS += -Wall
else
CPPUTEST_WARNINGFLAGS := $(addprefix -Wall , $(CPPUTEST_WARNINGFLAGS))
endif

CPPUTEST_CFLAGS += -std=gnu99

CPPUTEST_CFLAGS += -Wextra
CPPUTEST_CFLAGS += -Wstrict-prototypes
CPPUTEST_CFLAGS += -Werror=pointer-arith
CPPUTEST_CFLAGS += -Werror=missing-prototypes
CPPUTEST_CFLAGS += -Wfatal-errors
CPPUTEST_CFLAGS += -Wno-type-limits
CPPUTEST_CFLAGS += -Wno-unused-local-typedefs
CPPUTEST_CFLAGS += -Wno-unknown-warning-option
CPPUTEST_CFLAGS += -Wno-deprecated-declarations
CPPUTEST_CFLAGS += -Wno-nonportable-include-path
CPPUTEST_CFLAGS += -Wno-implicit-fallthrough
CPPUTEST_CFLAGS += -g -O0 --coverage
CPPUTEST_CPPFLAGS += -D__STDC_LIMIT_MACROS
CPPUTEST_CPPFLAGS += -Wno-unused-local-typedefs
CPPUTEST_CXXFLAGS += -fvisibility-inlines-hidden
CPPUTEST_LDFLAGS += -ftest-coverage
CPPUTEST_LDFLAGS += -fprofile-arcs
ifeq ($(shell uname),Linux)
	CPPUTEST_LDFLAGS += -Wl,-E
	CPPUTEST_CPPFLAGS+=-Wno-int-in-bool-context
endif

# Needed to compile Lua libs
LD_LIBRARIES += -lm -ldl

# This looks goofy, but it is needed to keep CppUTest's malloc/free, new/delete macros from blowing up STL
CPPUTEST_CXXFLAGS += -include $(LIB_TEST_DIR)/utilities/stl_includes.h
# Force include TestingUtils.h
CPPUTEST_CPPFLAGS += -include $(LIB_TEST_DIR)/utilities/testingutils.h

add_wildcard_suffix = $(addprefix $1,/*)
add_cwd_prefix = $(addprefix $(shell pwd)/,$1)
lcov_exclusion_list_from_src_dirs = $(foreach dir, $1, $(call add_wildcard_suffix,$(call add_cwd_prefix,$(dir))))

ifeq ($(BUILD_LIB_SOURCE), Y)
SRC_FILES += \

endif

ifeq ($(BUILD_LIB_SOURCE), Y)
LIB_SRC_DIRS = \
   $(LIB_DIR)/action \
   $(LIB_DIR)/algorithms \
   $(LIB_DIR)/datastructures/linkedlists \

SRC_DIRS += $(LIB_SRC_DIRS)

EXAMPLE_SRC_DIRS += \
	$(LIB_DIR)/examples
endif

# Tests for applcommon components
ifeq ($(RUN_LIB_TESTS), Y)
TEST_SRC_DIRS += \
	$(LIB_DIR)/action \
	$(LIB_DIR)/datastructures/linkedlists \
	$(EXAMPLE_SRC_DIRS)
endif

# Test helpers
ifeq ($(BUILD_LIB_SOURCE), Y)
TEST_SRC_DIRS += \
	$(LIB_TESTS_DIR)/action \
	$(LIB_TESTS_DIR)/datastructures/linkedlists \
	$(LIB_TEST_DIR)/utilities
endif

# Test runner
ifeq ($(BUILD_LIB_SOURCE), Y)
TEST_SRC_FILES += \
	$(LIB_TESTS_DIR)/run_all.cpp
else
TEST_SRC_FILES += \
	$(LIB_TESTS_DIR)/run_standalone.cpp
endif

INCLUDE_DIRS += \
	$(CPPUTEST_HOME)/include \
	$(LIB_DIR)/include \
	$(SRC_DIRS) \
	$(TEST_SRC_DIRS)

LCOV_EXCLUSION_LIST = $(subst /./,/,$(call add_wildcard_suffix,$(call add_cwd_prefix,$(LIB_TEST_DIR)/lua/lua53)))

ifeq ($(RUN_LIB_TESTS), N)
LCOV_EXCLUSION_LIST += $(call lcov_exclusion_list_from_src_dirs,$(LIB_SRC_DIRS))
endif

# Defer to CppUTest's build system to finish build
include $(CPPUTEST_HOME)/build/MakefileWorker.mk

# Automatically build CppUTest for current environment
$(CPPUTEST_HOME)/lib/libCppUTest.a: $(shell find $(CPPUTEST_HOME)/src)
	cd $(CPPUTEST_HOME) ; ./configure
	make -C $(CPPUTEST_HOME)

$(CPPUTEST_HOME)/lib/libCppUTestExt.a: $(CPPUTEST_HOME)/lib/libCppUTest.a

# Generate an LCOV report for all files included in the build
.PHONY: lcov_silent
lcov_silent: test
	$(SILENCE)rm -rf $(CPPUTEST_LCOV_DIR)
	$(SILENCE)mkdir -p $(CPPUTEST_LCOV_DIR)
	$(SILENCE)lcov -q -c -i -d $(CPPUTEST_OBJS_DIR) -o $(CPPUTEST_LCOV_DIR)/lcov_base.info -b .
	$(SILENCE)lcov -q --remove $(CPPUTEST_LCOV_DIR)/lcov_base.info $(LCOV_EXCLUSION_LIST) -o $(CPPUTEST_LCOV_DIR)/lcov_base.info
	$(SILENCE)lcov -q -c -d $(CPPUTEST_OBJS_DIR) -o $(CPPUTEST_LCOV_DIR)/lcov_test.info -b .
	$(SILENCE)lcov -q --remove $(CPPUTEST_LCOV_DIR)/lcov_test.info $(LCOV_EXCLUSION_LIST) -o $(CPPUTEST_LCOV_DIR)/lcov_test.info
	$(SILENCE)lcov -q -a $(CPPUTEST_LCOV_DIR)/lcov_base.info -a $(CPPUTEST_LCOV_DIR)/lcov_test.info -o $(CPPUTEST_LCOV_DIR)/lcov.info
	$(SILENCE)genhtml -q -o $(CPPUTEST_LCOV_DIR) $(CPPUTEST_LCOV_DIR)/lcov.info -p $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

.PHONY: lcov
lcov: lcov_silent
ifeq ($(UNAME_OS), $(LINUX_STR))
	$(SILENCE)x-www-browser `pwd`/$(CPPUTEST_LCOV_DIR)/index.html
endif
ifeq ($(UNAME_OS), $(MACOSX_STR))
	$(SILENCE)open `pwd`/$(CPPUTEST_LCOV_DIR)/index.html
endif

# Generate a "top ten" for complexity
.PHONY: pmccabe_summary
pmccabe_summary:
	$(SILENCE)pmccabe -vT $(SRC)
	$(SILENCE)pmccabe $(SRC) | sort -nr | head -10
	$(SILENCE)pmccabe -vT $(SRC) | grep Total | awk '{print "Complexity/LOC: " $$1/$$5}'
	$(SILENCE)pmccabe $(SRC) | awk '{sum+=$$3} END { print "LOC/function = ",sum/NR}'

# Generate a full complexity report
.PHONY: pmccabe_full
pmccabe_full:
	$(SILENCE)pmccabe -vT $(SRC)
	$(SILENCE)pmccabe $(SRC) | sort -nr
	$(SILENCE)pmccabe -vT $(SRC) | grep Total | awk '{print "Complexity/LOC: " $$1/$$5}'
	$(SILENCE)pmccabe $(SRC) | awk '{sum+=$$3} END { print "LOC/function = ",sum/NR}'

# By default generate just the "top ten"
.PHONY: pmccabe
pmccabe: pmccabe_summary

# Manually blow away CppUTest libs so that new libs will be built
.PHONY: upgrade
upgrade:
	rm -rf $(CPPUTEST_HOME)/lib

# This will clean up everything including CppUTest
.PHONY: distclean
distclean: clean upgrade
	make -C $(CPPUTEST_HOME) clean distclean

.PHONY: test_time_summary
test_time_summary: $(TEST_TARGET)
	$(RUN_TEST_TARGET) -v | grep TEST | sort -k4 -nr | head -n10

.PHONY: test_time
test_time: $(TEST_TARGET)
	$(RUN_TEST_TARGET) -v | grep TEST | sort -k4 -nr

.PHONY: verbose
verbose: $(TEST_TARGET)
	$(RUN_TEST_TARGET) -v

.PHONY: group
group: $(TEST_TARGET)
	$(RUN_TEST_TARGET) -g $(GROUP)

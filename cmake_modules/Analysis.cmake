#------------------------------------------------------------------------/
#
# Copyright (c) 2013 David Robin Cvetko
#
# MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the 
# "Software"), to deal in the Software without restriction, including 
# without limitation the rights to use, copy, modify, merge, publish, 
# distribute, sublicense, and/or sell copies of the Software, and to 
# permit persons to whom the Software is furnished to do so, subject to 
# the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#-----------------------------------------------------------------------*/

cmake_minimum_required (VERSION 2.8)

###########################################################################

enable_testing()
include(CTest)

set(CTEST_PROJECT_NAME ${CMAKE_PROJECT_NAME}-analysis)
message(STATUS "Enabling analysis module: ${CTEST_PROJECT_NAME}")

###########################################################################

#### Custom Build Type for Coverage
MACRO(coverage_flags)
    message(STATUS "Setting build flags for coverage")
    set(CMAKE_CXX_FLAGS_COVERAGE
        "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage"
        CACHE STRING "Flags used by C++ Compiler during coverage builds")
    set(CMAKE_EXE_LINKER_FLAGS_COVERAGE
        "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage -lgcov"
        CACHE STRING "Flags used for linking executables during coverage builds")
    set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE
        "${CMAKE_SHARED_LINKER_FLAGS_COVERAGE} -fprofile-arcs -ftest-coverage -lgcov"
        CACHE STRING "Flags used for linking shared libraries during coverage builds")
    mark_as_advanced(
        CMAKE_CXX_FLAGS_COVERAGE
        CMAKE_EXE_LINKER_FLAGS_COVERAGE
        CMAKE_SHARED_LINKER_FLAGS_COVERAGE
        )

    set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}"
        CACHE STRING "Choose the type of build"
        FORCE
        )
ENDMACRO()

###########################################################################

#### Do coverage builds when we are in a directory named *coverage*
MACRO(coverage_dir)
    if(CMAKE_BINARY_DIR MATCHES ".*coverage.*")
        message(STATUS "Setting build type to coverage")
        set(CMAKE_BUILD_TYPE coverage)
    endif()
ENDMACRO()

###########################################################################

#### Valgrind - Memcheck
MACRO(valgrind)
    message(STATUS "Setting memcheck command to valgrind/callgrind")
    set(CTEST_MEMORYCHECK_COMMAND "/usr/bin/valgrind")
    set(CTEST_MEMORYCHECK_COMMAND_OPTIONS "--tool=callgrind -v")
ENDMACRO()

###########################################################################

#### GCOV - Coverage
MACRO(gcov)
    message(STATUS "Setting coverage command to gcov")
    set(COVERAGE_COMMAND "/usr/bin/gcov")
ENDMACRO()

###########################################################################

#### cppcheck target
MACRO(cppcheck)
    message(STATUS "Adding analysis target: cppcheck")
    add_custom_target(cppcheck)
    set(CPPCHECK_FLAGS --enable=warning,performance,portability)
    add_custom_command(TARGET cppcheck
        COMMAND cppcheck ${CPPCHECK_FLAGS} ${CMAKE_SOURCE_DIR}
        )
ENDMACRO()

###########################################################################

# lcov targtes (clean + html info)
MACRO(lcov)
    message(STATUS "Adding testing/coverage targets: lcov-clean, lcov")
    add_custom_target(lcov-clean)
    add_custom_target(lcov)

    set(LCOV_DIR ${CMAKE_BINARY_DIR})
    set(LCOV_BASE ${CMAKE_SOURCE_DIR})
    set(LCOV_COVERAGE coverage.info)
    set(LCOV_FLAGS --capture --directory ${LCOV_DIR} --base-directory
        ${LCOV_BASE} --output-file ${LCOV_COVERAGE} --no-external)

    # Set the output directory of the HTML files here
    set(GENHTML_DIR coverage)
    set(GENHTML_FLAGS --output-directory ${GENHTML_DIR} --branch-coverage)

    add_custom_command(TARGET lcov-clean
        COMMAND lcov --zerocounters --directory ${LCOV_DIR}
        )
    add_custom_command(TARGET lcov
        COMMAND lcov ${LCOV_FLAGS}
        )
    add_custom_command(TARGET lcov
        COMMAND genhtml ${LCOV_COVERAGE} ${GENHTML_FLAGS}
        )
ENDMACRO()

###########################################################################

# rats target (sec analysis)
MACRO(rats)
    message(STATUS "Adding analysis target: RATS")
    add_custom_target(rats)
    add_custom_command(TARGET rats
        COMMAND rats ${CMAKE_SOURCE_DIR}
        )
ENDMACRO()

###########################################################################

# flawfinder target (mainly sec analysis)
MACRO(flawfinder)
    message(STATUS "Adding analysis target: flawfinder")
    add_custom_target(flawfinder)
    add_custom_command(TARGET flawfinder
    COMMAND flawfinder ${CMAKE_SOURCE_DIR}
    )
ENDMACRO()

###########################################################################

# "Main" -- Enable/Disable desired targets here
coverage_flags()
coverage_dir()
valgrind()
gcov()
cppcheck()
lcov()
rats()
flawfinder()

###########################################################################

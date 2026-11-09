cmake_minimum_required(VERSION 3.20)
project(census CXX)

set(CLANG_VERSION 23 CACHE STRING "Major version of clang the plugin targets")

find_package(LLVM REQUIRED CONFIG HINTS /usr/lib/llvm-${CLANG_VERSION} NO_DEFAULT_PATH)
find_package(Clang REQUIRED CONFIG HINTS /usr/lib/llvm-${CLANG_VERSION} NO_DEFAULT_PATH)
if(NOT LLVM_VERSION_MAJOR EQUAL CLANG_VERSION)
  message(FATAL_ERROR "Found LLVM ${LLVM_PACKAGE_VERSION}, expected ${CLANG_VERSION}")
endif()

set(CMAKE_CXX_STANDARD 17)

add_library(census MODULE
  Census.cpp
  census_lib.cpp
  filters/NonConstCopyConstructor.cpp
  filters/Inheritance.cpp
  filters/Exceptions.cpp
  filters/Concurrency.cpp
  filters/Simd.cpp
  filters/Asm.cpp
)
set_target_properties(census PROPERTIES PREFIX "")

separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
target_include_directories(census PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(census SYSTEM PRIVATE ${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
target_compile_definitions(census PRIVATE ${LLVM_DEFINITIONS_LIST})
if(NOT LLVM_ENABLE_RTTI)
  target_compile_options(census PRIVATE -fno-rtti)
endif()

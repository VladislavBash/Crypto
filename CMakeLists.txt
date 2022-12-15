cmake_minimum_required(VERSION 3.10.0)

project("Cryptography" CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(cmake/StandardProjectSettings.cmake)
# Link this 'library' to set the c++ standard / compile-time options requested
add_library(default INTERFACE)
target_compile_features(default INTERFACE  cxx_std_20)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(default)

enable_testing()
add_subdirectory(doctest)
add_subdirectory(src)

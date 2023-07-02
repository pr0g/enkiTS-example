cmake_minimum_required(VERSION 3.22)

project(third-party)

include(ExternalProject)

get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT isMultiConfig)
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE
        Debug
        CACHE STRING "" FORCE)
  endif()
  set(build_type_dir ${CMAKE_BUILD_TYPE})
  set(build_type_arg -DCMAKE_BUILD_TYPE=$<CONFIG>)
endif()

ExternalProject_Add(
  enkiTS
  GIT_REPOSITORY https://github.com/pr0g/enkiTS.git
  GIT_TAG cd8e8c2af2e7c3f7d7719ccbed25f147d63b71f6
  BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/enkiTS/build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             "$<$<CONFIG:Debug>:-DCMAKE_DEBUG_POSTFIX=d>"
             -DENKITS_BUILD_EXAMPLES=OFF -DENKITS_INSTALL=ON)

cmake_minimum_required(VERSION 3.15)
project(enkiTS-example)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

option(ENKITS_EXAMPLE_USE_INSTALL "Use installed enkiTS libray" OFF)

if(ENKITS_EXAMPLE_USE_INSTALL)
  find_package(enkiTS)
  target_link_libraries(${PROJECT_NAME} PRIVATE enkiTS::enkiTS)
else()
  include(FetchContent)
  FetchContent_Declare(
    enkiTS
    GIT_REPOSITORY https://github.com/pr0g/enkiTS.git
    GIT_TAG cd8e8c2af2e7c3f7d7719ccbed25f147d63b71f6)
  FetchContent_MakeAvailable(enkiTS)
  target_link_libraries(${PROJECT_NAME} PRIVATE enkiTS)
endif()

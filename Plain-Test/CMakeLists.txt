# ${PROJECT_ROOT}/Plain/Plain-Tests/CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(PlainTests)  # 名前を統一
set(CMAKE_CXX_STANDARD 20)

# Google Testをプロジェクトに組み込む
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

#add_library(Plain STATIC IMPORTED)
#set_target_properties(Plain PROPERTIES
#    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Plain/libPlain.a"
#)

add_executable(plain-test main.cpp)
target_include_directories(plain-test PRIVATE
  ${gtest_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${CMAKE_CURRENT_SOURCE_DIR}/../Grain
)
#target_link_libraries(plain-test gtest gtest_main Plain)


target_link_libraries(plain-test
  gtest
  gtest_main
  Plain
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARY}
)



#cmake_minimum_required(VERSION 3.12)
#project(Plain-Tests)
#set(CMAKE_CXX_STANDARD 20)
#
#add_subdirectory(googletest)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#
#add_library(Plain STATIC IMPORTED GLOBAL)
#set_target_properties(Plain PROPERTIES IMPORTED_LOCATION ../Plain/libPlain.a)
#
#add_executable(plain-test main.cpp)
#target_link_libraries(plain-test gtest gtest_main Plain)
#
#project(PlainTests)


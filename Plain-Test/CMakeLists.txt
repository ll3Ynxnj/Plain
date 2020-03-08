project(Plain-Tests)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add_library(Plain STATIC IMPORTED GLOBAL)
#set_target_properties(Plain PROPERTIES IMPORTED_LOCATION ../Plain/libPlain.a)

add_executable(plain-test main.cpp)
target_link_libraries(plain-test gtest gtest_main Plain)

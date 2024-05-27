# ${PROJECT_ROOT}/Plain/CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(Plain CXX)
set(CMAKE_CXX_STANDARD 20)  # C++標準のバージョンを設定

# サブプロジェクトを追加
add_subdirectory(Grain)
add_subdirectory(Plain-Test)

# ソースファイルを再帰的に検索
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# ライブラリを作成
add_library(Plain STATIC ${SOURCE_FILES})

# インクルードディレクトリを設定
target_include_directories(Plain PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/Grain"
)

# OSごとにプリプロセッサを定義
if("${PLA_PLATFORM}" STREQUAL "MacOS")
  target_compile_definitions(Plain PRIVATE PLA_PLATFORM_MACOS)
elseif("${PLA_PLATFORM}" STREQUAL "Linux")
  target_compile_definitions(Plain PRIVATE PLA_PLATFORM_LINUX)
else()
  if ("${PLA_PLATFORM}" STREQUAL "")
    message(FATAL_ERROR "The variable 'PLA_PLATFORM' is empty.")
  else()
    message(FATAL_ERROR "It is unexpected that the variable 'PLA_PLATFORM' is '${PLA_PLATFORM}'.")
  endif()
endif()


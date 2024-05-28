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

# ソースファイルの自動検索
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# 実行ファイルの定義
add_executable(plain-test main.cpp)

# テストを追加
add_test(NAME plain-test COMMAND plain-test)

# インクルードディレクトリの指定
target_include_directories(plain-test PRIVATE
  ${gtest_SOURCE_DIR}/include
)

# ライブラリのリンク
target_link_libraries(plain-test
  gtest
  gtest_main
  Plain
)

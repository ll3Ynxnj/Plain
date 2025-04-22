# ${PROJECT_ROOT}/Plain/CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(Plain CXX)
set(CMAKE_CXX_STANDARD 20)  # C++標準のバージョンを設定

# CMakeポリシー設定とOpenGLのライブラリ選択
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

# C++標準の設定
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# パッケージを探索
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# サブプロジェクトを追加
add_subdirectory(Grain)
add_subdirectory(Plain-Test)

# ソースファイルを再帰的に検索
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# ライブラリを作成
add_library(Plain STATIC ${SOURCE_FILES})

# インクルードするディレクトリ設定
target_include_directories(Plain PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  ${OpenCV_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${GLUT_INCLUDE_DIRS}
)

# リンクするライブラリを設定
if(APPLE)
  target_link_libraries(Plain PUBLIC
    stdc++
    grain
    ${OpenCV_LIBS}
    ${OPENGL_LIBRARIES}
    "-framework GLUT"
  )
else()
  target_link_libraries(Plain PUBLIC
    stdc++
    grain
    ${OpenCV_LIBS}
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}   # または、環境に合わせて ${GLUT_LIBRARIES} にする
  )
endif()

# OS情報を取得
execute_process(
        COMMAND uname -s
        OUTPUT_VARIABLE OS_NAME
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# OSに基づいてプリプロセッサ定義をターゲットに追加
if("${OS_NAME}" STREQUAL "Darwin")
  target_compile_definitions(Plain PRIVATE PLA_PLATFORM_DARWIN)
elseif("${OS_NAME}" STREQUAL "Linux")
  target_compile_definitions(Plain PRIVATE PLA_PLATFORM_LINUX)
else()
  message(FATAL_ERROR "Unsupported OS: ${OS_NAME}")
endif()

# OS情報を取得
execute_process(
        COMMAND uname -s
        OUTPUT_VARIABLE OS_NAME
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# OSに基づいてプリプロセッサ定義をターゲットに追加
if("${OS_NAME}" STREQUAL "Darwin")
  target_compile_definitions(Plain PRIVATE PLA_PLATFORM_DARWIN)
elseif("${OS_NAME}" STREQUAL "Linux")
  target_compile_definitions(Plain PRIVATE PLA_PLATFORM_LINUX)
else()
  message(FATAL_ERROR "Unsupported OS: ${OS_NAME}")
endif()

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
find_package(Freetype REQUIRED)

# Download ONNX models for face/smile detection
set(PLA_MODELS_DIR "${CMAKE_CURRENT_BINARY_DIR}/models")
file(MAKE_DIRECTORY ${PLA_MODELS_DIR})

# YuNet face detection model
set(PLA_YUNET_MODEL_PATH "${PLA_MODELS_DIR}/face_detection_yunet_2023mar.onnx")
if(NOT EXISTS ${PLA_YUNET_MODEL_PATH})
  message(STATUS "Downloading YuNet face detection model...")
  file(DOWNLOAD
    "https://github.com/opencv/opencv_zoo/raw/main/models/face_detection_yunet/face_detection_yunet_2023mar.onnx"
    ${PLA_YUNET_MODEL_PATH}
    SHOW_PROGRESS
  )
endif()

# Emotion recognition model (FER+)
set(PLA_EMOTION_MODEL_PATH "${PLA_MODELS_DIR}/emotion-ferplus-8.onnx")
if(NOT EXISTS ${PLA_EMOTION_MODEL_PATH})
  message(STATUS "Downloading emotion recognition model...")
  file(DOWNLOAD
    "https://github.com/onnx/models/raw/main/validated/vision/body_analysis/emotion_ferplus/model/emotion-ferplus-8.onnx"
    ${PLA_EMOTION_MODEL_PATH}
    SHOW_PROGRESS
  )
endif()

# Download Noto Sans JP font
set(PLA_FONTS_DIR "${CMAKE_CURRENT_BINARY_DIR}/fonts")
file(MAKE_DIRECTORY ${PLA_FONTS_DIR})

set(PLA_DEFAULT_FONT_PATH "${PLA_FONTS_DIR}/NotoSansJP-Regular.ttf")
if(NOT EXISTS ${PLA_DEFAULT_FONT_PATH})
  message(STATUS "Downloading Noto Sans JP font...")
  file(DOWNLOAD
    "https://github.com/notofonts/noto-cjk/raw/main/Sans/SubsetOTF/JP/NotoSansJP-Regular.otf"
    ${PLA_DEFAULT_FONT_PATH}
    SHOW_PROGRESS
  )
endif()

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
  ${FREETYPE_INCLUDE_DIRS}
)

# リンクするライブラリを設定
target_link_libraries(Plain PUBLIC
  stdc++
  grain
  ${OpenCV_LIBS}
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARY}
  ${FREETYPE_LIBRARIES}
)

# モデルパスをコンパイル時に埋め込み
target_compile_definitions(Plain PRIVATE
  PLA_YUNET_MODEL_PATH="${PLA_YUNET_MODEL_PATH}"
  PLA_EMOTION_MODEL_PATH="${PLA_EMOTION_MODEL_PATH}"
  PLA_DEFAULT_FONT_PATH="${PLA_DEFAULT_FONT_PATH}"
)

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

# OSごとにプリプロセッサを定義
# if("${PLA_PLATFORM}" STREQUAL "MacOS")
#   target_compile_definitions(Plain PRIVATE PLA_PLATFORM_MACOS)
# elseif("${PLA_PLATFORM}" STREQUAL "Linux")
#   target_compile_definitions(Plain PRIVATE PLA_PLATFORM_LINUX)
# else()
#   if ("${PLA_PLATFORM}" STREQUAL "")
#     message(FATAL_ERROR "The variable 'PLA_PLATFORM' is empty.")
#   else()
#     message(FATAL_ERROR "It is unexpected that the variable 'PLA_PLATFORM' is '${PLA_PLATFORM}'.")
#   endif()
# endif()

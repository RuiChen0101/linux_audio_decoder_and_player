cmake_minimum_required(VERSION 3.10)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(INC_LIST
  "include/decoder/decoder.h"
  "include/decoder/ffmpeg_decoder.h"
  "include/decoder/pcm_reader.h"
  "include/player/player.h"
  "include/player/alsa_player.h"
  "include/player/pcm_dumper.h"
)

set(SRC_LIST
  "src/decoder/decoder.cpp"
  "src/decoder/ffmpeg_decoder.cpp"
  "src/decoder/pcm_reader.cpp"
  "src/player/player.cpp"
  "src/player/alsa_player.cpp"
  "src/player/pcm_dumper.cpp"
  "main.cpp"
)

set(LIB_LIST
  "-lasound"
  "-lavformat"
  "-lavcodec"
  "-lavutil"
  "-lswresample"
)

set(COMPILE_OPTION -std=c++17 -Wfatal-errors)
include_directories("./")
include_directories("./include")
include_directories("/usr/include")
link_directories("/usr/lib")

#build main
set(MAIN_TARGET decode_and_play)

add_executable(${MAIN_TARGET} ${SRC_LIST} ${INC_LIST})
target_compile_options(${MAIN_TARGET} PUBLIC ${COMPILE_OPTION})
target_link_libraries(${MAIN_TARGET} PUBLIC ${LIB_LIST})
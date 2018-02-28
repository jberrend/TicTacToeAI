cmake_minimum_required(VERSION 3.7)

project(TicTacToe)

set(CMAKE_CXX_STANDARD 11)

include_directories( ${CMAKE_SOURCE_DIR}/include )

#file(GLOB SRC_FILES
#	"src/*.cpp"
#)

add_subdirectory(src)
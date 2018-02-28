set (SRC_FILES Main.cpp TicTacToeGame.cpp GameAgent.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(TicTacToe ${SRC_FILES})
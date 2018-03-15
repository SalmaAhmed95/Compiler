cmake_minimum_required(VERSION 3.8)
project(complier)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp NFA.h Node.h Node.cpp NFA.cpp Automata.h NfaNode.cpp NfaNode.h DfaNode.cpp DfaNode.h Automata.cpp DFA.cpp DFA.h)
add_executable(complier ${SOURCE_FILES})
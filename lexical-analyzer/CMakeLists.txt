cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Compiler)

enable_testing()

#add_subdirectory(code-parser)
add_subdirectory(grammar-parser)
add_subdirectory(main)
add_subdirectory(automata)
add_subdirectory(dfa-minimizer)
add_subdirectory(error)
add_subdirectory(pattern-matcher)
add_subdirectory(utils)
#add_subdirectory(tests)

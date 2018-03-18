cmake_minimum_required(VERSION 2.8)

project(Compiler)

enable_testing()

add_subdirectory(grammar-parser)
add_subdirectory(main)
add_subdirectory(automata)
add_subdirectory(tests)

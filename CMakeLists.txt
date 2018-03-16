cmake_minimum_required(VERSION 3.8)
project(Compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/complier.cbp
        cmake-build-debug/Makefile
        lexical-analyzer/automata/Automata.cpp
        lexical-analyzer/automata/Automata.h
        lexical-analyzer/automata/DFA.cpp
        lexical-analyzer/automata/DFA.h
        lexical-analyzer/automata/DfaNode.cpp
        lexical-analyzer/automata/DfaNode.h
        lexical-analyzer/automata/NFA.cpp
        lexical-analyzer/automata/NFA.h
        lexical-analyzer/automata/NfaNode.cpp
        lexical-analyzer/automata/NfaNode.h
        lexical-analyzer/automata/Node.cpp
        lexical-analyzer/automata/Node.h
        lexical-analyzer/build/automata/cmake_install.cmake
        lexical-analyzer/build/automata/libautomata.a
        lexical-analyzer/build/automata/Makefile
        lexical-analyzer/build/grammar-parser/cmake_install.cmake
        lexical-analyzer/build/grammar-parser/libgrammar-parser.a
        lexical-analyzer/build/grammar-parser/Makefile
        lexical-analyzer/build/main/cmake_install.cmake
        lexical-analyzer/build/main/lexical-analyzer
        lexical-analyzer/build/main/Makefile
        lexical-analyzer/build/cmake_install.cmake
        lexical-analyzer/build/CMakeCache.txt
        lexical-analyzer/build/Makefile
        lexical-analyzer/grammar-parser/ProductionParser.cpp
        lexical-analyzer/grammar-parser/ProductionParser.hpp
        lexical-analyzer/grammar-parser/Properties.cpp
        lexical-analyzer/grammar-parser/Properties.hpp
        lexical-analyzer/grammar-parser/Token.cpp
        lexical-analyzer/grammar-parser/Token.hpp
        lexical-analyzer/main/main.cpp
        lexical-analyzer/CMakeLists.txt lexical-analyzer/pattern-matcher/PatternMatcher.cpp lexical-analyzer/pattern-matcher/PatternMatcher.h lexical-analyzer/code-parser/CodeParser.cpp lexical-analyzer/code-parser/CodeParser.h lexical-analyzer/utils/SymbolTable.cpp lexical-analyzer/utils/SymbolTable.h)

add_executable(Compiler ${SOURCE_FILES})
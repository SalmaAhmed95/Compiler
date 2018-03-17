cmake_minimum_required(VERSION 3.8)
project(Compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        lexical-analyzer/automata/Automata.cpp
        lexical-analyzer/automata/Automata.h
        lexical-analyzer/automata/DFA.cpp
        lexical-analyzer/automata/DFA.h
        lexical-analyzer/automata/DfaNode.cpp
        lexical-analyzer/automata/DfaNode.h
        lexical-analyzer/automata/main.cpp
        lexical-analyzer/automata/NFA.cpp
        lexical-analyzer/automata/NFA.h
        lexical-analyzer/automata/NfaNode.cpp
        lexical-analyzer/automata/NfaNode.h
        lexical-analyzer/automata/NfaToDfaConverter.cpp
        lexical-analyzer/automata/NfaToDfaConverter.h
        lexical-analyzer/automata/Node.cpp
        lexical-analyzer/automata/Node.h
        lexical-analyzer/automata/RegexToNfaConverter.cpp
        lexical-analyzer/automata/RegexToNfaConverter.hpp
        lexical-analyzer/code-parser/CodeParser.cpp
        lexical-analyzer/code-parser/CodeParser.h
        lexical-analyzer/dfa-minimizer/DfaMinimizer.cpp
        lexical-analyzer/dfa-minimizer/DfaMinimizer.h
        lexical-analyzer/grammar-parser/ProductionParser.cpp
        lexical-analyzer/grammar-parser/ProductionParser.hpp
        lexical-analyzer/grammar-parser/Properties.cpp
        lexical-analyzer/grammar-parser/Properties.hpp
        lexical-analyzer/grammar-parser/Token.cpp
        lexical-analyzer/grammar-parser/Token.hpp
        lexical-analyzer/pattern-matcher/PatternMatcher.cpp
        lexical-analyzer/pattern-matcher/PatternMatcher.h
        lexical-analyzer/utils/SymbolTable.cpp
        lexical-analyzer/utils/SymbolTable.h)

add_executable(Compiler ${SOURCE_FILES})
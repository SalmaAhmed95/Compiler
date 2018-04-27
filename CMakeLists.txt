cmake_minimum_required(VERSION 3.5)
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
        error/ErrorHandler.cpp
        error/ErrorHandler.h
        file-writer/FileWriter.cpp
        file-writer/FileWriter.h
        lexical-analyzer/grammar-parser/ProductionParser.cpp
        lexical-analyzer/grammar-parser/ProductionParser.hpp
        lexical-analyzer/grammar-parser/Properties.cpp
        lexical-analyzer/grammar-parser/Properties.hpp
        lexical-analyzer/grammar-parser/Token.cpp
        lexical-analyzer/grammar-parser/Token.hpp
        lexical-analyzer/tokenizer/Tokenizer.cpp
        lexical-analyzer/tokenizer/Tokenizer.h
        utils/SymbolTable.cpp
        utils/SymbolTable.h
        utils/StringUtils.h
        utils/StringUtils.cpp
        lexical-analyzer/automata/Definitions.h
        parser/CFGParser.h parser/CFGParser.cpp
        parser/Grammar.h parser/Grammar.cpp
        parser/Grammar.h parser/Grammar.cpp
        parser/ProductionNode.h
        parser/ProductionNode.cpp
        parser/ParsingTable.cpp
        parser/ParsingTable.h
        parser/Parser.h
        parser/Parser.cpp parser/ParseResult.h
        main/main.cpp)

add_executable(Compiler ${SOURCE_FILES})

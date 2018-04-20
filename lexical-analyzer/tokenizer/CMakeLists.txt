set(PatternMatcher_SRCS
        Tokenizer.cpp
    ../code-parser/CodeParser.cpp
    ../error/ErrorHandler.cpp
    ../file-writer/FileWriter.cpp
)

set(PatternMatcher_HEADERS
        Tokenizer.h
    ../code-parser/CodeParser.h
    ../error/ErrorHandler.h
    ../file-writer/FileWriter.h
)


# Declare the library
add_library(pattern-matcher STATIC
    ${PatternMatcher_SRCS}
    ${PatternMatcher_HEADERS}
)


# Specify here the include directories exported
# by this library
target_include_directories(pattern-matcher PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

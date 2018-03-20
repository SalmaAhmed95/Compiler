set(code-parser_SRCS
    CodeParser.cpp
)

set(code-parser_HEADERS
    CodeParser.h
)


# Declare the library
add_library(code-parser STATIC
    ${code-parser_SRCS}
    ${code-parser_HEADERS}
)


# Specify here the include directories exported
# by this library
target_include_directories(code-parser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

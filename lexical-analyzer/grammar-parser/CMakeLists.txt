set(grammar-parser_SRCS
    ProductionParser.cpp
    Properties.cpp
    Token.cpp
)

set(grammar-parser_HEADERS
    Token.hpp
    Properties.hpp
    ProductionParser.hpp
)


# Declare the library
add_library(grammar-parser STATIC
    ${grammar-parser_SRCS}
    ${grammar-parser_HEADERS}
)


# Specify here the include directories exported
# by this library
target_include_directories(grammar-parser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

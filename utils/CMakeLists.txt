set(utils_SRCS
        SymbolTable.cpp
)

set(utils_HEADERS
        SymbolTable.h
)


# Declare the library
add_library(utils-lib STATIC
    ${utils_SRCS}
    ${utils_HEADERS}
)


# Specify here the include directories exported
# by this library
target_include_directories(utils-lib PUBLIC
        .
)

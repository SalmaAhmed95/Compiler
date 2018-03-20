set(DfaMinimizer_SRCS
    DfaMinimizer.cpp
)

set(DfaMinimizer_HEADERS
    DfaMinimizer.h
)


# Declare the library
add_library(dfa-minimizer STATIC
    ${DfaMinimizer_SRCS}
    ${DfaMinimizer_HEADERS}
)


# Specify here the include directories exported
# by this library
target_include_directories(dfa-minimizer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

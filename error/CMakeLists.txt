set(ErrorHandle_SRCS
        ErrorHandler.cpp
)

set(ErrorHandle_HEADERS
        ErrorHandler.h
)


# Declare the library
add_library(error-handler STATIC
    ${ErrorHandle_SRCS}
    ${ErrorHandle_HEADERS}
)


# Specify here the include directories exported
# by this library
target_include_directories(error-handler PUBLIC
        .
)

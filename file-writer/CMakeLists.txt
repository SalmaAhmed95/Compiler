set(FileWriter_SRCS
    FileWriter.cpp
)

set(FileWriter_HEADERS
    FileWriter.h
)


# Declare the library
add_library(file-writer STATIC
    ${FileWriter_SRCS}
    ${FileWriter_HEADERS}
)


# Specify here the include directories exported
# by this library
target_include_directories(file-writer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(grammar-parser-tests ${SRCS})

TARGET_LINK_LIBRARIES(grammar-parser-tests
    grammar-parser
    libgtest
    libgmock
)

add_test(NAME grammar-parser-tests
COMMAND grammar-parser-tests)

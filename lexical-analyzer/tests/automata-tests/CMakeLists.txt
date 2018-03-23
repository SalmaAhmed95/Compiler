file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(automata-tests ${SRCS})

TARGET_LINK_LIBRARIES(automata-tests
    automata
    libgtest
    libgmock
)

add_test(NAME automata-tests
COMMAND automata-tests)

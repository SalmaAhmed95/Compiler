set(SRCS
  main.cpp
  TestAutomata.cpp
  TestAutomata.hpp
  TestRegexToNfaConverter.cpp
  TestRegexToNfaConverter.hpp
  ../grammar-parser-tests/TestHelper.cpp
  ../grammar-parser-tests/TestHelper.hpp
  TestNfaToDfaConverter.hpp
  TestNfaToDfaConverter.cpp
)

ADD_EXECUTABLE(automata-tests ${SRCS})

TARGET_LINK_LIBRARIES(automata-tests
    automata
    grammar-parser
    libgtest
    libgmock
)

add_test(NAME automata-tests
COMMAND automata-tests)

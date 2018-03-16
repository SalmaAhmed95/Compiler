set(automata_SRCS
    Automata.cpp
    DFA.cpp
    DfaNode.cpp
    NFA.cpp
    NfaNode.cpp
    Node.cpp
)

set(automata_HEADERS
    Automata.h
    DFA.h
    DfaNode.h
    NFA.h
    NfaNode.h
    Node.h
)


# Declare the library
add_library(automata STATIC
    ${automata_SRCS}
    ${automata_HEADERS}
)


# Specify here the include directories exported
# by this library
target_include_directories(automata PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

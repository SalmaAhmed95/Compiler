# Compiler

It's an academic project that means to know how Compliers generates its intermediate code in the first phase of code generation.
It's composed of two modules: Lexical Analayzer that tokenizes the code into certain lexemes, and Syntax parser that checks
that the code follows certain context free grammer rules.

##LEX 

As extension to the project, it was required to generate JavaByte code for simple CFG rules by adding the suitable semantic 
rules to generate it. To construct the parse tree, Bison tool was used and we generated the suitable actions to generate the 
intermediate code. 

## Future Plans:

Implementing the parser tree and extending the original project to excute semantic actions





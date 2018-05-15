# Compiler

It's an academic project that means to know how Compliers generates its intermediate code in the first phase of code generation.
It's composed of two modules: Lexical Analayzer that tokenizes the code into certain lexemes, and Syntax parser that checks
that the code follows certain context free grammer rules by converting the rules to LL grammer and implementing the top down 
parser.

## LEX 

As extension to the project, it was required to generate JavaByte code for simple CFG rules by adding the suitable semantic 
rules to generate it. To construct the parse tree, Bison tool was used and we generated the suitable actions to generate the 
intermediate code. 

## Future Plans

Implementing the parser tree and extending the original project to excute semantic actions and completing the documentation for the project.


## How to Use it

### There are four input files that needs to be setted: 

  1.lexical_rules.txt : It contains the regular expressions that defines the terminal types (lexemes types) that is 
   supported by this language.
  
 `2. properties.ini : It contains  the delimiters that are used to define the regular expressions.
 
  3. grammer.txt : It contains the context free grammer rules and it can be recursive.
  
  4. code.txt : It contains the code you needs to be complied.
  
###  And There are three output files:  

 1. lexical_ouput.txt : It contains the minimzied DFA that are used to parse the regular expressions and each lexeme with its type
 
 2. parser_output.txt : It contains the parsing table for the syntax parsing and how the parsing stack changes.
 
 3. left_derivation.txt : It contains the left derivation of the code by using the rules in grammer.txt
  
  
 
 


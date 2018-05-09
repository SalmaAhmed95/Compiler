%{
#include <stdlib.h> /* malloc. */
#include <string.h> /* strlen. */
#include <cstdio>
#include <map>
#include <iostream>
#include <string>
#include <vector>


using namespace std;
#define TINT  267
#define TFLOAT  268
// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);


/*memory location counter for local variables*/
int memory_location_counter = 1;

typedef struct symrec {
  int type;    /* type of symbol: either VAR or FNCT */
  int location;
  bool isConstant;
	
  symrec(int type, bool isConstant) {
    this->type = type;
    location = memory_location_counter;
    this->isConstant = isConstant;
  }
  
  symrec(){}

} symrec;

map<string, symrec> symTable;

string declareAction(symrec);
string assignAction();

%}

%union {
  int  ival;
  double fval;
  char *string;
}
%start METHOD_BODY
%token <string> ID
%token ASSIGN
%token OPEN_BRACKET
%token CLOSED_BRACKET
%token OPEN_CURLY
%token CLOSED_CURLY
%token If
%token ELSE
%token While
%token <ival> INT
%token <fval> FLOAT
%token <string> RELOP
%token <string> ADDOP
%token <string> MULOP
%type <ival> PRIMITIVE_TYPE NUM
%type <string> SIGN DECLARATION
%%

METHOD_BODY:		STATEMENT_LIST
STATEMENT_LIST:		STATEMENT
			| STATEMENT_LIST STATEMENT
STATEMENT:		DECLARATION
			| IF
			| WHILE
			| ASSIGNMENT
DECLARATION:		PRIMITIVE_TYPE ID ';' {
						memory_location_counter++;
						string varName($2);
						symrec newRec = symrec($1, false);
						symTable[varName] = newRec;
						string tmp = declareAction(newRec);
						vector<char> v(tmp.begin(), tmp.end());
						$$ = &v[0];
					      }
PRIMITIVE_TYPE:		INT {$$ = $1;}
			| FLOAT {$$ = $1;}
IF:			If OPEN_BRACKET EXPRESSION CLOSED_BRACKET OPEN_CURLY STATEMENT CLOSED_CURLY ELSE OPEN_CURLY STATEMENT CLOSED_CURLY
WHILE:			While OPEN_BRACKET EXPRESSION CLOSED_BRACKET OPEN_CURLY STATEMENT CLOSED_CURLY
ASSIGNMENT:		ID ASSIGN EXPRESSION ';' {}
EXPRESSION:		SIMPLE_EXPRESSION
			| SIMPLE_EXPRESSION RELOP SIMPLE_EXPRESSION
SIMPLE_EXPRESSION:	TERM
			| SIGN TERM
			| SIMPLE_EXPRESSION ADDOP TERM 
TERM:			FACTOR
			| TERM MULOP FACTOR
FACTOR:			ID
			| NUM 
			| OPEN_BRACKET EXPRESSION CLOSED_BRACKET
SIGN:			ADDOP {$$ = $1;}

NUM:                    INT {$$ = $1;}
                        | FLOAT {$$ = $1;}

%%

int main (int argc, char const* argv[]) {
    FILE *fh;
    if (argc == 2 && (fh = fopen(argv[1], "r"))){
          if (!fh) {
		printf("I can't open file!\n");
		return -1;
	  }
          yyin = fh;	
	  // parse through the input until there is no more:
          do {
	  	yyparse();
          } while (!feof(yyin));
    }
	
    for (map<string, symrec>::iterator it = symTable.begin(); it != symTable.end(); it++) {
	cout << (*it).first << "\t" << (*it).second.type << endl;
    }

    return 0;
}

string declareAction(symrec rec) {
	string code;
	if (rec.type == TINT) {
		code += "iconst_0\n";
		code += string("istore") + (memory_location_counter < 4 ? "_" : "") + to_string(memory_location_counter);
	} else if (rec.type == TFLOAT) {
		code += string("fconst_0\n");
		code += string("fstore") + (memory_location_counter < 4 ? string("_") : string(" ")) + to_string(memory_location_counter);
	}
	return code;    
}

void yyerror(const char *s) {
	printf("EEK, parse error! %s\n",s);
	// might as well halt now:
	exit(-1);
}

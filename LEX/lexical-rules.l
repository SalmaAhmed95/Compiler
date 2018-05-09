%{
#include <stdio.h>
#include <iostream>
#include "grammer.tab.h"
#include <string>

using namespace std;

#define YY_DECL extern "C" int yylex()
%}
letter [a-z|A-Z]
digit  [0-9]
digits {digit}+
ID  {letter}({letter}|{digit})*
relop  (\=\=)|(!\=)|(>)|(>\=)|(<)|(<\=)
assign [\=]
addop  [\+ | \-]
mulop  [* | /]
%%
" "       {}
[ \t]*		{}
[ \n]*		{}
if {return If;}
else {return ELSE;}
while {return While;}
int   {yylval.ival = INT; return INT;}
float {yylval.ival = FLOAT; return FLOAT;}
[0-9]+\.[0-9]+    { yylval.fval = atof(yytext); return FLOAT; }
[0-9]+            { yylval.ival = atoi(yytext); return INT; }
";" {return ';';}
"(" {return OPEN_BRACKET;}
")" {return CLOSED_BRACKET;}
"{" {return OPEN_CURLY;}
"}" {return CLOSED_CURLY;}
{ID} {yylval.string = strdup(yytext); return ID;}
{assign} {return ASSIGN;}
{relop} {yylval.string = strdup(yytext); return RELOP;}
{addop} {yylval.string = strdup(yytext); return ADDOP;}
{mulop} {yylval.string = strdup(yytext); return MULOP;}

%%
/*main(int argc, char* argv[]) {
    FILE *fh;

    if (argc == 2 && (fh = fopen(argv[1], "r")))
        yyin = fh;
    yylex();
    return 0;
}*/

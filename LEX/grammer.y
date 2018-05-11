%{
#include <stdlib.h> /* malloc. */
#include <string.h> /* strlen. */
#include <cstdio>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>



using namespace std;
#define TINT  267
#define TFLOAT  268

const string SI_PUSH = "si_push";
const string F_PUSH = "sf_push";
const string I_STORE = "istore";
const string F_STORE = "fstore";
const string I_LOAD = "iload";
const string F_LOAD = "fload";
const string ADD = "add";
const string MUL = "mul";
const string DIV = "div";
const string SUB = "sub";
const string NEGATIVE = "iconst_m1";

const string I2F = "i2f";
const string FCMPL = "fcmpl";

const string IFNE = "if_icmpne";
const string IFE = "if_icmpeq";
const string IFLT = "if_icmplt";
const string IFGE = "if_icmpge";
const string IFGT = "if_icmpgt";
const string IFLE = "if_icmple";
const string IFEZ = "ifeq";
const string IFNEZ = "ifne";
const string IFLTZ = "iflt";
const string IFGEZ = "ifge";
const string IFGTZ = "ifgt";
const string IFLEZ = "ifle";
const string GOTO = "goto";
// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyerror(const char *s);


/*memory location counter for local variables*/
int memory_location_counter = 0;
int temp_counter = 0;
int label_counter = 0;

typedef struct symrec {
	int type;
	int location;

	symrec(int type, int location_counter) {
		this->type = type;
		location = location_counter;
	}
	symrec() {}
} symrec;

map<string, symrec> symTable;
void writeToFile (char *allCode);
string getNewLabel();
string getCurrentLabel();
string declareAction(symrec);
char *constAction(int type, int ival, float fval);
string getTempName();
char *assignAction(char *idName, string varName);
string getFloatIntOp(symrec op1, symrec op2, string operation1, string operation2, string n1, string n2);
string genIfCode(string op1, string relOp, string op2);
string getEndDelimiter(string* code);
string generateSignCode (string term ,char* sign);
struct synAttr *performOperation(string n1, string n2, char *opera);
struct synAttr *loadID(string name);
%}

%code requires {
	struct synAttr {
		char *tempName = 0;
		char *genCode;
	};
}

%union {
	int ival;
	double fval;
	char *string;
	struct synAttr *passedValue;
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
%type <ival> PRIMITIVE_TYPE
%type <string> SIGN DECLARATION ASSIGNMENT STATEMENT STATEMENT_LIST METHOD_BODY NUM IF WHILE
%type <passedValue> EXPRESSION SIMPLE_EXPRESSION FACTOR TERM 
%%

METHOD_BODY:		STATEMENT_LIST {$$ = $1;
                                        cout<<"method body "<<$$<<endl;
				        writeToFile($$);}
STATEMENT_LIST:		STATEMENT {$$ = $1;}
			| STATEMENT_LIST STATEMENT	{
								string statement_list($1);
								string statement ($2);
								statement_list += '\n' + statement;
								char *value = (char *)malloc (statement_list.length() + 1);
								copy( statement_list.begin(), statement_list.end(), value);
								value[statement_list.length()] = '\0';
								$$ = value;
							}

STATEMENT:		DECLARATION {$$ = $1;}
			| IF {$$ = $1;}
			| WHILE {$$ = $1;}
			| ASSIGNMENT {$$ = $1;}
DECLARATION:		PRIMITIVE_TYPE ID ';'	{
							memory_location_counter++;
							string varName($2);
							symrec newRec = symrec($1,memory_location_counter);
							symTable[varName] = newRec;
							string tmp = declareAction(newRec);
							char *value = (char *) malloc(tmp.length() + 1);
							copy(tmp.begin(), tmp.end(), value );
							value[tmp.length()] = '\0';
							$$ = value;
						}

PRIMITIVE_TYPE:		INT {$$ = $1;}
			| FLOAT {$$ = $1;}

IF:			If OPEN_BRACKET EXPRESSION CLOSED_BRACKET OPEN_CURLY STATEMENT CLOSED_CURLY ELSE OPEN_CURLY STATEMENT CLOSED_CURLY	{
																			string compCode($3->genCode);
																			string stmt1Code($6);
																			string stmt2Code($10);
																			string endDelimiter = getEndDelimiter(&stmt1Code);
																			string genCode = compCode + stmt1Code + endDelimiter;
																			genCode += GOTO + " " + getNewLabel() + "\n";
																			genCode += string($3->tempName) + " ";
																			genCode += stmt2Code + "\n";
																			genCode += getCurrentLabel();
																			char *codeVal = (char *) malloc(genCode.length() + 1);
																			copy(genCode.begin(), genCode.end(), codeVal );
																			codeVal[genCode.length()] = '\0';
																			$$ = codeVal;
																		}

WHILE:			While OPEN_BRACKET EXPRESSION CLOSED_BRACKET OPEN_CURLY STATEMENT CLOSED_CURLY	{
														string compCode = ($3->genCode);
														string stmtCode = ($6);
														string loopLabel = getNewLabel();
														string genCode = loopLabel + " " + compCode;
														string endDelimiter = getEndDelimiter(&stmtCode);
														genCode += stmtCode + endDelimiter;
														genCode += GOTO + " " + loopLabel + "\n";
														genCode += string($3->tempName);
														char *codeVal = (char *) malloc(genCode.length() + 1);
														copy(genCode.begin(), genCode.end(), codeVal );
														codeVal[genCode.length()] = '\0';
														$$ = codeVal;
														cout << "Parsed a while " << genCode << endl;
													}

ASSIGNMENT:		ID ASSIGN EXPRESSION ';'	{
								string expCode($3->genCode);
								string s($3->tempName);
								string assignCode( assignAction($1, s));
								expCode += assignCode;
								char *value = (char *)malloc (expCode.length() + 1);
								copy( expCode.begin(), expCode.end(), value );
								value[expCode.length()] = '\0';
								$$ = value;
								cout<<"assignment  "<<$$<<endl;
							}

EXPRESSION:		SIMPLE_EXPRESSION	{
							$$ = new struct synAttr;
							$$->genCode = $1->genCode;
							$$->tempName = $1->tempName;
							cout<<"expression  "<<$$->genCode<<endl;
						}

			| SIMPLE_EXPRESSION RELOP SIMPLE_EXPRESSION	{
										string exp1($1->genCode);
										string exp2($3->genCode);
										string code = exp1 + exp2 + genIfCode($1->tempName, $2, $3->tempName);
										char *codeVal = (char *) malloc(code.length() + 1);
										copy(code.begin(), code.end(), codeVal);
										codeVal[code.length()] = '\0';
										string currentLabel = getCurrentLabel();
										char *tempNameVal = (char *) malloc(currentLabel.length() + 1);
										copy(currentLabel.begin(), currentLabel.end(), tempNameVal);
										tempNameVal[currentLabel.length()] = '\0';
										$$ = new struct synAttr;
										$$->tempName = tempNameVal;
										$$->genCode = codeVal;
										
										cout << "Reversed Comparison" << $$->genCode << endl;
									}

SIMPLE_EXPRESSION:	TERM	{
					$$ = new struct synAttr;
					$$->genCode = $1->genCode;
					$$->tempName = $1->tempName;
					cout<<"simple expression  "<<$$->genCode<<endl;
				}

			| SIGN TERM {
				     string termCode($2->genCode);
                                     termCode += generateSignCode($2->tempName,$1);
                                     char *value = (char *)malloc (termCode.length() + 1);
                                     copy( termCode.begin(), termCode.end(), value );
				     value[termCode.length()] = '\0';
                                     $$->genCode = value; 
                                     $$->tempName = $2->tempName; 

                                    }
			| SIMPLE_EXPRESSION ADDOP TERM	{
								string exp($1->genCode);
								string term ($3->genCode);
								string genCode = exp + term;
								string s1($1->tempName), s2($3->tempName);
								struct synAttr *returnedAttr = performOperation(s1, s2, $2);
								string attrStr(returnedAttr->genCode);
								genCode += attrStr;
								char *value = (char *)malloc (genCode.length() + 1);
								copy( genCode.begin(), genCode.end(), value );
								value[genCode.length()] = '\0';
								$$ = new struct synAttr;
								$$->genCode = value;
								$$->tempName = returnedAttr->tempName;
							}

TERM:			FACTOR	{
					$$ = new struct synAttr;
					$$->genCode = $1->genCode;
					$$->tempName = $1->tempName;
				        cout<<"term "<<$$->genCode<<endl;
		                }
			| TERM MULOP FACTOR	{
							string termCode($1->genCode);
							string factorCode ($3->genCode);
							string genCode = termCode + factorCode;
							string s1($1->tempName), s2($3->tempName);
				                        struct synAttr *returnedAttr = performOperation(s1, s2, $2);
							string attrStr(returnedAttr->genCode);
							genCode += attrStr;
				                        char *value = (char *)malloc (genCode.length() + 1);
				                        cout<<"gencode in term mul  "<<genCode<<endl;
				                        copy( genCode.begin(), genCode.end(), value );
							value[genCode.length()] = '\0';
							$$ = new struct synAttr;
							$$->genCode = value;
							$$->tempName = returnedAttr->tempName;
							cout<<"term mul  "<<$$->genCode<<endl;
						}

FACTOR:			ID	{
					string idName($1);
					struct synAttr *attr = loadID(idName);
					$$->genCode = attr->genCode;
					$$->tempName = attr->tempName;
				}

			| NUM	{
					char c[1]; c[0] = '\0';
					$$ = new struct synAttr;
					$$->genCode = $1;
					$$->tempName = c;
					cout<<"factor "<<$$->genCode<<endl;
				}

			| OPEN_BRACKET EXPRESSION CLOSED_BRACKET	{
										$$ = new struct synAttr;
										$$->genCode = $2->genCode;
										$$->tempName = $2->tempName;
									}

SIGN:			ADDOP	{$$ = $1;}

NUM:                    INT	{
					$$ = constAction(TINT, $1,0);
					cout<<"in num "<<$$<<endl;
				}

                        | FLOAT { $$ = constAction(TFLOAT,0, $1); }


%%

int main (int argc, char const* argv[]) {
    FILE *fh;
	if (argc == 2 && (fh = fopen(argv[1], "r"))) {
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
		code += I_STORE + (memory_location_counter < 4 ? "_" : "") + to_string(memory_location_counter);
	} else if (rec.type == TFLOAT) {
		code += string("fconst_0\n");
		code += F_STORE + (memory_location_counter < 4 ? string("_") : string(" ")) + to_string(memory_location_counter);
	}
	return code;
}

char *constAction(int type, int ival, float fval) {
	string val, key;
	if (type == TINT) {
		key = to_string(ival);
		val = SI_PUSH + " " + to_string(ival);
	} else {
		key = to_string(fval);
		val = F_PUSH + " " + to_string(fval);
	}
	val += "\n";
	char *value = (char *) malloc(val.length() + 1);
	copy(val.begin(), val.end(), value);
	value[val.length()] = '\0';
	return value;
}

void yyerror(const char *s) {
	printf("EEK, parse error! %s\n",s);
	// might as well halt now:
	exit(-1);
}

void writeToFile (char *allCode) {
	ofstream myfile;
	myfile.open ("output.txt");
	myfile << allCode;
	myfile.close();
}

string getTempName() {
	string t = "t" + to_string(temp_counter);
	temp_counter++;
	return t;
}

struct synAttr *loadID(string name){
	if(symTable.find(name) == symTable.end()) exit(-1);
	symrec returnRec = symTable[name];
	string genCode;
	string tempName =  getTempName();
	memory_location_counter++;
	symrec temp(returnRec.type, memory_location_counter);
	symTable[tempName] = temp;
	if (returnRec.type == TINT) {
		genCode = I_LOAD + ' ' + to_string(returnRec.location) + '\n' + I_STORE + ' ' + to_string(memory_location_counter) + '\n';
	} else {
		genCode = F_LOAD +  ' ' + to_string(returnRec.location) + '\n' + F_STORE + ' ' + to_string(memory_location_counter) + '\n';
	}
	char *value = (char *)malloc (genCode.length() + 1);
	copy(genCode.begin(), genCode.end(), value);
	value[genCode.length()] = '\0';
	char *tname= (char *)malloc (tempName.length() + 1);
	copy(tempName.begin(), tempName.end(), tname);
	tname[tempName.length()] = '\0';
	struct synAttr *attr = (struct synAttr *) malloc(sizeof(struct synAttr));
	attr->genCode = value;
	attr->tempName = tname;
	return attr;
}

char *assignAction(char *idName, string varName){
	string id(idName);
	symrec returnedId = symTable[idName];
	string code = "";
	if (returnedId.type == TINT) {
		if (varName != "") {
			symrec varRec = symTable[varName];
			code += I_LOAD + ' ' + to_string(varRec.location) + '\n';
		}
		code += I_STORE + ' ' + to_string(returnedId.location);
	} else {
		if (varName != "") {
			symrec varRec = symTable[varName];
			code += F_LOAD + ' ' + to_string(varRec.location) + '\n';
		}
		code += F_STORE + ' ' + to_string(returnedId.location);
	}
	char *value = (char *)malloc (code.length() + 1);
	copy(code.begin(), code.end(), value);
	value[code.length()] = '\0';
	return value;
}

string getFloatIntOp(symrec op1, symrec op2, string operation1, string operation2, string n1, string n2) {
	string genCode;
	if(n1 != "") genCode = operation1 + ' ' + to_string(op1.location) + "\n", memory_location_counter--, temp_counter--, symTable.erase(n1);
	if(n2 != "") genCode += operation2 + ' ' + to_string(op2.location) + "\n", memory_location_counter--, temp_counter--, symTable.erase(n2);
	genCode += "f";
	return genCode;
}

struct synAttr *performOperation(string n1, string n2, char *opera) {
	symrec op1 = symTable[n1];
	symrec op2 = symTable[n2];
	string genCode;
	int type;
	if(op1.type == TFLOAT || op2.type == TFLOAT) {
		if(op1.type == TFLOAT && op2.type == TINT) {
			genCode = getFloatIntOp(op1, op2, F_LOAD, I_LOAD, n1, n2);
		} else if(op1.type == TINT && op2.type == TFLOAT) {
			genCode = getFloatIntOp(op1, op2, I_LOAD, F_LOAD, n1, n2);
		} else {
			genCode = getFloatIntOp(op1, op2, F_LOAD, F_LOAD, n1, n2);
		}
		type = TFLOAT;
	} else {
		if(n1 != "")
			genCode = I_LOAD + " " + to_string(op1.location) + "\n", memory_location_counter--, temp_counter--, symTable.erase(n1);
		if(n2 != "")
			genCode = I_LOAD + " " + to_string(op2.location) + "\n", memory_location_counter--, temp_counter--, symTable.erase(n2);
		genCode += "i";
		type = TINT;
	}
	switch(*opera) {
		case '+' :
			genCode += ADD;
			break;
		case '-' :
			genCode += SUB;
			break;
		case '*' :
			genCode += MUL;
			break;
		case '/' :
			genCode += DIV;
			break;
		default :
			break;
	}
	genCode += '\n';
	string tempName = getTempName();
	memory_location_counter++;
	symrec tempRec(type, memory_location_counter);
	symTable[tempName] = tempRec;
	if(type == TINT) {
		genCode += I_STORE;
	} else {
		genCode += F_STORE;
	}
	genCode += " " + to_string(memory_location_counter) + '\n';
	cout<<"geeen code "<<genCode<<endl;
	char *value = (char *)malloc (genCode.length() + 1);
	copy(genCode.begin(), genCode.end(), value);
	value[genCode.length()] = '\0';
	char *tname= (char *)malloc (tempName.length() + 1);
	copy(tempName.begin(), tempName.end(), tname);
	tname[tempName.length()] = '\0';
	struct synAttr *attr = (struct synAttr *) malloc(sizeof(struct synAttr));
	attr->genCode = value;
	attr->tempName = tname;
	return attr;
}

string genIfCode(string tempName1, string relOp, string tempName2) {
	symrec sym1 = symTable[tempName1];
	symrec sym2 = symTable[tempName2];
	string code;
	cout << ">>>>>>>>>>>>>> " << sym1.type << "\t" << sym2.type << endl;
	bool sym1Float = (sym1.type == TFLOAT);
	bool sym2Float = (sym2.type == TFLOAT);
	
	if (sym1.location != 0)
		code += (sym1Float ? F_LOAD : I_LOAD) + " " + to_string(sym1.location) + "\n";
	if (sym2Float && !sym1Float)
		code += I2F + "\n";
	if (sym2.location != 0)
		code += (sym2Float ? F_LOAD : I_LOAD) + " " + to_string(sym2.location) + "\n";
	if (sym1Float && !sym2Float)
		code += I2F + "\n";
		
	if (sym1Float || sym2Float) {
		code += FCMPL + "\n";
		if (relOp == "==") {
			code += IFNEZ;
		} else if (relOp == "!=") {
			code += IFEZ;
		} else if (relOp == "<") {
	      		code += IFLEZ;
		} else if (relOp == ">") {
			code += IFGEZ;
		} else if (relOp == "<=") {
			code += IFLTZ;
		} else if (relOp == ">=") {
			code += IFGTZ;
		}
	} else {
		if (relOp == "==") {
			code += IFNE;
		} else if (relOp == "!=") {
			code += IFE;
		} else if (relOp == "<") {
	      		code += IFGE;
		} else if (relOp == ">") {
			code += IFLE;
		} else if (relOp == "<=") {
			code += IFGT;
		} else if (relOp == ">=") {
			code += IFLT;
		}
	}
	code += " " + getNewLabel() + "\n";
	return  code;
}

string getNewLabel() {
	return string("label_") + to_string(++label_counter);
}

string getCurrentLabel() {
	return string("label_") + to_string(label_counter);
}

string getEndDelimiter(string* code) {
	string endDelimiter = "\n";
	int i = code->length();
	while(--i >= 0) {
		if (code->operator[] (i) == '\n') {
			i++;
			break;
		}
	}
	string suffix = code->substr(i);
	if (suffix.substr(0, string("label").length()) == string("label")) {
		endDelimiter = " ";
	}
	return endDelimiter;
}


string generateSignCode(string term,char* sign){
 	string genCode="";
 	if(*sign == '+')
    		return genCode;
 	symrec temp = symTable[term];
 	string mul;
 	string store;
 	if(temp.type == TINT){
  		if (temp.location != 0)
  			genCode+= I_LOAD +" " +to_string(temp.location)+"\n";
  		mul="i"+ MUL;
  		store =I_STORE;
	 }else{
              if (temp.location != 0)
  			genCode+=F_LOAD + " " +to_string(temp.location)+"\n";
  		mul = "f"+MUL;
 		store=F_STORE;
 	}

 	genCode+=NEGATIVE+"\n";
 	genCode+=mul+"\n";
 	if (temp.location != 0)
 		genCode+=store+" "+to_string(temp.location)+"\n";
 return genCode;
}


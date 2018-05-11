#ifdef HEADER_H
#define HEADER_H

typedef struct synAttr {
     string tempName = 0;
     char *genCode;
     synAttr(string tempName, char *genCode){
	this->tempName = tempName;
	this->genCode = genCode;
     }
} synAttr;


#endif

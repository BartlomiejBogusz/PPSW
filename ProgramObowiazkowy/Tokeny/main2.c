#define NULL 0
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3

typedef enum TokenType {KEYWORD, NUMBER, STRING} TokenType;

typedef enum KeywordCode {LD, ST, RST} KeywordCode;

typedef union TokenValue
{
	enum KeywordCode eKeyword;
	unsigned int uiNumber;
	char *pcString;
} TokenValue;

typedef struct Token
{
	enum TokenType eType;
	union TokenValue uValue;
} Token;

struct Token asToken[MAX_TOKEN_NR];

typedef struct Keyword
{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
} Keyword;

struct Keyword asKeywordList[MAX_KEYWORD_NR]=
{
{RST,"reset"},
{LD, "load" },
{ST, "store"}
};


enum Result {OK, ERROR};
enum CompResult {DIFFERENT,EQUAL};
enum Result eResult;

enum CompResult eCompareString(char pcStr1[], char pcStr2[]){
	
	unsigned char ucLicznikZnakow;
	
	for(ucLicznikZnakow=0; pcStr1[ucLicznikZnakow]==pcStr2[ucLicznikZnakow]; ucLicznikZnakow++){
		if(NULL==pcStr1[ucLicznikZnakow] & NULL==pcStr2[ucLicznikZnakow]){
			return EQUAL;
		}
	}
	return DIFFERENT;
}



enum Result eStringToKeyword(char pcStr[], enum KeywordCode *peKeywordCode){
	
	unsigned char ucTokenCounter;
	
	for(ucTokenCounter=0; ucTokenCounter < MAX_TOKEN_NR; ucTokenCounter++){
		if(eCompareString(pcStr, asKeywordList[ucTokenCounter].cString) == EQUAL){
			*peKeywordCode = asKeywordList[ucTokenCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}

int main(){
	char cStr[] = "load";
	enum KeywordCode eKeywordCode;
	eResult = eStringToKeyword(cStr, &eKeywordCode);
}

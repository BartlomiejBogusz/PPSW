#define NULL 0
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3
char cTest[] = "load 0x20 xD";
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

//------------------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------------------------

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue){
	
	unsigned char ucCharacterCounter;
	unsigned char ucCurrentCharacter;
	
	*puiValue = 0;
	
	if((pcStr[0]!='0') || (pcStr[1]!='x') || (pcStr[2]==NULL)){
		return ERROR;
	}
	for(ucCharacterCounter=2; pcStr[ucCharacterCounter] != NULL; ucCharacterCounter++){
		ucCurrentCharacter = pcStr[ucCharacterCounter];
		if(ucCharacterCounter >= 6){
			return ERROR;
		}
		*puiValue = *puiValue << 4;
		if((ucCurrentCharacter >= '0') && (ucCurrentCharacter <= '9')){
			ucCurrentCharacter = ucCurrentCharacter - '0';
		}
		else if((ucCurrentCharacter >= 'A') && (ucCurrentCharacter <= 'F')){
			ucCurrentCharacter = ucCurrentCharacter - 'A' + 10;
		}
		else{
			return ERROR;
		}
		*puiValue = *puiValue | ucCurrentCharacter;
	}
	return OK;
}

//--------------------------------------------------------------------------------------

unsigned char ucTokenNr = 0;
unsigned char ucFindTokenInString(char *pcString){
	
	enum State {TOKEN, DELIMITER};
	enum State eState = DELIMITER;
	unsigned char ucCharacterCounter;
	unsigned char ucCurrentCharacter;
	
	for(ucCharacterCounter=0;;ucCharacterCounter++){
		ucCurrentCharacter = pcString[ucCharacterCounter];                     //*(pcString+ucCharacterCounter)
		switch(eState){
			case DELIMITER:
				if(ucCurrentCharacter == NULL){
					return ucTokenNr;
				}
				else if(ucCurrentCharacter == ' '){}
				else{
					eState = TOKEN;
					asToken[ucTokenNr].uValue.pcString = pcString + ucCharacterCounter;  //pcString to zmienna majaca w sobie adres innej zmiennej typu char. W tym przypadku ten adres to pcString + ucCharacterCounter.
					ucTokenNr++;
				}
				break;
			case TOKEN:
				if(ucCurrentCharacter == NULL){
					return ucTokenNr;
				}
				else if(ucTokenNr == MAX_TOKEN_NR){
					return ucTokenNr;
				}
				else if(ucCurrentCharacter != ' '){
					eState = TOKEN;
				}
				else{
					eState = DELIMITER;
				}
				break;
		}
	}
}

//------------------------------------------------------------------------------------------------------

void DecodeTokens(void){
	
	unsigned char ucTokenCounter;
	Token *tValue;
	enum KeywordCode eTokenCode;
	unsigned int uiTokenValue;
	
	for(ucTokenCounter=0; ucTokenCounter<ucTokenNr; ucTokenCounter++){
		
		tValue = &asToken[ucTokenCounter];
		
		if(eStringToKeyword(tValue->uValue.pcString, &eTokenCode) == OK){
			tValue->eType = KEYWORD;
			tValue->uValue.eKeyword = eTokenCode;
		}
		else if(eHexStringToUInt(tValue->uValue.pcString, &uiTokenValue) == OK){
			tValue->eType = NUMBER;
			tValue->uValue.uiNumber = uiTokenValue;
		}
		else{
			tValue->eType = STRING;
		}
	}
}

//---------------------------------------------------------------------------------------------

void ReplaceCharaktersInString(char pcString[], char cOldChar, char cNewChar){
	
	unsigned int ucLicznikZnakow;
	
	for(ucLicznikZnakow=0; pcString[ucLicznikZnakow]!=NULL; ucLicznikZnakow++){
		if(pcString[ucLicznikZnakow]==cOldChar){
			pcString[ucLicznikZnakow]=cNewChar;
		}
	}
}

//----------------------------------------------------------------------------------------------

void DecodeMsg(char *pcString){
	ucFindTokenInString(pcString);
	ReplaceCharaktersInString(pcString, ' ', NULL);
	DecodeTokens();
}

int main(){
	enum KeywordCode eKeywordCode;
	DecodeMsg(cTest);
	eResult = eStringToKeyword(cTest, &eKeywordCode);
}

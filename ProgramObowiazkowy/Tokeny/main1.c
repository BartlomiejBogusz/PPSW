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

int main(){
	char pcStr[] = "ma sa";
	ucTokenNr = ucFindTokenInString(pcStr);
}

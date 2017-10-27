%{
    #include "hash.h"
	#include "y.tab.h"

	int lineNumber = 1;
	int running = 1;

	int getLineNumber();
	int isRunning();
	void initMe();
%}

%x COMMENT

%%

"byte"										{return KW_BYTE;}
"short" 									{return KW_SHORT;}
"long" 										{return KW_LONG;}
"float" 									{return KW_FLOAT;}
"double" 									{return KW_DOUBLE;}
"if" 										{return KW_IF;}
"then" 										{return KW_THEN;}
"else" 										{return KW_ELSE;}
"while" 									{return KW_WHILE;}
"for" 										{return KW_FOR;}
"read" 										{return KW_READ;}
"print" 									{return KW_PRINT;}
"return" 									{return KW_RETURN;}

[\(\)\[\]\{\}\+\-\*\/\<\>\$]				{return yytext[0];}
[,;:-=!&#] 									{return yytext[0];}

"<=" 										{return OPERATOR_LE;}
">=" 										{return OPERATOR_GE;}
"==" 										{return OPERATOR_EQ;}
"!=" 										{return OPERATOR_NE;}
"&&" 										{return OPERATOR_AND;}
"||" 										{return OPERATOR_OR;}

[a-zA-Z_]([a-zA-Z_0-9 ]*[a-zA-Z_0-9])* 		{hashInsert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER;}
[0-9]+ 										{hashInsert(LIT_INTEGER, yytext); return LIT_INTEGER;}
[0-9]+\.[0-9]+ 								{hashInsert(LIT_REAL, yytext); return LIT_REAL;}
'([^'\\\n]?|\\.)'							{hashInsert(LIT_CHAR, yytext); return LIT_CHAR;}
\"([^\"\\\n]|\\.)*\"						{hashInsert(LIT_STRING, yytext); return LIT_STRING;}

"\n" 										{lineNumber++;}
"//".*
"/*" 										{BEGIN(COMMENT);}

[ \t]										{}
. 											{return TOKEN_ERROR;}

<COMMENT>"\n" 								{lineNumber++;}
<COMMENT>.									{}
<COMMENT>"*/" 								{BEGIN(INITIAL);}

%%

int getLineNumber(void)
{
	return lineNumber;
}

int isRunning(void)
{
	return running;
}

void initMe(void)
{
	running = 1;
	lineNumber = 1;
	hashInit();
}

int yywrap(void)
{
	running = 0;
	return 1;
}
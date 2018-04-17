%{
	/*
		UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
		INSTITUTO DE INFORMÁTICA   
		INF01147 - Compiladores - 2017/2
		Prof. Dr. Marcelo Johann

		ETAPA 3
		220485 - Leonardo Bissani
		208783 - Paulo Ricardo Delwing
	*/

    #include "hash.h"
    #include "ast.h"
	#include "y.tab.h"

	int lineNumber = 1;
	int running = 1;

	int getLineNumber();
	int isRunning();
	void initMe();
%}

%option nounput
%option noinput

%x COMMENT

%%

	static int initialized = 0;
	
	if (!initialized)
	{
		initMe();
		initialized = 1;
	}

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

[a-zA-Z_]([a-zA-Z_0-9 ]*[a-zA-Z_0-9])* 		{ yylval.symbol = hashInsert(SYMBOL_NAO_DEFINIDO,  yytext, DATATYPE_NAO_DEFINIDO, lineNumber); return TK_IDENTIFIER; }
[0-9]+ 										{ yylval.symbol = hashInsert(SYMBOL_LIT, yytext, DATATYPE_INTEIRO, lineNumber); return LIT_INTEGER; }
[0-9]+\.[0-9]+ 								{ yylval.symbol = hashInsert(SYMBOL_LIT, yytext, DATATYPE_CHAR, lineNumber); return LIT_REAL; }
'([^'\\\n]?|\\.)'							{ yylval.symbol = hashInsert(SYMBOL_LIT, yytext, DATATYPE_STRING, lineNumber); return LIT_CHAR; }
\"([^\"\\\n]|\\.)*\"						{ yylval.symbol = hashInsert(SYMBOL_LIT, yytext, DATATYPE_REAL, lineNumber); return LIT_STRING; }

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
%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "hash.h"
	#include "lex.yy.h"

	int getLineNumber();
	int yyerror();
	int yylex();
%}

%token KW_BYTE
%token KW_SHORT
%token KW_LONG
%token KW_FLOAT
%token KW_DOUBLE
%token KW_IF
%token KW_THEN	
%token KW_ELSE
%token KW_WHILE	
%token KW_FOR
%token KW_READ	
%token KW_PRINT	
%token KW_RETURN	
%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE	
%token OPERATOR_AND	
%token OPERATOR_OR	
%token <symbol>TK_IDENTIFIER
%token <symbol>LIT_INTEGER
%token <symbol>LIT_CHAR
%token <symbol>LIT_STRING
%token <symbol>LIT_REAL
%token TOKEN_ERROR

%union
{
	HASH_NODE *symbol;
}

%left '<' '>' '!'
%left OPERATOR_LE 
%left OPERATOR_EQ 
%left OPERATOR_NE
%left OPERATOR_GE
%left OPERATOR_AND
%left OPERATOR_OR
%left '+' '-'
%left '*' '/'

%%	

Declaracao_global:
		Declaracao_local
	| 	Declaracao_global Declaracao_local
	;	

Declaracao_local:
		Variavel_Global ';'
	| 	Funcao
	;

Variavel_Global:
		Variavel
	|	Vetor
	;	
	
Variavel:
		TK_IDENTIFIER ':' Tipo '=' Literal
	;
	
Tipo:
		KW_BYTE
	|	KW_SHORT
	|	KW_LONG
	|	KW_FLOAT
	|	KW_DOUBLE
	;
	
Literal:
		LIT_INTEGER
	|	LIT_CHAR
	|	LIT_REAL
	;
	
Vetor:
		TK_IDENTIFIER ':' Tipo '[' LIT_INTEGER ']'
	|	TK_IDENTIFIER ':' Tipo '[' LIT_INTEGER ']' Lista_Literais
	;
	
Lista_Literais:
		Literal
	|	Literal Lista_Literais
	;
	
Funcao:
		'(' Tipo ')' TK_IDENTIFIER '(' ')' Bloco_Comandos
	|	'(' Tipo ')' TK_IDENTIFIER '(' Lista_Parametros ')' Bloco_Comandos
	;
	
Bloco_Comandos:
		'{' Lista_Comandos '}'
	;
	
Lista_Comandos:
		Comando
	|	Comando ';' Lista_Comandos
	;
	
Comando:
		Atribuicao
	|	Controle_Fluxo
	|	Read
	|	Print
	|	Return
	|	Bloco_Comandos
	|
	;
	
Atribuicao:
		TK_IDENTIFIER '=' Expressao
	|	TK_IDENTIFIER '[' Expressao	']' '=' Expressao
	;
	
Expressao:
		TK_IDENTIFIER
	|	TK_IDENTIFIER '[' Expressao ']'
	|	Literal
	|	'(' Expressao ')'
	|	Expressao '<' Expressao
	|	Expressao '>' Expressao
	|	Expressao '!' Expressao
	|	Expressao '-' Expressao
	|	Expressao '+' Expressao
	|	Expressao '*' Expressao
	|	Expressao '/' Expressao
	|	Expressao OPERATOR_LE Expressao
	|	Expressao OPERATOR_GE Expressao
	|	Expressao OPERATOR_EQ Expressao
	|	Expressao OPERATOR_NE Expressao
	|	Expressao OPERATOR_AND Expressao
	|	Expressao OPERATOR_OR Expressao
	|	TK_IDENTIFIER '(' ')'
	|	TK_IDENTIFIER '(' Lista_Expressoes ')'
	;

Lista_Expressoes:
		Expressao
	|	Expressao ',' Lista_Expressoes
	;
	
Controle_Fluxo:
		KW_IF '(' Expressao ')' KW_THEN Comando
	|	KW_IF '(' Expressao ')' KW_THEN Comando KW_ELSE Comando
	|	KW_WHILE '(' Expressao ')' Comando
	;
	
Read:
		KW_READ '>' TK_IDENTIFIER
	;
	
Print:
		KW_PRINT Lista_Elementos
	;
	
Lista_Elementos:
		Elemento
	|	Elemento ',' Lista_Elementos
	;
	
Elemento:
		LIT_STRING
	|	Expressao
	;
	
Return:
		KW_RETURN Expressao
	;
	
Lista_Parametros:
		Parametro
	|	Parametro ',' Lista_Parametros
	;

Parametro:
		TK_IDENTIFIER ':' Tipo
	;
	
%%

int yyerror() 
{	 
	fprintf(stderr, "Erro de sintaxe na linha %d.\n", getLineNumber());
	exit(3);
}

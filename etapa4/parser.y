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

	#include <stdio.h>
	#include <stdlib.h>
	#include "hash.h"
	#include "ast.h"

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

%left '<' '>' '!'
%left OPERATOR_LE 
%left OPERATOR_EQ 
%left OPERATOR_NE
%left OPERATOR_GE
%left OPERATOR_AND
%left OPERATOR_OR
%left '+' '-'
%left '*' '/'

%type<ast> Declaracao_global Declaracao_local Variavel_Global Variavel Tipo Literal
%type<ast> Vetor Lista_Literais Funcao Bloco_Comandos Lista_Comandos Comando Atribuicao
%type<ast> Expressao Lista_Expressoes Controle_Fluxo Read Print Lista_Elementos Elemento
%type<ast> Return Lista_Parametros Parametro

%union
{
	HASH_NODE *symbol;
	AST_NODE *ast;
}

%%	

root:	
		Declaracao_global 							{ root = $1; }
		;

Declaracao_global:
			Declaracao_local						{ $$ = astCreate(AST_DEC_GLOBAL, getLineNumber(), 0, $1, 0, 0, 0); }
		|	Declaracao_global Declaracao_local		{ $$ = astCreate(AST_DEC_GLOBAL, getLineNumber(), 0, $1, $2, 0, 0); }
		;

Declaracao_local:
		Funcao										{ $$ = $1; }				
	| 	Variavel_Global	';'							{ $$ = $1; }
	;	

Variavel_Global:
		Variavel 									{ $$ = $1; }
	|	Vetor										{ $$ = $1; }
	;	
	
Variavel:
		TK_IDENTIFIER ':' Tipo '=' Literal 			{ $$ = astCreate(AST_VARIAVEL, getLineNumber(), $1, $3, $5, 0, 0); }
	;
	
Tipo:
		KW_BYTE										{ $$ = astCreate(AST_BYTE, getLineNumber(), 0, 0, 0, 0, 0); }
	|	KW_SHORT									{ $$ = astCreate(AST_SHORT, getLineNumber(), 0, 0, 0, 0, 0); }
	|	KW_LONG										{ $$ = astCreate(AST_LONG, getLineNumber(), 0, 0, 0, 0, 0); }
	|	KW_FLOAT									{ $$ = astCreate(AST_FLOAT, getLineNumber(), 0, 0, 0, 0, 0); }
	|	KW_DOUBLE									{ $$ = astCreate(AST_DOUBLE, getLineNumber(), 0, 0, 0, 0, 0); }
	;
	
Literal:
		LIT_INTEGER									{ $$ = astCreate(AST_SYMBOL, getLineNumber(), $1, 0, 0, 0, 0); }
	|	LIT_CHAR									{ $$ = astCreate(AST_SYMBOL, getLineNumber(), $1, 0, 0, 0, 0); }
	|	LIT_REAL									{ $$ = astCreate(AST_SYMBOL, getLineNumber(), $1, 0, 0, 0, 0); }
	;
	
Vetor:
		TK_IDENTIFIER ':' Tipo '[' LIT_INTEGER ']'					{ $$ = astCreate(AST_VETOR_NAO_DECLARADO, getLineNumber(), $1, $3, astCreate(AST_SYMBOL, getLineNumber(), $5, 0, 0, 0, 0), 0, 0); }
	|	TK_IDENTIFIER ':' Tipo '[' LIT_INTEGER ']' Lista_Literais	{ $$ = astCreate(AST_VETOR_DECLARADO, getLineNumber(), $1, $3, astCreate(AST_SYMBOL, getLineNumber(), $5, 0, 0, 0, 0), $7, 0); }
	;
	
Lista_Literais:
		Literal 									{ $$ = astCreate(AST_LITERAL, getLineNumber(), 0, $1, 0, 0, 0); }
	|	Literal Lista_Literais						{ $$ = astCreate(AST_LISTA_LITERAL, getLineNumber(), 0, $1, $2, 0, 0); }
	;
	
Funcao:
		'(' Tipo ')' TK_IDENTIFIER '(' ')' Bloco_Comandos					{ $$ = astCreate(AST_FUNCAO, getLineNumber(), $4, $2, 0, $7, 0); }		
	|	'(' Tipo ')' TK_IDENTIFIER '(' Lista_Parametros ')' Bloco_Comandos	{ $$ = astCreate(AST_FUNCAO, getLineNumber(), $4, $2, $6, $8, 0); }
	;
	
Bloco_Comandos:
		'{' Lista_Comandos '}'						{ $$ = astCreate(AST_BLOCO_COMANDO, getLineNumber(), 0, $2, 0, 0, 0); }
	;
	
Lista_Comandos:
		Comando 									{ $$ = astCreate(AST_COMANDO, getLineNumber(), 0, $1, 0, 0, 0); }	
	|	Comando ';' Lista_Comandos					{ $$ = astCreate(AST_LISTA_COMANDO, getLineNumber(), 0, $1, $3, 0, 0); }	
	;
	
Comando:
		Atribuicao							{ $$ = astCreate(AST_COMANDO, getLineNumber(), 0, $1, 0, 0, 0); }
	|	Controle_Fluxo						{ $$ = astCreate(AST_COMANDO, getLineNumber(), 0, $1, 0, 0, 0); }
	|	Read 								{ $$ = astCreate(AST_COMANDO, getLineNumber(), 0, $1, 0, 0, 0); }
	|	Print 								{ $$ = astCreate(AST_COMANDO, getLineNumber(), 0, $1, 0, 0, 0); }
	|	Return 								{ $$ = astCreate(AST_COMANDO, getLineNumber(), 0, $1, 0, 0, 0); }
	|	Bloco_Comandos						{ $$ = astCreate(AST_COMANDO, getLineNumber(), 0, $1, 0, 0, 0); }
	|										{ $$ = 0; }
	;
	
Atribuicao:
		TK_IDENTIFIER '=' Expressao						{ $$ = astCreate(AST_ATRIBUICAO_VAR, getLineNumber(), $1, $3, 0, 0, 0); }
	|	TK_IDENTIFIER '[' Expressao	']' '=' Expressao	{ $$ = astCreate(AST_ATRIBUICAO_VETOR, getLineNumber(), $1, $3, $6, 0, 0); }
	;
	
Expressao:
		TK_IDENTIFIER							{ $$ = astCreate(AST_IDENTIFICADOR, getLineNumber(), $1, 0, 0, 0, 0); }
	|	TK_IDENTIFIER '[' Expressao ']'			{ $$ = astCreate(AST_ID_VETOR, getLineNumber(), $1, $3, 0, 0, 0); }
	|	Literal 								{ $$ = $1; }
	|	'(' Expressao ')'						{ $$ = astCreate(AST_PARENTESES, getLineNumber(), 0, $2, 0, 0, 0); }
	|	Expressao '<' Expressao					{ $$ = astCreate(AST_LT, getLineNumber(), 0, $1, $3, 0, 0); }
	|	Expressao '>' Expressao					{ $$ = astCreate(AST_GT, getLineNumber(), 0, $1, $3, 0, 0); }
	|	Expressao '!' Expressao					{ $$ = astCreate(AST_NEG, getLineNumber(), 0, $1, $3, 0, 0); }
	|	Expressao '-' Expressao					{ $$ = astCreate(AST_SUB, getLineNumber(), 0, $1, $3, 0, 0); }
	|	Expressao '+' Expressao					{ $$ = astCreate(AST_ADD, getLineNumber(), 0, $1, $3, 0, 0); }
	|	Expressao '*' Expressao					{ $$ = astCreate(AST_MULT, getLineNumber(), 0, $1, $3, 0, 0); }
	|	Expressao '/' Expressao					{ $$ = astCreate(AST_DIV, getLineNumber(), 0, $1, $3, 0, 0); }
	|	Expressao OPERATOR_LE Expressao			{ $$ = astCreate(AST_LE, getLineNumber(), 0, $1, $3, 0, 0); }
	|	Expressao OPERATOR_GE Expressao			{ $$ = astCreate(AST_GE, getLineNumber(), 0, $1, $3, 0, 0); }
	|	Expressao OPERATOR_EQ Expressao			{ $$ = astCreate(AST_EQ, getLineNumber(), 0, $1, $3, 0, 0); }
	|	Expressao OPERATOR_NE Expressao			{ $$ = astCreate(AST_NE, getLineNumber(), 0, $1, $3, 0, 0); }
	|	Expressao OPERATOR_AND Expressao		{ $$ = astCreate(AST_AND, getLineNumber(), 0, $1, $3, 0, 0); }
	|	Expressao OPERATOR_OR Expressao			{ $$ = astCreate(AST_OR, getLineNumber(), 0, $1, $3, 0, 0); }
	|	TK_IDENTIFIER '(' ')'					{ $$ = astCreate(AST_ID_FUNCAO, getLineNumber(), $1, 0, 0, 0, 0); }
	|	TK_IDENTIFIER '(' Lista_Expressoes ')'	{ $$ = astCreate(AST_ID_FUNCAO, getLineNumber(), $1, $3, 0, 0, 0); }
	;

Lista_Expressoes:
		Expressao							{ $$ = astCreate(AST_LISTA_EXPRESSAO, getLineNumber(), 0, $1, 0, 0, 0); }
	|	Expressao ',' Lista_Expressoes		{ $$ = astCreate(AST_LISTA_EXPRESSAO, getLineNumber(), 0, $1, $3, 0, 0); }
	;
	
Controle_Fluxo:
		KW_IF '(' Expressao ')' KW_THEN Comando 					{ $$ = astCreate(AST_IF, getLineNumber(), 0, $3, $6, 0, 0); }
	|	KW_IF '(' Expressao ')' KW_THEN Comando KW_ELSE Comando 	{ $$ = astCreate(AST_IF_ELSE, getLineNumber(), 0, $3, $6, $8, 0); }
	|	KW_WHILE '(' Expressao ')' Comando 							{ $$ = astCreate(AST_WHILE, getLineNumber(), 0, $3, $5, 0, 0); }
	;
	
Read:
		KW_READ '>' TK_IDENTIFIER			{ $$ = astCreate(AST_READ, getLineNumber(), $3, 0, 0, 0, 0); }
	;
	
Print:
		KW_PRINT Lista_Elementos			{ $$ = astCreate(AST_PRINT, getLineNumber(), 0, $2, 0, 0, 0); }
	;
	
Lista_Elementos:
		Elemento  							{ $$ = astCreate(AST_PRINT_LISTA_ELEMENTOS, getLineNumber(), 0, $1, 0, 0, 0); }
	|	Elemento ',' Lista_Elementos		{ $$ = astCreate(AST_PRINT_LISTA_ELEMENTOS, getLineNumber(), 0, $1, $3, 0, 0); }
	;
	
Elemento:
		LIT_STRING							{ $$ = astCreate(AST_SYMBOL, getLineNumber(), $1, 0, 0, 0, 0); }
	|	Expressao							{ $$ = astCreate(AST_PRINT_LISTA_ELEMENTOS, getLineNumber(), 0, $1, 0, 0, 0); }
	;
	
Return:
		KW_RETURN Expressao					{ $$ = astCreate(AST_RETURN, getLineNumber(), 0, $2, 0, 0, 0); }
	;
	
Lista_Parametros:
		Parametro 							{ $$ = astCreate(AST_LISTA_PARAMETROS, getLineNumber(), 0, $1, 0, 0, 0); }
	|	Parametro ',' Lista_Parametros		{ $$ = astCreate(AST_LISTA_PARAMETROS, getLineNumber(), 0, $1, $3, 0, 0); }
	;

Parametro:
		TK_IDENTIFIER ':' Tipo				{ $$ = astCreate(AST_PARAMETRO, getLineNumber(), $1, $3, 0, 0, 0); }
	;
	
%%

int yyerror() 
{	 
	fprintf(stderr, "Erro de sintaxe na linha %d.\n", getLineNumber());
	exit(3);
}

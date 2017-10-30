/*
	UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
	INSTITUTO DE INFORMÁTICA   
	INF01147 - Compiladores - 2017/2
	Prof. Dr. Marcelo Johann

	ETAPA 3
	220485 - Leonardo Bissani
	208783 - Paulo Ricardo Delwing
*/

#ifndef AST_H
#define AST_H

#include <stdio.h>

#define MAX_SONS 4

/* PROGRAMA */
#define AST_DEC_GLOBAL 1

/* IDENTIFICADOR */
#define AST_SYMBOL 2

/* TIPOS */
#define AST_FLOAT 10
#define AST_BYTE 11
#define AST_SHORT 12
#define AST_LONG 13
#define AST_DOUBLE 14
#define AST_INT	15

/* GLOBAIS */
#define VARIAVEL 21
#define AST_VETOR_NAO_DECLARADO 21
#define AST_VETOR_DECLARADO 22

/* LITERAIS */
#define AST_LITERAL 30
#define AST_LISTA_LITERAL 31

/* FUNÇÕES */
#define AST_FUNCAO 40
#define AST_LISTA_PARAMETROS 41
#define AST_PARAMETRO 42

/* COMANDOS */
#define AST_COMANDO 50
#define AST_BLOCO_COMANDO 51
#define AST_LISTA_COMANDO 52

/* PRINT, RETURN READ, ETC */
#define AST_READ 60
#define AST_PRINT 61
#define AST_PRINT_LISTA_ELEMENTOS 62
#define AST_RETURN 63

/* EXPRESSÕES */
#define AST_IDENTIFICADOR 70
#define AST_ID_VETOR 71
#define AST_ID_FUNCAO 72
#define AST_PARENTESES 73
#define AST_LISTA_EXPRESSAO 74

/* OPERADORES ARITMÉTICOS */
#define AST_ADD 80
#define AST_SUB 81
#define AST_MULT 82
#define AST_DIV 83

/* OPERADORES LÓGICOS */
#define AST_LE 90
#define AST_GE 91
#define AST_EQ 92
#define AST_NE 93
#define AST_AND 94
#define AST_OR 95
#define AST_LT 96
#define AST_GT 97
#define AST_NEG 98

/* CONTROLE DE FLUXO */
#define AST_IF 101
#define AST_IF_ELSE 102
#define AST_WHILE 103

/* ATRIBUIÇÃO */
#define AST_ATRIBUICAO_VAR 110
#define AST_ATRIBUICAO_VETOR 111

typedef struct ast_node
{
	int type;
	HASH_NODE *symbol;
	struct ast_node* sons[MAX_SONS];
} AST;

AST *root;
FILE* outputfile;

AST* astCreate(int type, HASH_NODE *symbol, AST* son0, AST* son1, AST* son2, AST* son3);
void astPrintNode(AST *node);
void astPrint(AST *node, FILE *output);

#endif

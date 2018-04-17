/*
	UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
	INSTITUTO DE INFORMÁTICA   
	INF01147 - Compiladores - 2017/2
	Prof. Dr. Marcelo Johann

	ETAPA 4
	220485 - Leonardo Bissani
	208783 - Paulo Ricardo Delwing
*/

#if !defined(SEMANTIC_H)
#define SEMANTIC_H
#include "ast.h"

typedef struct list_func
{
	AST_NODE* ast_node;
 	struct list_func* next;
} LIST_FUNC;

int checkSemantic(AST_NODE *node);
void checkDeclarations(AST_NODE *node);
void checkCorrectUse(AST_NODE *node);
void checkDataTypes(AST_NODE *node);
void checkUndeclaredSymbols();
int checkAritmeticOperation(int operator1Type, int operator2Type);

void setSymbolType(AST_NODE *node);
void setDataType(AST_NODE *node);
int verifyAttributionTypes(int type1, int type2);
void semanticError(int lineNumber, char message[]);
int equivalents(int type1, int type2);
int acceptInt(int type);
void listFuncInsert(LIST_FUNC** listFunc, AST_NODE* node);

AST_NODE* findFuncDeclaration(AST_NODE *funcall_node);

#endif
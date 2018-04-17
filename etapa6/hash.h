/*
	UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
	INSTITUTO DE INFORMÁTICA   
	INF01147 - Compiladores - 2017/2
	Prof. Dr. Marcelo Johann

	ETAPA 3
	220485 - Leonardo Bissani
	208783 - Paulo Ricardo Delwing
*/

#ifndef HASH_H
#define HASH_H
#define SYMBOL_IDENTIFIER   1
#define SYMBOL_LIT_INTEGER  2
#define SYMBOL_LIT_REAL     3
#define SYMBOL_LIT_CHAR     4
#define SYMBOL_LIT_STRING   5

#define HASH_SIZE 1223

#define SYMBOL_LIT 6
#define SYMBOL_ESCALAR 7
#define SYMBOL_VETOR 8
#define SYMBOL_FUNCAO 9
#define SYMBOL_NAO_DEFINIDO 10
#define SYMBOL_LABEL 22

#define DATATYPE_BYTE 11
#define DATATYPE_SHORT 12
#define DATATYPE_LONG 13
#define DATATYPE_FLOAT 14
#define DATATYPE_DOUBLE 15
#define DATATYPE_REAL 16
#define DATATYPE_NAO_DEFINIDO 17
#define DATATYPE_INTEIRO 18
#define DATATYPE_CHAR 19
#define DATATYPE_STRING 20
#define DATATYPE_BOOLEANO 21
#define DATATYPE_TEMP 22

typedef struct hash_node 
{
    int type;
    char* text;
    struct hash_node* next;
	int dataType;
	int lineNumber;
} HASH_NODE;

HASH_NODE* hashTable[HASH_SIZE];

void hashInit(void);
int hashAddress(char* text);
HASH_NODE* hashInsert(int type, char* text, int dataType, int lineNumber);
HASH_NODE* hashFind(char* text);
void hashPrint(void);

HASH_NODE *makeTemp();
HASH_NODE *makeLabel();
HASH_NODE *makeLabelArray(HASH_NODE *node);

#endif

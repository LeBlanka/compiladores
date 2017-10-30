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

typedef struct hash_node {
    int type;
    char* text;
    struct hash_node* next;
} HASH_NODE;

void hashInit(void);
int hashAddress(char* text);
HASH_NODE* hashInsert(int type, char* text);
HASH_NODE* hashFind(char* text);
void hashPrint(void);

#endif

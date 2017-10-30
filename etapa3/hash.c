/*
    UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
    INSTITUTO DE INFORMÁTICA   
    INF01147 - Compiladores - 2017/2
    Prof. Dr. Marcelo Johann

    ETAPA 3
    220485 - Leonardo Bissani
    208783 - Paulo Ricardo Delwing
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"
#include "ast.h"
#include "y.tab.h"

HASH_NODE* hashTable[HASH_SIZE];

void hashInit(void)
{
    int i;
    for (i = 0; i < HASH_SIZE; ++i) {
        hashTable[i] = NULL;
    }
}

int hashAddress(char* text)
{
    int i = 0;
    int address = 1;
    for (i = 0; i < strlen(text); ++i) {
        address = (address * text[i]) % HASH_SIZE + 1;
    }
    return address - 1;
}

HASH_NODE* hashInsert(int type, char* text)
{
    int address;
    HASH_NODE* newNode = NULL;

    address = hashAddress(text);

    newNode = hashFind(text);
    if (newNode == NULL) {
        newNode = (HASH_NODE*) calloc(1, sizeof(HASH_NODE));
        newNode->type = type;
        newNode->text = (char*) calloc(strlen(text)+1, sizeof(char));
        strcpy(newNode->text, text);

        newNode->next = hashTable[address];
        hashTable[address] = newNode;
    }
    return newNode;
}

HASH_NODE* hashFind(char* text)
{
    int address;
    address = hashAddress(text);

    HASH_NODE* node;

    for (node = hashTable[address]; node != NULL; node = node->next) {
        if (!strcmp(text, node->text))
            return node;
    }

    return NULL;
}

void hashPrint(void)
{
    int i = 0;
    HASH_NODE* node;

    for (i = 0; i < HASH_SIZE; ++i) {
        for (node = hashTable[i]; node != NULL; node = node->next) {
            fprintf(stderr, "Bucket %d has %s of type %d\n",
                    i, node->text, node->type);
        }
    }
}
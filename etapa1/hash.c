#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

HASH_NODE* table[HASH_SIZE];

void hashInit(void)
{
    int i;
    for (i = 0; i < HASH_SIZE; ++i) 
	{
        table[i] = 0;
    }
}

int hashAddress(char* text)
{
    int i = 0;
    int address = 1;
    for (i = 0; i < strlen(text); ++i) 
	{
        address = (address * text[i]) % HASH_SIZE + 1; 
    }
    return address - 1;
}

HASH_NODE* hashFind(char* text) 
{
    int address;
    address = hashAddress(text);
    HASH_NODE* node;
    for (node = table[address]; node != NULL; node = node->next) {
        if (!strcmp(text, node->text))
		{
            return node;
		}
    }
	return 0;
}

HASH_NODE* hashInsert(int type, char* text)
{
    int address;
    HASH_NODE* newNode;    
    address = hashAddress(text);
    if(newNode = hashFind(text))
	{
        return newNode;
    }   
    newNode = (HASH_NODE*) calloc(1, sizeof(HASH_NODE));
    newNode->type = type;
    newNode->text = (char*) calloc(strlen(text)+1, sizeof(char));
    strcpy(newNode->text, text);
	newNode->next = table[address];
    table[address] = newNode;
    return newNode;
}

void hashPrint(void) 
{
    int i = 0;
    HASH_NODE* node;
    for (i = 0; i < HASH_SIZE; ++i) {
        for (node = table[i]; node; node = node->next) {
            fprintf(stderr, "Posicao %d contem %s\n", i, node->text);
        }
    }
}



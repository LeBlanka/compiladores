#if !defined(GENCO_H)
#define GENCO_H

#include <stdio.h>
#include <stdlib.h>
#include "tac.h"
#include "hash.h"
#include "ast.h"

void tac2asm(TAC*node, FILE* output);
void genVarDeclaration(FILE* output, TAC *tac);
void genLongLiteralDeclaration(FILE *output, HASH_NODE *hashNode, TAC* tac);
void genByteLiteralDeclaration(FILE *output, HASH_NODE *hashNode, TAC* tac);

void genArrayDeclaration(FILE* output, TAC *tac);
void genByteArrayDeclaration(FILE *output, HASH_NODE *hashNode, TAC *tac);
void genLongArrayDeclaration(FILE* output, TAC *tac);

#endif
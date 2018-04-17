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
#include "semantic.h"
#include "lex.yy.h"
#include "y.tab.h"

extern AST_NODE *root;

int yyparse();

int main(int argc, char *argv[]) 
{
	yyin = fopen(argv[1], "r");
	if (argc < 3)
	{
		fprintf(stderr, "Número de argumentos inválido! Me chame com ./etapa3 arquivo-entrada arquivo-saida.\n");
		exit(1);
	}
	if (!yyin)
	{
		fprintf(stderr, "Não foi possível abrir o arquivo!\n");
		exit(2);
	}	
	yyparse();
	int numberOfSemanticErrors = checkSemantic(root);
	if(numberOfSemanticErrors)
	{
		fprintf(stderr, "\nNúmero de erros de semântica: %d!\n\n", numberOfSemanticErrors);
   		exit(4);
	}
    fprintf(stderr, "Sucesso!\n");
    FILE* output = stdout;
	output = fopen(argv[2], "w");	
	if (!output) 
	{
		fprintf(stderr, "Não foi possível abrir o arquivo de saída - %s\n", argv[2]);
		exit(2);
	}	
	astPrint(root, output);
	fprintf(stderr, "Escrita finalizada no arquivo de saída!\n");
	fclose(output);
	exit(0);
}

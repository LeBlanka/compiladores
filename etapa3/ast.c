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

AST_NODE *astCreate(int type, HASH_NODE *symbol, AST_NODE* son0, AST_NODE* son1, AST_NODE* son2, AST_NODE* son3)
{
	AST_NODE *newNode;

	if (!(newNode = (AST_NODE*) calloc(1, sizeof(AST_NODE))))
	{
		fprintf(stderr, "Erro no AST CREATE: sem memória disponível!\n");
		exit(1);
	}

	newNode->type = type;
	newNode->symbol = symbol;
	newNode->sons[0] = son0;
	newNode->sons[1] = son1;
	newNode->sons[2] = son2;
	newNode->sons[3] = son3;

	return newNode;
}

void astPrint(AST_NODE *node, FILE* output)
{
	if (node)
	{
		switch (node->type)
		{
			/* PROGRAMA */
			case AST_DEC_GLOBAL:
				astPrint(node->sons[0], output);
				if (node->sons[1])
				{
					astPrint(node->sons[1], output);
				}
				break;
			
			/* SÍMBOLO */
			case AST_SYMBOL:
				fprintf(output, "%s", node->symbol->text);
				break;

			/* TIPOS */
			case AST_FLOAT:
				fprintf(output, "float ");
				break;
			case AST_BYTE:
				fprintf(output, "byte ");
				break;
			case AST_SHORT:
				fprintf(output, "short ");
				break;
			case AST_LONG:
				fprintf(output, "long ");
				break;
			case AST_DOUBLE:
				fprintf(output, "double ");
				break;

			/* GLOBAIS */
			case AST_VARIAVEL: /* minhaVar: double 40; */
				if(node->symbol)
					fprintf(output, "%s:", node->symbol->text);

				astPrint (node->sons[0], output);
				astPrint (node->sons[1], output);
				fprintf(output, ";\n");
				break;
			
			case AST_VETOR_NAO_DECLARADO:  /* meuArray: long[5] */
				if(node->symbol)
					fprintf(output, "%s:", node->symbol->text);
				
				astPrint (node->sons[0], output);
				fprintf(output, "[");
				astPrint (node->sons[1], output);
				fprintf(output, "]");
				fprintf(output, ";\n");
				break;

			case AST_VETOR_DECLARADO:  /* meuArray2: long[10] 0 0 0 0 0 0 0 0 0 0 */
				if(node->symbol)
					fprintf(output, "%s:", node->symbol->text);
				
				astPrint (node->sons[0], output);
				fprintf(output, "[");
				astPrint (node->sons[1], output);
				fprintf(output, "] ");
				astPrint (node->sons[2], output);
				fprintf(output, ";\n");
				break;

			/* LITERAIS */
			case AST_LISTA_LITERAL: 
				astPrint (node->sons[0], output);
				astPrint (node->sons[1], output);
				break;

			case AST_LITERAL: 
				astPrint (node->sons[0], output);	
				break;

			/* FUNÇÔES */
			case AST_FUNCAO:  /* type TK_IDENTIFIER '(' lista_argumentos ')' */
				astPrint (node->sons[0], output);
				if(node->symbol)
					fprintf(output, "%s", node->symbol->text);
				fprintf(output, "(");
				if(node->sons[1])
					astPrint (node->sons[1], output);
				fprintf(output, ")\n");
				astPrint (node->sons[2], output);

				fprintf(output, ";\n");
				break;
			case AST_LISTA_PARAMETROS: 
				astPrint (node->sons[0], output);
				if (node->sons[1])
				{
					fprintf(output, ", ");
					astPrint (node->sons[1], output);
				}

				break;
			case AST_PARAMETRO: 
				astPrint (node->sons[0], output);
				if(node->symbol)
					fprintf(output, "%s", node->symbol->text);

				break;

			/* COMANDOS */
			case AST_COMANDO:
				astPrint (node->sons[0], output);
				break;
			case AST_BLOCO_COMANDO:
				fprintf(output, "{");
				fprintf(output, "\n");
				astPrint (node->sons[0], output);
				fprintf(output, "}");
				break;
			case AST_LISTA_COMANDO:
				astPrint (node->sons[0], output);
				fprintf (output, ";\n");
				astPrint (node->sons[1], output);
				break;

			/* PRINT, RETURN READ, ETC */
			case AST_READ:
				fprintf (output, "read ");
				if(node->symbol)
					fprintf(output, "%s", node->symbol->text);
				break;
			case AST_PRINT:
				fprintf (output, "print ");
				astPrint (node->sons[0], output);
				break;
			case AST_PRINT_LISTA_ELEMENTOS:
				astPrint(node->sons[0], output);
				if(node->sons[1])
				{
					fprintf(output, " ");
					astPrint(node->sons[1], output);
				}
				break;
			case AST_RETURN:
				fprintf (output, "return ");
				astPrint (node->sons[0], output);
				break;

			/* EXPRESSÕES */
			case AST_IDENTIFICADOR:
				if(node->symbol)
					fprintf(output, "%s", node->symbol->text);
				break;
			case AST_ID_VETOR:  /* TK_IDENTIFIER '[' expressao ']' */
				if(node->symbol)
					fprintf(output, "%s", node->symbol->text);

				fprintf(output, "[");
				astPrint (node->sons[0], output);
				fprintf(output, "]");
				break;
			case AST_ID_FUNCAO:  /* TK_IDENTIFIER '(' ')' | TK_IDENTIFIER '(' lista_expressoes ')' */
				if(node->symbol)
					fprintf (output, "%s", node->symbol->text);

				fprintf (output, "(");
			
				if(node->sons[0])
					astPrint (node->sons[0], output);

				fprintf (output, ")");
				break;
			case AST_LISTA_EXPRESSAO:
				astPrint(node->sons[0], output);
				if(node->sons[1])
				{
					fprintf(output, ", ");
					astPrint(node->sons[1], output);
				}
				break;
			case AST_PARENTESES:  /* '(' expressao ')' */
				fprintf (output, "(");
				astPrint (node->sons[0], output);
				fprintf (output, ")");
				break;

			/* OPERADORES ARITMÉTICOS */
			case AST_ADD:
				astPrint(node->sons[0], output);
				fprintf(output, " + ");
				astPrint(node->sons[1], output);
				break;
			case AST_SUB:
				astPrint(node->sons[0], output);
				fprintf(output, " - ");
				astPrint(node->sons[1], output);
				break;
			case AST_MULT:
				astPrint(node->sons[0], output);
				fprintf(output, " * ");
				astPrint(node->sons[1], output);
				break;
			case AST_DIV:
				astPrint(node->sons[0], output);
				fprintf(output, " / ");
				astPrint(node->sons[1], output);
				break;

    		/* OPERADORES LÓGICOS */
			case AST_OR:
				astPrint(node->sons[0], output);
				fprintf(output, " || ");
				astPrint(node->sons[1], output);
				break;
	  		case AST_AND:
    			astPrint(node->sons[0], output);
				fprintf(output, " && ");
				astPrint(node->sons[1], output);
				break;	
			case AST_NE:
		    	astPrint(node->sons[0], output);
				fprintf(output, " != ");
				astPrint(node->sons[1], output);
				break;
  			case AST_EQ:
	    		astPrint(node->sons[0], output);
				fprintf(output, " == ");
				astPrint(node->sons[1], output);
				break;
			case AST_GE:
				astPrint(node->sons[0], output);
				fprintf(output, " >= ");
				astPrint(node->sons[1], output);
				break;
			case AST_LE:
				astPrint(node->sons[0], output);
				fprintf(output, " <= ");
				astPrint(node->sons[1], output);
				break;
			case AST_LT:
				astPrint(node->sons[0], output);
				fprintf(output, " < ");
				astPrint(node->sons[1], output);
				break;
			case AST_GT:
				astPrint(node->sons[0], output);
				fprintf(output, " > ");
				astPrint(node->sons[1], output);
				break;
  			case AST_NEG:
  				astPrint(node->sons[0], output);
				fprintf(output, " ! ");
				astPrint(node->sons[1], output);
				break;

			/* CONTROLE DE FLUXO */
			case AST_IF:
				fprintf(output, "if (");
				astPrint (node->sons[0], output);
				fprintf(output, ") then\n");
				astPrint (node->sons[1], output); 
				break;
			case AST_IF_ELSE:
				fprintf(output, "if (");
				astPrint (node->sons[0], output);
				fprintf(output, ") then\n");
				astPrint (node->sons[1], output);
				fprintf(output, " else\n");
				astPrint (node->sons[2], output);
				break;
			case AST_WHILE:
	  			fprintf(output, "while (");
				astPrint (node->sons[0], output);
				fprintf(output, ")\n");
				astPrint (node->sons[1], output); 
				break;

			/* ATRIBUIÇÃO */
			case AST_ATRIBUICAO_VAR:
				fprintf(output, "%s = ", node->symbol->text);
				astPrint(node->sons[0], output);
				break;
			case AST_ATRIBUICAO_VETOR:
				if(node->symbol)
					fprintf(output, "%s", node->symbol->text);
				fprintf (output, "#");
				astPrint (node->sons[0], output);
				fprintf (output, " = ");
				astPrint (node->sons[1], output);
				break;

			default: 
				fprintf(output, "Sem correspondência!");
				break;
		}
	}
}




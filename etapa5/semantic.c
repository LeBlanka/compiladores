/*
	UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
	INSTITUTO DE INFORMÁTICA   
	INF01147 - Compiladores - 2017/2
	Prof. Dr. Marcelo Johann

	ETAPA 4
	220485 - Leonardo Bissani
	208783 - Paulo Ricardo Delwing
*/
#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

LIST_FUNC* listFunc;
int numberOfErrors;

//AST_NODE *declaredFunctions[100];
int functionsCount;

AST_NODE* findFuncDeclaration(AST_NODE *funcall_node)
{
 	LIST_FUNC *temp;
 	temp = listFunc; 
 	while (temp != 0)
 	{
  		if (temp->ast_node->symbol->text == funcall_node->symbol->text)
   			return temp->ast_node;  
  		temp = temp->next;
 	}
	return 0;
}

void listFuncInsert(LIST_FUNC** listFunc, AST_NODE* node)
{
	LIST_FUNC *newNode;	
	if (!(newNode = (LIST_FUNC*) calloc(1, sizeof(LIST_FUNC))))
	{
		fprintf(stderr, "Erro FUNC_LIST_CREATE: sem memória!\n");
		exit(1);
 	}
	newNode->ast_node = node;
	newNode->next = 0;
	if (*listFunc == 0)
	{
	 	*listFunc = newNode;
	}
	else
	{
	  	LIST_FUNC* temp = *listFunc;	  	
	  	while (temp->next != 0)
	  	{
	   		temp = temp->next;
	 	}	  
	  	temp->next = newNode;
	}
}

void setSymbolType(AST_NODE *node)
{
	switch(node->type)
	{
		case AST_PARAMETRO:
			node->symbol->type = SYMBOL_ESCALAR; 
			break;
		case AST_VARIAVEL:
			node->symbol->type = SYMBOL_ESCALAR; 
			break;
		case AST_VETOR_DECLARADO:
			node->symbol->type = SYMBOL_VETOR; 
			break;
		case AST_VETOR_NAO_DECLARADO:
			node->symbol->type = SYMBOL_VETOR; 
			break;
		case AST_FUNCAO:
			node->symbol->type = SYMBOL_FUNCAO; 
			break;
		default:
			node->symbol->type = SYMBOL_NAO_DEFINIDO; 
			break;
	}
}

void setDataType(AST_NODE *node)
{
	switch(node->sons[0]->type) 
	{
		case AST_BYTE:
			node->symbol->dataType = DATATYPE_BYTE; 
			break;
		case AST_SHORT:
			node->symbol->dataType = DATATYPE_SHORT; 
			break;
		case AST_LONG:
			node->symbol->dataType = DATATYPE_LONG; 
			break;
		case AST_FLOAT:
			node->symbol->dataType = DATATYPE_FLOAT; 
			break;
		case AST_DOUBLE:
			node->symbol->dataType = DATATYPE_DOUBLE; 
			break;
		/*case AST_LIT_INT:
			node->symbol->dataType = DATATYPE_INTEIRO;
			break;*/
		default:
			node->symbol->dataType = DATATYPE_NAO_DEFINIDO; 
			break;
	}
}

void checkUndeclaredSymbols() 
{
	int i;
	HASH_NODE *node;
	for (i = 0; i < HASH_SIZE; i++)
	{
		if (node = hashTable[i])
		{
			while (node) 
			{
				if (node->type == SYMBOL_NAO_DEFINIDO) 
				{
					semanticError(node->lineNumber, "Identificador não declarado."); /* APENAS A PRIMEIRA OCORRÊNCIA DO SÍMBOLO */
				}				
				node = node->next;
			}
		}
	}
}



void checkParams(AST_NODE *funcall_node)
{
	int numberOfParams = 0;
	AST_NODE *funcDeclaration = findFuncDeclaration(funcall_node); 	
 	/* CHAMADA DE FUNÇÃO NÃO DEFINIDA */
 	if (!funcDeclaration) 
 	{
 		semanticError(funcall_node->lineNumber, "Função não declarada.");
  		return;
 	}
	AST_NODE *nodeFuncCall, *nodeFuncDef;
	nodeFuncCall = funcall_node->sons[0];
	nodeFuncDef = funcDeclaration->sons[1];	
	if (nodeFuncCall && nodeFuncDef)
	{
		while (nodeFuncCall && nodeFuncDef)
		{
			numberOfParams++;			
			if (!equivalents(nodeFuncCall->sons[0]->dataType, nodeFuncDef->sons[0]->dataType) && !(acceptInt(nodeFuncDef->sons[0]->dataType) && nodeFuncCall->sons[0]->dataType == DATATYPE_INTEIRO))
			{
				semanticError(funcall_node->lineNumber, "Chamada de função tem tipos diferentes da sua definição.");
			}
			nodeFuncDef = nodeFuncDef->sons[1];
			nodeFuncCall = nodeFuncCall->sons[1];
		}
	}
	if (nodeFuncDef)
	{
		semanticError(funcall_node->lineNumber, "Menos argumentos que o necessário para a função.");
	}	
	if (nodeFuncCall) 
	{
		semanticError(funcall_node->lineNumber, "Mais argumentos que o necessário para a função.");
	}
}

void checkDeclarations(AST_NODE *node) 
{
	if (!node) 
	{ 
		return; 
	}
	if (node->type == AST_VARIAVEL || node->type == AST_VETOR_NAO_DECLARADO || node->type == AST_VETOR_DECLARADO || node->type == AST_FUNCAO || node->type == AST_PARAMETRO) 
	{
		if (node->symbol->type != SYMBOL_NAO_DEFINIDO)
		{
   			if (node->symbol->type == SYMBOL_FUNCAO)
    			semanticError(node->lineNumber, "Função já foi declarada.");
			else
    			semanticError(node->lineNumber, "Identificador já foi declarado.");
		}
		setSymbolType(node);
		setDataType(node);
		node->dataType = node->symbol->dataType;
		if (node->type == AST_FUNCAO) 
		{
   			listFuncInsert(&listFunc, node);
  		}
	}
 	int i;
	for (i = 0; i < 4; i++) 
	{
		checkDeclarations(node->sons[i]);
	}
}



void checkCorrectUse(AST_NODE *node)
{
	if (!node) 
	{ 
		return; 
	}
	switch (node->type) 
	{
		case AST_VARIAVEL:
			if(node->symbol->type != SYMBOL_ESCALAR)
				semanticError(node->lineNumber, "Uso incorreto.");
			break;

		case AST_ATRIBUICAO_VAR:
			if(node->symbol->type != SYMBOL_ESCALAR)
				semanticError(node->lineNumber, "Uso incorreto.");
			break;

		case AST_ATRIBUICAO_VETOR:
			if(node->symbol->type != SYMBOL_VETOR)
				semanticError(node->lineNumber, "Uso incorreto.");
			break;

		case AST_ID_VETOR:
			if(node->symbol->type != SYMBOL_VETOR)
				semanticError(node->lineNumber, "Uso incorreto.");
			break;

		case AST_ID_FUNCAO:
			if(node->symbol->type != SYMBOL_FUNCAO)
				semanticError(node->lineNumber, "Uso incorreto.");
			break;
	}
	int s;
	for (s = 0; s < 4; s++)
	{
		checkCorrectUse(node->sons[s]);
	}
}


void checkDataTypes(AST_NODE *node)
{
	if (!node) 
	{ 
		return; 
	}
	int s;
	for (s = 0; s < 4; s++)
	{
		checkDataTypes(node->sons[s]);
	}
	switch (node->type) 
	{
		case AST_IDENTIFICADOR:
			node->dataType = node->symbol->dataType;
			break;

		case AST_SYMBOL:
			node->dataType = node->symbol->dataType;
			break;

		case AST_GE:
		case AST_LE:
		case AST_LT:
		case AST_GT:
			if (node->sons[0]->dataType == DATATYPE_BOOLEANO || node->sons[1]->dataType == DATATYPE_BOOLEANO)
			{
				semanticError(node->lineNumber, "Operação Lógica - não é esperado booleano.");
			}
			node->dataType = DATATYPE_BOOLEANO;
			break;

		case AST_OR:
		case AST_AND:
			if (node->sons[0]->dataType != DATATYPE_BOOLEANO || node->sons[1]->dataType != DATATYPE_BOOLEANO)
			{
				semanticError(node->lineNumber, "Operação lógica - esperado booleano.");
			}
			node->dataType = DATATYPE_BOOLEANO;
			break;

		case AST_EQ:
		case AST_NE:
			if ((node->sons[0]->dataType == DATATYPE_BOOLEANO && node->sons[1]->dataType != DATATYPE_BOOLEANO) ||
			   (node->sons[1]->dataType == DATATYPE_BOOLEANO && node->sons[0]->dataType != DATATYPE_BOOLEANO))
			{
				semanticError(node->lineNumber, "Operação lógica - conflito de tipos.");
			}
			node->dataType = DATATYPE_BOOLEANO;
			break;

		case AST_ADD:
		case AST_SUB:
		case AST_MULT:
			if (node->sons[0]->dataType == DATATYPE_BOOLEANO || node->sons[1]->dataType == DATATYPE_BOOLEANO)
			{
				semanticError(node->lineNumber, "Operação Aritmética - não é esperado booleano.");
			}
			node->dataType = checkAritmeticOperation(node->sons[0]->dataType, node->sons[1]->dataType);
			break;

		case AST_DIV:
			if (node->sons[0]->dataType == DATATYPE_BOOLEANO || node->sons[1]->dataType == DATATYPE_BOOLEANO)
			{
				semanticError(node->lineNumber, "Operação Aritmética - não é esperado booleano.");
			}
			node->dataType = DATATYPE_FLOAT;
			break;
		case AST_PARENTESES:
			node->dataType = node->sons[0]->dataType;
			break;
		case AST_ATRIBUICAO_VAR:
			if ((!(verifyAttributionTypes(node->symbol->dataType, node->sons[0]->dataType))) && (!((node->symbol->dataType==12) || (node->symbol->dataType==13) || (node->symbol->dataType==14)) && (node->sons[0]->dataType==17)))
			{
				semanticError(node->lineNumber, "Tipos conflitantes para atribuição.");
	 		}
			break;
		case AST_ATRIBUICAO_VETOR:
			if (node->sons[0]->dataType != DATATYPE_INTEIRO) 
			{
				semanticError(node->lineNumber, "Acesso ao índice do vetor - esperado um valor inteiro.");
			}
			if (!(verifyAttributionTypes(node->symbol->dataType, node->sons[0]->dataType)))
			{
				semanticError(node->lineNumber, "Tipos conflitantes para atribuição.");
			}
			break;
		case AST_IF:
			if (node->sons[0]->dataType != DATATYPE_BOOLEANO)
			{
				semanticError(node->sons[0]->lineNumber, "Comando WHEN - esperado booleano.");
			}
			break;
		case AST_WHILE:
			if (node->sons[0]->dataType != DATATYPE_BOOLEANO)
			{
				semanticError(node->sons[0]->lineNumber, "Comando WHILE - esperado booleano.");
			}
			break;
		case AST_ID_FUNCAO:
			checkParams(node);
			node->dataType = node->symbol->dataType;
			break;
	}
}

int verifyAttributionTypes(int type1, int type2)
{
	if (type1 == DATATYPE_NAO_DEFINIDO || type2 == DATATYPE_NAO_DEFINIDO) 
	{
		return 0;
	}
	if (type1 == type2) 
	{
		return 1;
	} 
	else 
		return equivalents(type1, type2);
}

int checkAritmeticOperation(int operator1Type, int operator2Type)
{
	if (operator1Type == DATATYPE_BOOLEANO || operator2Type == DATATYPE_BOOLEANO)
	{
		return DATATYPE_NAO_DEFINIDO;
	}
	switch (operator1Type)
	{
		case DATATYPE_CHAR:
			if (operator2Type == DATATYPE_CHAR)
			{ 
				return DATATYPE_CHAR; 
			}
			if (operator2Type == DATATYPE_INTEIRO)
			{ 
				return DATATYPE_INTEIRO; 
			}			
			if (operator2Type == DATATYPE_FLOAT)
			{ 
				return DATATYPE_FLOAT; 
			}
			break;
		case DATATYPE_FLOAT:
			return DATATYPE_FLOAT;
		case DATATYPE_INTEIRO:
			if (operator2Type == DATATYPE_CHAR)
			{ 
				return DATATYPE_INTEIRO; 
			}			
			if (operator2Type == DATATYPE_INTEIRO)
			{ 
				return DATATYPE_INTEIRO; 
			}			
			if (operator2Type == DATATYPE_FLOAT)
			{ 
				return DATATYPE_FLOAT; 
			}
			if (operator2Type == DATATYPE_LONG)
			{ 
				return DATATYPE_LONG; 
			}
			break;
		case DATATYPE_LONG:
			return DATATYPE_LONG;
	}
	return DATATYPE_NAO_DEFINIDO;
}

void semanticError(int lineNumber, char message[])
{
	numberOfErrors++;
	fprintf(stderr, "(ERRO SEMÂNTICO) linha %i - %s\n", lineNumber, message);
}


int checkSemantic(AST_NODE *node) 
{
	fprintf(stderr, "Checando semântica...\n");
	numberOfErrors = 0;
	checkDeclarations(node);
	checkUndeclaredSymbols();
	checkCorrectUse(node);
	checkDataTypes(node);
	return numberOfErrors;
}

int equivalents(int type1, int type2)
{
	switch (type1)
	{
		case DATATYPE_INTEIRO:
		case DATATYPE_CHAR:
		case DATATYPE_BYTE:
		case DATATYPE_SHORT:
		case DATATYPE_LONG:
		case DATATYPE_DOUBLE:
		case DATATYPE_FLOAT:
		case DATATYPE_REAL:
			switch (type2)
			{
				case DATATYPE_INTEIRO:
				case DATATYPE_CHAR:
				case DATATYPE_BYTE:
				case DATATYPE_SHORT:
				case DATATYPE_LONG:
				case DATATYPE_DOUBLE:
				case DATATYPE_FLOAT:
				case DATATYPE_REAL:
					return 1;
					break;

				default:
					return 0;
					break;
			}
			break;
		case DATATYPE_STRING:
			switch (type2)
			{
				case DATATYPE_STRING:
					return 1;
					break;

				default:
					return 0;
					break;
			}
			break;
		case DATATYPE_BOOLEANO:
			switch (type2)
			{
				case DATATYPE_BOOLEANO:
					return 1;
					break;
				
				default:
					return 0;
					break;
			}
			break;
		default:
			return 0;
			break;
	}
}

int acceptInt(int type)
{
	switch (type)
	{
		case DATATYPE_INTEIRO:
		case DATATYPE_CHAR:
		case DATATYPE_BYTE:
		case DATATYPE_SHORT:
		case DATATYPE_LONG:
		case DATATYPE_DOUBLE:
		case DATATYPE_FLOAT:
		case DATATYPE_REAL:
			return 1;
			break;		
		default:
			return 0;
			break;
	}
}

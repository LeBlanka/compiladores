int main(int argc, char* argv[]) 
{
    int tok;
    yyin = fopen(argv[1], "r");
    initMe();
    
    while (isRunning()) 
	{
        tok = yylex();
        if (!isRunning()) 
		{
            break;
        }
        
        switch(tok) 
		{
			case KW_BYTE:
				fprintf(stderr, "KW_BYTE - linha %i\n", getLineNumber());
				break;
			case KW_SHORT:
				fprintf(stderr, "KW_SHORT - linha %i\n", getLineNumber());
				break;
			case KW_LONG:
				fprintf(stderr, "KW_LONG - linha %i\n", getLineNumber());
				break;
			case KW_FLOAT:
				fprintf(stderr, "KW_FLOAT - linha %i\n", getLineNumber());
				break;
			case KW_DOUBLE:
				fprintf(stderr, "KW_DOUBLE - linha %i\n", getLineNumber());
				break;
			case KW_IF:
				fprintf(stderr, "KW_IF - linha %i\n", getLineNumber());
				break;
			case KW_THEN:
				fprintf(stderr, "KW_THEN - linha %i\n", getLineNumber());
				break;
			case KW_ELSE:
				fprintf(stderr, "KW_ELSE - linha %i\n", getLineNumber());
				break;
			case KW_WHILE:
				fprintf(stderr, "KW_WHILE - linha %i\n", getLineNumber());
				break;
			case KW_FOR:
				fprintf(stderr, "KW_FOR - linha %i\n", getLineNumber());
				break;
			case KW_READ:
				fprintf(stderr, "KW_READ - linha %i\n", getLineNumber());
				break;
			case KW_RETURN:
				fprintf(stderr, "KW_RETURN - linha %i\n", getLineNumber());
				break;
			case KW_PRINT:
				fprintf(stderr, "KW_PRINT - linha %i\n", getLineNumber());
				break;			
			case OPERATOR_LE:
				fprintf(stderr, "OPERATOR_LE - linha %i\n", getLineNumber());
				break;
			case OPERATOR_GE:
				fprintf(stderr, "OPERATOR_GE - linha %i\n", getLineNumber());
				break;
			case OPERATOR_EQ:
				fprintf(stderr, "OPERATOR_EQ - linha %i\n", getLineNumber());
				break;
			case OPERATOR_NE:
				fprintf(stderr, "OPERATOR_NE - linha %i\n", getLineNumber());
				break;
			case OPERATOR_AND:
				fprintf(stderr, "OPERATOR_AND - linha %i\n", getLineNumber());
				break;
			case OPERATOR_OR:
				fprintf(stderr, "OPERATOR_OR - linha %i\n", getLineNumber());
				break;			
			case TK_IDENTIFIER:
				fprintf(stderr, "TK_IDENTIFIER - linha %i\n", getLineNumber());
				break;
			case LIT_INTEGER:
				fprintf(stderr, "LIT_INTEGER - linha %i\n", getLineNumber());
				break;
			case LIT_REAL:
				fprintf(stderr, "LIT_REAL - linha %i\n", getLineNumber());
				break;
			case LIT_CHAR:
				fprintf(stderr, "LIT_CHAR - linha %i\n", getLineNumber());
				break;   
			case LIT_STRING:
				fprintf(stderr, "LIT_STRING - linha %i\n", getLineNumber());
				break;			
			case TOKEN_ERROR:
				fprintf(stderr, "TOKEN_ERROR - linha %i\n", getLineNumber());
				break;			
			default:
				fprintf(stderr, "%c - linha %i\n", tok, getLineNumber());
				break;
        }
    }
    fprintf(stderr, "\n\n------------------ HASH TABLE ------------------\n");
    hashPrint();
    fprintf(stderr, "------------------------------------------------\n");
    return 0;
}
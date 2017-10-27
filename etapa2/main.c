#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "lex.yy.h"
#include "y.tab.h"

int main(int argv, char *argc[]) {

    if (argv < 2) {
        fprintf(stderr, "Missing arguments.\n");
        exit(1);
    }

    yyin = fopen(argc[1], "r");

    if (!yyin) {
        fprintf(stderr, "Cannot open file - %s\n", argc[1]);
    }

    yyparse();
    

    hashPrint();
    exit(0);

}

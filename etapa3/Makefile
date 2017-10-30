#	UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
#	INSTITUTO DE INFORMÁTICA   
#	INF01147 - Compiladores - 2017/2
#	Prof. Dr. Marcelo Johann
#
#	ETAPA 3
#	220485 - Leonardo Bissani
#	208783 - Paulo Ricardo Delwing

etapa3: y.tab.o lex.yy.o hash.o ast.o main.o 
	gcc lex.yy.o hash.o ast.o main.o y.tab.o -o etapa3

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

y.tab.c: parser.y lex.yy.c
	yacc -d parser.y

lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l

ast.o: ast.c
	gcc -c ast.c

clean:
	rm -f *.o etapa3 lex.yy.c lex.yy.h y.tab.c y.tab.h

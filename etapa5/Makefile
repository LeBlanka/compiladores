#	UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
#	INSTITUTO DE INFORMÁTICA   
#	INF01147 - Compiladores - 2017/2
#	Prof. Dr. Marcelo Johann
#
#	ETAPA 4
#	220485 - Leonardo Bissani
#	208783 - Paulo Ricardo Delwing

etapa4: y.tab.o lex.yy.o hash.o ast.o tac.o semantic.o main.o
	gcc lex.yy.o hash.o ast.o tac.o semantic.o main.o y.tab.o -o etapa5

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

tac.o: tac.c
	gcc -c tac.c -Wall
	
semantic.o: semantic.c
	gcc -c semantic.c

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

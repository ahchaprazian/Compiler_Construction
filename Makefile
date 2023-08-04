bminor: main.o scanner.o parser.o type.o stmt.o expr.o param_list.o decl.o stack.o hash_table.o symbol.o
	gcc main.o scanner.o parser.o type.o stmt.o expr.o param_list.o decl.o stack.o hash_table.o symbol.o -o bminor

main.o: main.c token.h parser.c
	gcc main.c -c -o main.o

scanner.o: scanner.c token.h parser.c
	gcc scanner.c -c -o scanner.o

scanner.c: scanner.flex
	flex -oscanner.c scanner.flex

parser.o: parser.c token.h
	gcc parser.c -c -o parser.o

parser.c token.h: parser.bison
	bison -t -v --defines=token.h --output=parser.c parser.bison

decl.o: decl.c decl.h
	gcc decl.c -c -o decl.o

type.o: type.c type.h
	gcc type.c -c -o type.o

stmt.o: stmt.c stmt.h
	gcc stmt.c -c -o stmt.o

expr.o: expr.c expr.h
	gcc expr.c -c -o expr.o

stack.o: stack.c stack.h
	gcc stack.c -c -o stack.o

symbol.o: symbol.c symbol.h
	gcc symbol.c -c -o symbol.o

hash_table.o: hash_table.c hash_table.h
	gcc hash_table.c -c -o hash_table.o

param_list.o: param_list.c param_list.h
	gcc param_list.c -c -o param_list.o

clean:
	rm -f main.o scanner.c scanner.o parser.c parser.o type.o stmt.o expr.o param_list.o decl.o stack.o hash_table.o symbol.o bminor

rmOut:
	rm *.bminor.out
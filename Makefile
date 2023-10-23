all: tests reconocedor

reconocedor: reconocedor_automata.o
		gcc  main.c reconocedor_automata.o -o tablaToken

reconocedor_automata.o : reconocedor_automata.c
		gcc -c reconocedor_automata.c

ReconocedorTest: reconocedor_automata.o
	gcc tests.c reconocedor_automata.o -o test

tests: ReconocedorTest
	test

clean:
	del /q test.exe reconocedor_automata.o tablaToken.exe
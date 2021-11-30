assembler: structers.o main.o symbolTable.o parseLines.o memoryList.o code.o data.o files.o
			gcc -g -Wall -ansi -pedantic structers.o main.o symbolTable.o parseLines.o memoryList.o code.o data.o files.o -o assembler
main.o: main.c global.h lists.h main.h
			gcc -c -Wall -ansi -pedantic main.c -o main.o
symbolTable.o: symbolTable.c global.h lists.h symbolTable.h
			gcc -c -Wall -ansi -pedantic symbolTable.c -o symbolTable.o
parseLines.o: parseLines.c global.h parseLines.h structers.h
			gcc -c -Wall -ansi -pedantic parseLines.c -o parseLines.o
memoryList.o: memoryList.c global.h lists.h memoryList.h structers.h
			gcc -c -Wall -ansi -pedantic memoryList.c -o memoryList.o
code.o: code.c global.h code.h structers.h
			gcc -c -Wall -ansi -pedantic code.c -o code.o
data.o: data.c global.h data.h structers.h
			gcc -c -Wall -ansi -pedantic data.c -o data.o
structers.o: structers.c global.h structers.h
			gcc -c -Wall -ansi -pedantic structers.c -o structers.o
files.o: files.c global.h files.h
			gcc -c -Wall -ansi -pedantic files.c -o files.o

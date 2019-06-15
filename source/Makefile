all: printy
 
printy: testeKruskal.o kruscal.o
 gcc -o printy testeKruskal.o helloWorld.o
 
testeKruskal.o: testeKruskal.c helloWorld.h
 gcc -o testeKruskal.o testeKruskal.c -c -W -Wall -ansi -pedantic
 
kruscal.o: kruscal.c kruscal.h
 gcc -o kruscal.o kruscal.c -c -W -Wall -ansi -pedantic
 
clean:
 rm -rf *.o *~ printy
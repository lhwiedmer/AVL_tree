parametrosCompilacao=-Wall #-Wshadow
nomePrograma=trab1_20221234_20221222

all: $(nomePrograma)

$(nomePrograma): main.o avl.o libfila.o
	gcc -o $(nomePrograma) main.o avl.o libfila.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

avl.o: avl.h avl.c
	gcc -c avl.c $(parametrosCompilacao)

libfila.o: libfila.h libfila.c
	gcc -c libfila.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)

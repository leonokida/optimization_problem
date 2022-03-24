#Laura e Leon

#gcc parcial-relaxada.c parcial.c -lm -ldl -o parcial-relaxada liblpsolve55.so


CFLAGS = -Wall -lm -ldl liblpsolve55.so

objects = parcial.o

all: parcial-relaxada

parcial-relaxada: parcial-relaxada.c $(objects)
	gcc parcial-relaxada.c -o parcial-relaxada $(objects) $(CFLAGS)

parcial.o: parcial.c parcial.h
	gcc -c parcial.c $(CFLAGS)

purge: clean
	-rm -f parcial-relaxada
clean:
	-rm -f $(objects)
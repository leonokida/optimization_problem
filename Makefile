#Laura e Leon

#gcc parcial-relaxada.c parcial.c -lm -ldl -o parcial-relaxada liblpsolve55.so


CFLAGS = -Wall -lm -ldl liblpsolve55.so

objects = parcial.o

all: parcial-relaxada envio

parcial-relaxada: parcial-relaxada.c $(objects)
	gcc parcial-relaxada.c -o parcial-relaxada $(objects) $(CFLAGS)

parcial.o: parcial.c parcial.h
	gcc -c parcial.c $(CFLAGS)

envio: envio.c $(objects)
	gcc envio.c -o envio $(objects) $(CFLAGS)

purge: clean
	-rm -f parcial-relaxada envio
	-rm -f entrada.lp
clean:
	-rm -f $(objects)
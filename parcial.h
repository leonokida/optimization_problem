//Laura e Leon

#ifndef __PARCIAL__
#define __PARCIAL__

#include <stdlib.h>

/*
Struct que guarda uma restrição de par ordenado.
*/
typedef struct t_par_ordenado t_par_ordenado;
struct t_par_ordenado {
    int antes;
    int depois;
};

/*
Retorna k, que é o número mínimo de viagens necessárias.
*/
double parcial(int qtdItens, double capacidade, double * pesos, int qtdPares, t_par_ordenado * pares);

#endif
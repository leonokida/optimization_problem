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
Struct que guarda uma solução parcial do problema.
*/
typedef struct t_parciais t_parciais;
struct t_parciais {
    int indice;
    int viagem;
};

/*
Retorna k, que é o número mínimo de viagens necessárias.
*/
double parcial(int qtdItens, double capacidade, double * pesos, int qtdPares, t_par_ordenado * pares, int l, t_parciais * parciais);

#endif
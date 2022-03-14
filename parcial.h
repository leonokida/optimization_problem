#include <stdlib.h>

/*
Struct que guarda os pares ordenados de restrição.
*/
typedef struct t_par_ordenado t_par_ordenado;
struct t_par_ordenado {
    int antes;
    int depois;
};

/*
Retorna k, que é o número mínimo de viagens necessárias.
*/
double parcial(int qtdItens, double capacidade, double * pesos, t_par_ordenado * pares);
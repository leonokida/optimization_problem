#include "parcial.h"
#include <stdio.h>

#include "lp_lib.h"

double parcial(int qtdItens, double capacidade, double * pesos, t_par_ordenado * pares) {
    printf("qtdItens: %d, capacidade: %lf\n", qtdItens, capacidade);
    printf("Peso 1: %lf\n", pesos[0]);
    printf("Antes 1: %d, Depois 1: %d\n", pares[0].antes, pares[0].depois);

    //system("lp_solve -h");
}
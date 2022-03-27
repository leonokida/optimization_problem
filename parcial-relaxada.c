#include <stdio.h>
#include <stdlib.h>
#include "parcial.h"

int main() {
    int qtdItens, qtdPares;
    double capacidade;

    scanf("%d", &qtdItens);
    scanf("%d", &qtdPares);
    scanf("%lf", &capacidade);

    double * pesos = (double *) calloc(qtdItens, sizeof(double));
    t_par_ordenado * pares = (t_par_ordenado *) calloc(qtdPares, sizeof(t_par_ordenado));

    for (int i = 0; i < qtdItens; i++) {
        scanf("%lf", &pesos[i]);
    }

    for (int i = 0; i < qtdPares; i++) {
        scanf("%d", &pares[i].antes);
        scanf("%d", &pares[i].depois);
    }

    double resultado = parcial(qtdItens, capacidade, pesos, qtdPares, pares);

    printf("\e[1;1H\e[2J");
    printf("O valor de K é: %lf\n", resultado);

    free(pesos);
    free(pares);
    
    return 0;
}
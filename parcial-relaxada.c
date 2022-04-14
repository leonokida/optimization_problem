//Laura e Leon

#include <stdio.h>
#include <stdlib.h>
#include "parcial.h"

int main() {
    int qtdItens, qtdPares;
    double capacidade;

    scanf("%d", &qtdItens);
    scanf("%d", &qtdPares);
    scanf("%lf", &capacidade);

    //Alocando vetores para pesos e pares ordenados
    double * pesos = (double *) calloc(qtdItens, sizeof(double));
    t_par_ordenado * pares = (t_par_ordenado *) calloc(qtdPares, sizeof(t_par_ordenado));

    for (int i = 0; i < qtdItens; i++) {
        scanf("%lf", &pesos[i]);
    }

    for (int i = 0; i < qtdPares; i++) {
        scanf("%d", &pares[i].antes);
        scanf("%d", &pares[i].depois);
    }

    int l;
    scanf("%d", &l);
    t_parciais * parciais = (t_parciais *) calloc(l, sizeof(t_parciais));
    for (int i = 0; i < l; i++) {
        scanf("%d", &parciais[i].indice);
        scanf("%d", &parciais[i].viagem);
    }

    //Chama função parcial
    double resultado = parcial(qtdItens, capacidade, pesos, qtdPares, pares, l, parciais);

    printf("\e[1;1H\e[2J"); //Limpa tela
    printf("O valor de K é: %lf\n", resultado);

    free(pesos);
    free(pares);
    free(parciais);
    
    return 0;
}

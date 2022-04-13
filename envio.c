//Laura e Leon

#include <stdio.h>
#include <stdlib.h>
#include "parcial.h"



void resolucao(int qtdItens, double capacidade, double * pesos, int qtdPares, t_par_ordenado * pares, t_parciais * parciais, int itemIndice, int l, double * opt) {

    if (itemIndice > qtdItens) {        
        return;
    }

    parciais[l-1].indice = itemIndice;
    double resultado;
/*
    double resultado = parcial(qtdItens, capacidade, pesos, qtdPares, pares, l, parciais);
    if ((resultado > 0) && (resultado < *opt)) {
        *opt = resultado;
        for (int i = 2; i <= qtdItens; i++) {
            resolucao(qtdItens, capacidade, pesos, qtdPares, pares, parciais, itemIndice, i, opt);
        }
    }*/
    for (int i = 1; i <= qtdItens; i++) {
        parciais[l-1].viagem = i;
        resultado = parcial(qtdItens, capacidade, pesos, qtdPares, pares, l, parciais);
        if ((resultado > 0) && (resultado < *opt)) {
            *opt = resultado;
            l++;
            resolucao(qtdItens, capacidade, pesos, qtdPares, pares, parciais, itemIndice+1, l, opt);
        }
    }

}

void imprime(double * opt, int qtdItens, t_parciais * parciais) {
    printf("%lf\n", *opt);
    for (int i = 0; i < qtdItens; i++)
        printf("%d: %d\n", parciais[i].indice, parciais[i].viagem);
}

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

    t_parciais * parciais = (t_parciais *) calloc(qtdItens, sizeof(t_parciais));
    double opt = qtdItens;
    int l = 1;
    resolucao(qtdItens, capacidade, pesos, qtdPares, pares, parciais, 1, l, &opt);
    imprime(&opt, qtdItens, parciais);

    //Chama função parcial
    //double resultado = parcial(qtdItens, capacidade, pesos, qtdPares, pares, l, parciais);

    //printf("\e[1;1H\e[2J"); //Limpa tela
    //printf("O valor de K é: %lf\n", resultado);

    free(pesos);
    free(pares);
    
    return 0;
}

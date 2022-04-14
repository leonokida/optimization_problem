//Laura e Leon

#include <stdio.h>
#include <stdlib.h>
#include "parcial.h"
#include "math.h"

double opt;
t_parciais * resposta;

void copia(t_parciais * parciais, int qtdItens) {
	for (int i = 0; i < qtdItens; i++) {
		resposta[i].indice = parciais[i].indice;
		resposta[i].viagem = parciais[i].viagem;
	}
}

void resolucao(int qtdItens, double capacidade, double * pesos, int qtdPares, t_par_ordenado * pares, t_parciais * parciais, int itemIndice, int l, double custo) {

    if (itemIndice > qtdItens) {
        if (custo < opt) {
            opt = custo;
            copia(parciais, qtdItens);
        }

        return;
    }

    parciais[l].indice = itemIndice;
    double resultado;
    for (int i = 1; i <= qtdItens; i++) {
        parciais[l].viagem = i;
        resultado = parcial(qtdItens, capacidade, pesos, qtdPares, pares, l+1, parciais);
        if ((resultado > 0) && (resultado < opt)) {
            resolucao(qtdItens, capacidade, pesos, qtdPares, pares, parciais, itemIndice+1, l+1, resultado);
        }
    }
}

void imprime(int qtdItens) {
    printf("\e[1;1H\e[2J"); //Limpa tela

    //TODO calcular numero de viagens
    printf("%lf\n", opt);
    for (int i = 0; i < qtdItens; i++) {
        //printf("%d: %d\n", resposta[i].indice, resposta[i].viagem);
        printf("%d\n", resposta[i].viagem);
    }
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

    opt = qtdItens;

    t_parciais * parciais = (t_parciais *) calloc(qtdItens, sizeof(t_parciais));
    resposta = (t_parciais *) calloc(qtdItens, sizeof(t_parciais));
    int l = 0;
    resolucao(qtdItens, capacidade, pesos, qtdPares, pares, parciais, 1, l, qtdItens);
    imprime(qtdItens);

    free(pesos);
    free(pares);
    free(parciais);
    free(resposta);

    return 0;
}

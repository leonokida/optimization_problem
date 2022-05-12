//Laura e Leon

#include <stdio.h>
#include <stdlib.h>
#include "parcial.h"
#include "math.h"

int opt;
double limitante;
t_parciais * resposta;

int maxViagem(t_parciais * parciais, int qtdItens) {
    int max = 0;
    for (int i = 0; i < qtdItens; i++)
        if (parciais[i].viagem > max)
            max = parciais[i].viagem;
    return max;
}

void copia(t_parciais * parciais, int qtdItens) {
	for (int i = 0; i < qtdItens; i++) {
		resposta[i].indice = parciais[i].indice;
		resposta[i].viagem = parciais[i].viagem;
	}
}

int verificaPeso(double * pesos, t_parciais * parciais, double capacidade, int viagem, int l) {
    int soma = 0;
    int i;
    for (i = 0; i < l; i++) {
        if (parciais[i].viagem == viagem){
            soma += pesos[parciais[i].indice - 1];
        }
    }

    if (soma > capacidade)
        return 0;

    return 1;
}

int verificaOrdem(int qtdPares, t_par_ordenado * pares, int l, t_parciais * parciais, int itemIndice, int viagem) {

    for (int i = 0; i < qtdPares; i++) {
        if (pares[i].depois == itemIndice) {
            for (int j = 0; j < l; j++) {
                if ((parciais[j].indice == pares[i].antes) && (parciais[j].viagem >= viagem)){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int verificaCiclos(int qtdPares, t_par_ordenado * pares) {

    for (int i = 0; i < qtdPares; i++) {
        for (int j = i+1; j < qtdPares; j++) {
            if ((pares[i].antes == pares[j].depois) && (pares[i].depois == pares[j].antes)) {
                return 0;
            }
        }
    }

    return 1;
}

void resolucao(int qtdItens, double capacidade, double * pesos, int qtdPares, t_par_ordenado * pares, t_parciais * parciais, int l, int * ordemItens, int itemIndice, double custo) {

    if (l >= qtdItens) {
        int max = maxViagem(parciais, qtdItens);
        if (max < opt) {
            opt = max;
            copia(parciais, qtdItens);
        }
        return;
    }

    parciais[l].indice = ordemItens[itemIndice];
    double resultado;
    for (int i = 1; i <= qtdItens; i++) {
        parciais[l].viagem = i;

        if (verificaPeso(pesos, parciais, capacidade, i, l+1) && verificaOrdem(qtdPares, pares, l+1, parciais, ordemItens[itemIndice], i)){
            /*
            Descomentar a linha abaixo fará com que a solução do LP Solve seja usada como bound.
            resultado = parcial(qtdItens, capacidade, pesos, qtdPares, pares, l+1, parciais);
            */
            
            resultado = limitante;
            if ((resultado > 0) && (resultado < opt)) {
                resolucao(qtdItens, capacidade, pesos, qtdPares, pares, parciais, l+1, ordemItens, itemIndice+1, resultado);
            }
        }
    }
}

int buscaItem(int * ordemItens, int qtdItens, int k) {
    
    for (int j = 0; j < qtdItens; j++){
        if (ordemItens[j] == k) {
            return 1;
        }
    }
    return 0;
}

void troca(int a, int b) {
    t_parciais temp;
    temp.indice = resposta[a].indice;
    temp.viagem = resposta[a].viagem;
    resposta[a].indice = resposta[b].indice;
    resposta[a].viagem = resposta[b].viagem;
    resposta[b].indice = temp.indice;
    resposta[b].viagem = temp.viagem;
}

void ordenar(int qtdItens) {
    int i = 1;
    while (i < qtdItens) {
        int j = i;
        while ((j > 0) && (resposta[j-1].indice > resposta[j].indice)) {
            troca(j-1, j);
            j = j-1;
        }
        i++;
    }
}

void imprime(int qtdItens) {
    ordenar(qtdItens); // Ordena vetor de respostas

    //TODO calcular numero de viagens
    printf("%d\n", opt);
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

    limitante = 0;
    for (int i = 0; i < qtdItens; i++) {
        scanf("%lf", &pesos[i]);
        if (pesos[i] > capacidade) {
            printf("Peso maior que a capacidade máxima.\n");
            free(pesos);
            free(pares);
            return 0;
        }
        limitante+=pesos[i];
    }
    limitante = limitante / capacidade;

    for (int i = 0; i < qtdPares; i++) {
        scanf("%d", &pares[i].antes);
        scanf("%d", &pares[i].depois);
    }

    int * ordemItens = (int *) calloc(qtdItens, sizeof(int));
    int i;
    int j = 0;
    for (i = 0; i < qtdPares; i++) {
        if (!buscaItem(ordemItens, j, pares[i].antes)) {
            ordemItens[j] = pares[i].antes;
            j++;
        }
    }
    for (int k = 1 ; k <= qtdItens; k++) {
        if (!buscaItem(ordemItens, qtdItens, k)) {
            ordemItens[j] = k;
            j++;
        }
    }
    
    if(verificaCiclos(qtdPares, pares)){

        opt = qtdItens+1;

        t_parciais * parciais = (t_parciais *) calloc(qtdItens, sizeof(t_parciais));
        resposta = (t_parciais *) calloc(qtdItens, sizeof(t_parciais));
        int l = 0;
        resolucao(qtdItens, capacidade, pesos, qtdPares, pares, parciais, l, ordemItens, 0, opt);
        imprime(qtdItens);

        free(parciais);
        free(resposta);
    }
    else {
        printf("Tem ciclo.\n");
    }

    free(pesos);
    free(pares);
    free(ordemItens);

    return 0;
}

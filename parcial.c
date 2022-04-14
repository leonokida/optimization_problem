//Laura e Leon

#include "parcial.h"
#include <stdio.h>

#include "lp_lib.h"

/*
Escreve o modelo no arquivo entrada.lp
*/
void escreveModelo(int qtdItens, double capacidade, double * pesos, int qtdPares, t_par_ordenado * pares, int l, t_parciais * parciais) {
    
    FILE* modelo = fopen("entrada.lp", "w");

    //Imprime função objetiva
    fprintf(modelo, "min: ");
    int j;
    for (j = 1; j < qtdItens; j++)
      fprintf(modelo, "y%d+", j);
    fprintf(modelo, "y%d;\n", j);

    //Imprime restrição de pesos
    int i;
    for (i=1; i<= qtdItens; i++) {
        for (j=1; j < qtdItens; j++)
            fprintf(modelo, "%lf*x%d%d+", pesos[j-1], i, j);
        fprintf(modelo, "%lf*x%d%d <= %lf*y%d;\n", pesos[j-1], i, j, capacidade, i);
    }

    //Imprime restrição de viagem única para cada item
    for (i=1; i<= qtdItens; i++) {
        for (j=1; j < qtdItens; j++)
            fprintf(modelo, "x%d%d+", j, i);
        fprintf(modelo, "x%d%d = 1;\n", j, i);
    }

    //Imprime restrição de pares ordenados
    int k;
    for (k=0; k < qtdPares; k++) {
        for (i=1; i < qtdItens; i++)
            fprintf(modelo, "%d*x%d%d+", i, i, pares[k].depois);
        fprintf(modelo, "%d*x%d%d > ", i, i, pares[k].depois);
        for (i=1; i < qtdItens; i++)
            fprintf(modelo, "%d*x%d%d+", i, i, pares[k].antes);
        fprintf(modelo, "%d*x%d%d;\n", i, i, pares[k].antes);
    }

    //Imprime restrições de valor das variáveis "binárias"
    for (i=1; i < qtdItens; i++) {
        fprintf(modelo, "y%d >= y%d;\n", i, i+1);
        fprintf(modelo, "y%d >= 0;\n", i);
        fprintf(modelo, "y%d <= 1;\n", i);
    }
    fprintf(modelo, "y%d >= 0;\n", i);
    fprintf(modelo, "y%d <= 1;\n", i);

    for (i=1; i <= qtdItens; i++)
        for (j=1; j <= qtdItens; j++) {
            fprintf(modelo, "x%d%d >= 0;\n", i, j);
            fprintf(modelo, "x%d%d <= 1;\n", i, j);
        }

    for (i=0; i < l; i++) {
        int viagem = parciais[i].viagem;
        fprintf(modelo, "%d*x%d%d = %d;\n", viagem, viagem, parciais[i].indice, viagem);
    }


    fclose(modelo);

}

double parcial(int qtdItens, double capacidade, double * pesos, int qtdPares, t_par_ordenado * pares, int l, t_parciais * parciais) {

    escreveModelo(qtdItens,capacidade,pesos, qtdPares, pares, l, parciais);

    lprec *lp;

    /* Lendo modelo do arquivo */
    lp = read_LP("entrada.lp", NORMAL, "test model");
    if(lp == NULL) {
      fprintf(stderr, "Unable to read model\n");
      return(1);
    }

    int solucao = solve(lp);
    double resultado;
    switch(solucao){
        case 0:
        case 1:
            resultado = get_objective(lp);
            delete_lp(lp);
            //print_solution(lp, 1);
            //printf("RESULTADO PARCIAL: %lf\n", resultado);
            return resultado;
            break;
        case 2:
            printf("Problema inviável.\n");
            return -1;
            break;
        case 3:
            printf("Problema ilimitado.\n");
            return -1;
            break;
        default:
            printf("Algum erro ocorreu.\n");
            return -1;
            break;
    }
}

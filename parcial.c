#include "parcial.h"
#include <stdio.h>

#include "lp_lib.h"

void escreveModelo(int qtdItens, double capacidade, double * pesos, int qtdPares, t_par_ordenado * pares) {
    
    FILE* modelo = fopen("entrada.lp", "w");

    fprintf(modelo, "min: ");
    int j;
    for (j = 1; j < qtdItens; j++)
      fprintf(modelo, "y%d+", j);
    fprintf(modelo, "y%d;\n", j);

    int i;
    for (i=1; i<= qtdItens; i++) {
        for (j=1; j < qtdItens; j++)
            fprintf(modelo, "%lf*x%d%d+", pesos[j-1], i, j);
        fprintf(modelo, "%lf*x%d%d <= %lf*y%d;\n", pesos[j-1], i, j, capacidade, i);
    }

    for (i=1; i<= qtdItens; i++) {
        for (j=1; j < qtdItens; j++)
            fprintf(modelo, "x%d%d+", j, i);
        fprintf(modelo, "x%d%d = 1;\n", j, i);
    }


    int k;
    for (k=0; k < qtdPares; k++) {
        for (i=1; i < qtdItens; i++)
            fprintf(modelo, "%d*x%d%d+", i, i, pares[k].depois);
        fprintf(modelo, "%d*x%d%d > ", i, i, pares[k].depois);
        for (i=1; i < qtdItens; i++)
            fprintf(modelo, "%d*x%d%d+", i, i, pares[k].antes);
        fprintf(modelo, "%d*x%d%d;\n", i, i, pares[k].antes);
    }

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


    fclose(modelo);

}

double parcial(int qtdItens, double capacidade, double * pesos, int qtdPares, t_par_ordenado * pares) {

    escreveModelo(qtdItens,capacidade,pesos, qtdPares, pares);

    lprec *lp;

    /* Read LP model */
    lp = read_LP("entrada.lp", NORMAL, "test model");
    if(lp == NULL) {
      fprintf(stderr, "Unable to read model\n");
      return(1);
    }

    solve(lp);

    /*set_outputfile(lp, "log.txt");
    print_objective(lp);*/

    return get_objective(lp);
}

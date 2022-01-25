#include <stdbool.h>
#include <stdio.h>
#include "auxproj1.h"


bool verifica(int comp, int larg) {
    //Função que verifica se os valores introduzidos pelo utilizador estão dentro do intervalo
    if ((comp >= 20 && comp <= 35) && (larg >= 20 && larg <= 35)) {
        return true;
    }
    else {
        printf("Insira valores dentro do intervalo (20-35)!\n");
        return false;
    }
}


void insere(int *pL, int *pC){
    //Função que pede as medidas da matriz ao utilizador
    printf("Insira um valor para largura (20-35): ");
    scanf("%d", pL);
    printf("Insira um valor para comprimento (20-35): ");
    scanf("%d", pC);
}


void matrix(int comp, int larg, int matriz[][larg]) {
    /*Função que, a partir de expressões lógicas, representa numa matriz uma figura
     * (triangulo isosceles) em 0s e 1s*/
    for (int i = 0; i < comp; ++i) {
        for (int j = 0; j < larg; ++j) {
            if (larg % 2 != 0) {
                if ((i == (larg / 2)) || ((larg / 2) - i == j) || ((larg / 2) - i == larg - j - 1)) {
                    matriz[i][j] = 1;
                } else
                    matriz[i][j] = 0;
            }
            else{
                if(((i == (larg / 2)-1) || ((larg / 2) - i - 1 == j) ||
                    ((larg / 2) - i - 1 == larg - j - 2)) && j< larg - 1){
                    matriz[i][j] = 1;
                } else
                    matriz[i][j] = 0;
            }
        }
    }
}


static void matrizAlterna(int comp, int larg, int matriz[][larg]){
/*função que recebe uma matriz e muda a ordem das linhas, de modo a que o ponto (0,0)
 * fique no canto inferior esquerdo (recorrendo ao uso de uma matriz auxiliar) */
    int aux[comp][larg];
    for(int x = comp-1; x>=0; --x){
        for(int y = 0; y<larg;++y){
            aux[comp-1-x][y] = matriz[x][y];
        }
    }
    for(int x = 0; x<comp; ++x) {
        for (int y = 0; y < larg; ++y) {
            matriz[x][y]=aux[x][y];
        }
    }
}


void desenho(int comp, int larg, int matriz[][larg]){
    /*Função que, a partir de uma matriz de 0s e 1s, gera a figura geométrica */
    matrizAlterna(comp, larg, matriz);
    for(int k = 0; k<comp; ++k){
        for(int l = 0; l<larg;++l){
            if (matriz[k][l] == 1){
                //posição ocupada pela figura geométrica mostra '#';
                printf("#");
            }
            else if((((matriz[k][l+1] == 1) && (l+1)<larg) || ((matriz[k][l-1]==1) && (l-1)>=0))){
                // posição com espaço mas adjacente(horizontalmente)a uma ocupada mostra 'l';
                printf("l");
            }
            else{
                // posição com espaço mostra '~';
                printf("~");
            }
        }
        printf("\n");
    }
}

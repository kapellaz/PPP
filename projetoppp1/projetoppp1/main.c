#include "auxproj1.h"

/*1º Trabalho de Principios de Programação Procedimental:
 *
 * O objetivo deste trabalho é mostrar um triangulo isosceles definido pelo seu
 * contorno com o vertice oposto à base para baixo, a partir de uma matriz, em que
 * o ponto de coordenadas (0, 0) fica no canto inferior esquerdo.
 * Para chegar a esse objetivo comecei por gerar uma matriz de 0s e 1s que formassem um triângulo
 * com o vértice oposto à base  para cima, para posteriormente, ao passar o ponto de
 * coordenadas (0,0) para o canto inferior esquerdo, esse vértice passasse a ficar para baixo.
 * Decidi que o meu triangulo iria ficar com a base do mesmo tamanho da largura da matriz, e que os
 * lados(de igual tamanho) convergissem num ponto que pertence à primeira linha da matriz(que apos a
 * passagem do ponto (0,0) para o canto inferior esquerdo ficará na ultima linha).
 * Contudo, quando a largura da matriz era par, nao era possivel que os lados convergissem num ponto,
 * então, para essa situação, fiz com que a base do triangulo tivesse -1 unidade de medida que a largura,
 * para ser agora impar.*/


int main(void) {
    int L, C;

    do {
        insere(&L, &C);
    }
    while (!verifica(L, C));

    int matriz[C][L];

    matrix(C, L, matriz);

    desenho(C, L, matriz);

    return 0;
}
#include "aux1.h"


//se o tamanho da palavra for maior que a relaçao de proporcionalidade entre a ocorrencia e o numero de
//colunas de cada linha (70), essa palavra vai aparecer encostada à esquerda;

//palavras com maiusculas/acentos sao alfabeticamente maiores que as palavras correspondentes
// sem maiusculas/acentos;

//palavras que contenham numeros são ignoradas;

//palavras com hifen, p.ex "guarda-chuva", ficam separadas em 2, "guarda" e "chuva"



#define MAX_TEXTO 10000
#define PAL 70


int main(void) {
    struct base lista;

    inicializar(&lista);

    char aux[MAX_TEXTO + 1];

    if (ler_texto(aux)) {
        cria(aux, &lista);
    }

    int maior = get_mais_repet(&lista);

    struct palavra pal;

    while (retirar(&lista, &pal)){
        printa(&pal, maior);
    }
    return 0;

}

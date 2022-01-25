#include "aux1.h"
#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#define MAX_TEXTO 10000
#define PAL 70

bool ler_texto(char *ptexto) {
    FILE *fich1;
    int i, c;
    fich1 = fopen("C:\\Users\\conta\\OneDrive\\Ambiente de Trabalho\\2trbppp\\texto.txt", "r");
    if (fich1 == NULL) {
        // Ficheiro texto.txt não existe
        return false;
    }
    i = 0;
    while (i < (MAX_TEXTO) && (c = fgetc(fich1)) != EOF) {
        ptexto[i] = (char) c;
        // detetar e eliminar o UTF BOM
        if (i == 2 && ptexto[0] == (char)0xEF && ptexto[1] == (char) 0xBB && ptexto[2] == (char) 0xBF)
            i = 0;
        else
            i++;
    }
    ptexto[i] = 0;
    i++;
    fclose(fich1);
    if (i <= MAX_TEXTO)
        return true;
    else
        // limite de bytes ultrapassado
        return false;
}



int get_mais_repet(struct base *pf){    //obtem o maior numero de ocorrencias de uma palavra na lista
    int maior = 0;
    for (int j = pf->entrada_lista; j != pf->no[pf->entrada_lista].anterior; j = pf->no[j].seguinte){
        if (pf->no[j].p.ocorrencia > maior) maior = pf->no[j].p.ocorrencia;
    }
    return maior;
}


size_t strlen_u8(const char *s) {
    size_t tam = 0, i = 0;
    while (s[i] != 0) {
        if ((s[i] & 0xC0) != 0x80)
            tam++;
        i++;
    }
    return tam;
}


void printa(struct palavra *pal, int m){

    int dist = ((PAL * pal->ocorrencia) / m) - (int) strlen_u8(pal->pal);     //distancia a que deve estar do lado esquerdo

    for (int p = 0; p < dist && dist>0; ++p) {
        printf(" ");
    }
    printf("%s\n", pal->pal);
}
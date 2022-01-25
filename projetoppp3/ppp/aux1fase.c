#include "aux1fase.h"
#include <string.h>
#include <ctype.h>
#include "lib-utf8.h"
#define MAX 1000


static int pos(char *linha, char *pal, int posicao){
    //procura a posicao da palavra na linha em que se encontra no texto
    int aux = 0;
    for (int i = posicao; i < strlen(linha); i++) {
        if(linha[i] == pal[0]){
            aux = i;
            for (int j = 0; j < strlen(pal); j++) {
                if(linha[aux] == pal[j])
                    aux++;
            }
        }
        if ((aux - i) == (strlen(pal))) {
            if(!isalnum(linha[aux]))
                return i;
        }
    }
    return -1;
}


void new_file(FILE *in, FILE *out){
    //cria um ficheiro com os pares palavra-posicoes
    char line[MAX] = "";

    int tam = 0;

    while(fgets_u8(line, MAX, in) != NULL){
        char aux[MAX] = "";
        strcpy(aux, line);
        int p=0;
        char * s = "  .,;:!(-_<>)#/[]{}\"?\r\n\t";
        char *token = strtok(line, s);
        while(token!=NULL){
            if(strlen_u8(token) > 2) {
                int c = pos(aux, token, p);
                fprintf(out, "%s %d\n", token, c + tam);
                p=c+1;
            }
            token = strtok(NULL, s);
        }
        tam = tam + (int) strlen(aux);
    }
}
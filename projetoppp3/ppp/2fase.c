#include <locale.h>
#include <stdio.h>
#include <string.h>
#include "arvore.h"
#include "aux2fase.h"

#define MAX 1000


int main(int argc, char *argv[]){
    char file[MAX] = "";

    if(argc == 1){
        printf("Indique o nome do ficheiro: ");
        scanf("%s", file);
    }
    else if(argc > 2) fprintf(stderr, "Foram inseridos parametros a mais na linha de comandos");

    else {
        strcpy(file, argv[1]);

        setlocale(LC_ALL, "pt_PT.utf8");

        struct arvore_binaria arvore;

        inicializar_arvore(&arvore);

        FILE *in = fopen(file, "r");

        if (in == NULL) {
            fprintf(stderr, "ficheiro nao existe\n");
            return -1;
        }

        monta_arvore(in, &arvore);

        char aux[MAX] = "";
        retira_pre(file, aux);
        FILE *origem = fopen(aux, "r");

        struct lista posicoes;
        inicializar_lista(&posicoes);
        get_pos(&arvore, &posicoes);
        askfornumber(&arvore, &posicoes, origem);
        fclose(in);
        fclose(origem);
    }
    return 0;
}


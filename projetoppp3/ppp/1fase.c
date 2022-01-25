#include <stdio.h>
#include <locale.h>
#include <string.h>
#include "aux1fase.h"
#define MAX 1000




int main(int argc, char*argv[]) {
    setlocale(LC_ALL, "pt_PT.utf8");

    if(argc == 1) fprintf(stderr, "Nome do ficheiro não indicado");

    else if(argc > 2) fprintf(stderr, "Foram inseridos parametros a mais na linha de comandos");

    else {
        FILE *in = fopen(argv[1], "r");

        if (in == NULL) {
            fprintf(stderr, "ficheiro nao existe\n");
            return -1;
        }

        char pre[MAX] = "idx_";

        FILE *out = fopen(strcat(pre, argv[1]), "w");

        new_file(in, out);

        fclose(in);
        fclose(out);
    }
    return 0;
}

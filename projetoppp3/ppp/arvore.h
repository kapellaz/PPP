#ifndef MAIN_C_ARVORE_H
#define MAIN_C_ARVORE_H
#define MAX 1000

#include <stdbool.h>
#include "lib-utf8.h"
#include "lista.h"

struct palavra {
    char word[MAX];
    struct lista indice;
};

struct no {
    struct palavra gente;
    struct no *left;
    struct no *right;
};

struct arvore_binaria {
    struct no * raiz;
};

struct no *find(struct no *pr, char *pn);

void inicializar_arvore(struct arvore_binaria * pa);

bool colocar(struct arvore_binaria * pa, struct  palavra pal);

bool monta_arvore(FILE*in, struct arvore_binaria *arvore);

bool seguinte(struct arvore_binaria * pa, struct palavra * ppessoa);


#endif //MAIN_C_ARVORE_H

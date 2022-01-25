#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include <stdbool.h>


void inicializar_arvore(struct arvore_binaria * pa) {
    pa->raiz = NULL;
}


bool monta_arvore(FILE*in, struct arvore_binaria *arvore){
    //cria uma arvore binaria a partir do ficheiro que contem os pares palavra-posicao
    char line[MAX] = "";

    while (fgets_u8(line, MAX, in) != NULL) {
        char *s = " ";
        struct palavra pal;
        inicializar_lista(&pal.indice);
        char *token = strtok(line, s);
        strncpy(pal.word, token, MAX);
        token = strtok(NULL, s);
        while (token != NULL){
            int p = (int) strtol(token, &token, 10);
            colocar_lista(&pal.indice, p);
            token = strtok(NULL, s);
        }

        if (!colocar(arvore, pal)) {
            fprintf(stderr, "Não há espaco para inserir\n");
            break;
        }
    }
    return true;
}


static struct no *addtree(struct no *, struct no *);


struct no *find(struct no *pr, char *pn) {
    int cond;
    if (pr == NULL)
        return NULL;
    char nome1[MAX + 1] = "",nome2[MAX + 1] = "";
    strtobase_u8(nome1,pr->gente.word);
    strtobase_u8(nome2,pn);
    if ((cond = strcmp(nome1, nome2)) == 0)
        return pr;
    else if (cond > 0)
        return find(pr->left, pn);
    return find(pr->right, pn);
}

bool colocar(struct arvore_binaria * pa, struct palavra pal) {
    struct no *p = NULL;
    struct no *f = NULL;
    p = (struct no *) malloc(sizeof(struct no)); // make a new node
    if (p == NULL)
        return false;

    f = find(pa->raiz, pal.word);

    if(f!=NULL){
        colocar_lista(&f->gente.indice, pal.indice.raiz->pos);
        return true;
    }

    p->gente = pal;
    p->left = p->right = NULL;
    pa->raiz = addtree(pa->raiz, p);
    return true;
}


static struct no *addtree(struct no *pr, struct no *p) {
    int cond;
    char nome1[MAX + 1] = "",nome2[MAX + 1] = "";
    if (pr == NULL) {
        pr = p;
    } else {
        strtobase_u8(nome1,p->gente.word);
        strtobase_u8(nome2,pr->gente.word);
        if ((cond = strcmp(nome1,nome2)) > 0) {
            pr->right = addtree(pr->right, p);
        } else if (cond < 0)
            pr->left = addtree(pr->left, p);
    }
    return pr;
}


static struct no *find_next(struct no *pr, const char *anterior, struct no *candidato) {
    if (pr == NULL) return candidato;
    char nome1[MAX + 1] = "",nome2[MAX + 1] = "";
    strtobase_u8(nome1,anterior);
    strtobase_u8(nome2,pr->gente.word);
    if (strcmp(nome1,nome2) >= 0)
        return find_next(pr->right, anterior, candidato);
    else
        return find_next(pr->left, anterior, pr);
}

bool seguinte(struct arvore_binaria * pa, struct palavra * ppessoa) {
//struct pessoa seguinte(int *pvazio, const char nome[MAX + 1]) {
    struct no *p = NULL;

    p = find_next(pa->raiz, ppessoa->word, NULL);
    if (p == NULL) {
        return false;
    }
    *ppessoa = p->gente;
    return true;
}
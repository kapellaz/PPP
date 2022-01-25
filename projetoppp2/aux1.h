#ifndef INC_2TRBPPP_AUX1_H
#define INC_2TRBPPP_AUX1_H
#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#define PAL 70
#define MAX_TEXTO 10000

struct palavra{
    char pal[PAL];
    int ocorrencia;
};

struct no_lista {
    struct palavra p;
    bool ocupado;
    int seguinte;
    int anterior;
};

struct base {
    struct no_lista no[MAX_TEXTO];
    int tam;
    int entrada_lista;
    int saida_lista;
};

bool ler_texto(char *ptexto);
void inicializar(struct base *pf);
bool cria(char *v, struct base *pf);
size_t strlen_u8(const char *s);
bool retirar(struct base *pf, struct palavra *pal);
int get_mais_repet(struct base *pf);
void printa(struct palavra *pal, int m);
#endif

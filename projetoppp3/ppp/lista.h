#include <stdbool.h>


struct no_lista {
    int pos;
    struct no_lista * pseg;
};

struct lista {
    struct no_lista * raiz;
};

bool colocar_lista(struct lista * pf, int p);

void inicializar_lista(struct lista *pf);


#include <stdlib.h>
#include "lista.h"

void inicializar_lista(struct lista *pf) {
    pf->raiz = NULL;
}

bool colocar_lista(struct lista *pf, int p) {
    struct no_lista * aux, * prox, * anterior;

    //Obter espaço para um novo nó
    aux = (struct no_lista *) malloc(sizeof(struct no_lista));
    if (aux == NULL)
        //não há espaço
        return false;

    //construir novo nó da fila
    aux->pos = p;
    aux->pseg = NULL;

    //Procurar a posição onde a mensagem deve ficar
    if (pf->raiz == NULL) {
        // fila vazia, é a primeira mensagem
        pf->raiz = aux;
    } else {
        // fila contém mensagens
        if (pf->raiz->pos >= p) {
            // inserir à entrada da lista
            aux->pseg = pf->raiz;
            pf->raiz = aux;
        } else {
            // procurar posição de inserção
            anterior = pf->raiz;
            prox = pf->raiz->pseg;
            while (prox != NULL && prox->pos < p) {
                anterior = prox;
                prox = prox->pseg;
            }
            if (prox == NULL) {
                // inserir à saída da lista
                anterior->pseg = aux;
            } else {
                // inserir a meio da lista
                anterior->pseg = aux;
                aux->pseg = prox;
            }
        }
    }
    return true;
}


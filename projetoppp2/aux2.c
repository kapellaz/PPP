#include "aux1.h"
#include <string.h>
#include <locale.h>
#include <ctype.h>

void inicializar(struct base *pf) {  //inicializa a lista
    pf->tam = MAX_TEXTO;
    pf->entrada_lista = MAX_TEXTO-1;
    pf->saida_lista = MAX_TEXTO-1;
    for (int i = 0; i < MAX_TEXTO; i++) {
        pf->no[i].ocupado = false;
    }
}


static int encontra_vazio(struct base *pf){  //encontra a primeira posição vazia da lista
    for (int i = 0; i < pf->tam; ++i) {
        if(pf->no[i].ocupado==false)
            return i;
    }
    return -1;
}


static bool verifica_existencia(struct base *pf, char *pal){  //verifica se a palavra a inserir na lista já existe
                                                              // , se existir aumenta as ocorrencias
    for (int k = 0; k < pf->tam; ++k){
        if(strcmp(pf->no[k].p.pal, pal) == 0) {
            pf->no[k].p.ocorrencia++;
            return true;
        }
    }
    return false;
}


static int compara(char *pal1, char *pal2){
    //compara as duas palavras em primeiro lugar de acordo com o comprimento da palavra e se este for igual compara
    //por ordem alfabetica
    setlocale(LC_ALL, "pt_PT.utf8");
    int c = (int) (strlen_u8(pal2) - strlen_u8(pal1));
    if(c<0) return -1;
    else if (c>0) return 1;
    else{
        if (strcoll(pal1, pal2) > 0) return 1;
        else if (strcoll(pal1, pal2) < 0) return -1;
        else return 0;
    }
}


static bool verifica_numero(char * pal){
    // verifica se a palavra a colocar contêm um número;
    for (int i = 0; i < strlen(pal); ++i) {
        if (isdigit(pal[i]))
            return true;
    }
    return false;
}


static bool coloca_ordenado(struct base *pf, char *pal){  //coloca a palavra na posição correta da lista
    setlocale(LC_ALL, "pt_PT.utf8");
    if(verifica_numero(pal)) return true;

    int n, anterior, prox;

    if(verifica_existencia(pf, pal)) return true;

    n = encontra_vazio(pf);

    if (n<0) return false; //não há espaços vazios na lista

    for (int i = 0; i < strlen(pal); ++i) {
        pf->no[n].p.pal[i] = pal[i];
    }

    pf->no[n].p.ocorrencia = 1;

    if(!(pf->no[pf->entrada_lista].ocupado)){ // insere na primeira posição da lista
        pf->entrada_lista = n;
        pf->saida_lista = n;
        pf->no[n].seguinte = -1;
        pf->no[n].anterior = -1;
    }else {
        // fila contém mensagens
        if (compara(pf->no[pf->entrada_lista].p.pal, pal) >= 0) {
            // inserir à entrada da lista
            pf->no[n].seguinte = pf->entrada_lista;
            pf->no[n].anterior = -1;
            pf->no[pf->entrada_lista].anterior = n;
            pf->entrada_lista = n;
        } else {
            // procurar posição de inserção
            anterior = pf->entrada_lista;
            prox = pf->no[pf->entrada_lista].seguinte;
            while (prox >= 0 && compara(pf->no[prox].p.pal, pal) < 0 ) {
                anterior = prox;
                prox = pf->no[prox].seguinte;
            }
            if (prox < 0) {
                // inserir na saida da lista
                pf->no[anterior].seguinte = n;
                pf->no[n].seguinte = -1;
                pf->no[n].anterior = anterior;
                pf->saida_lista = n;
            } else {
                // inserir a meio da lista
                pf->no[anterior].seguinte = n;
                pf->no[n].anterior = anterior;
                pf->no[n].seguinte = prox;
                pf->no[prox].anterior = n;
            }
        }
    }
    pf->no[n].ocupado = true;
    return true;
}


bool cria(char *v, struct base *pf) {
    //separa o texto lido em palavras e coloca-as na lista
    char *token = strtok(v, "  .,;:!(-_<>)#/[]{}\"?\r\n\t");
    while (token != NULL) {
        coloca_ordenado(pf, token);
        token = strtok(NULL, " .,;:!(-_<>)#/[]{}\"?\r\n\t");
    }
    return true;
}


bool retirar(struct base *pf, struct palavra *pal) {
    // retira as palavras da lista
    if (! pf->no[pf->saida_lista].ocupado) {
        // lista vazia
        printf("Lista Vazia\n");
        return false;
    }
    * pal = pf->no[pf->saida_lista].p;
    pf->no[pf->saida_lista].ocupado = false;
    if (pf->no[pf->saida_lista].anterior != -1) {
        // havia mais do que uma mensagem na lista
        pf->saida_lista = pf->no[pf->saida_lista].anterior;
        pf->no[pf->saida_lista].seguinte = -1;
    }
    return true;
}
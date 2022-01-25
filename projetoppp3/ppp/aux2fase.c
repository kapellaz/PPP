#include "aux2fase.h"
#include "string.h"
#include <stdlib.h>


void retira_pre(char *pal, char *out){
    //cria uma nova palavra retirando à palavra original os primeiros 4 caracteres
    for (int i = 4; i < strlen(pal); ++i) {
        strcpy(&out[i-4], &pal[i]);
    }
}


static bool encontra_letra(struct arvore_binaria *pa, char *str){
    //procura na arvore as palavras comecadas por uma letra/gama de letras
    char auxi[MAX] = "";
    strtobase_u8(auxi, str);
    int i_first = (int) auxi[0];
    int i_last;

    if (strlen(str) == 1) i_last = i_first;
    else i_last = (int) auxi[1];

    if(strlen(str)<1 || strlen(str)>2 || (i_first > i_last)){
        printf("Letra/Gama de letras inválida\n");
        return false;
    } else if(i_first < 97 || i_last > 122 || i_last < 97 || i_first > 122){
        printf("Letra/Gama de letras inválida\n");
        return false;
    }
    else{
        while (i_last-i_first >=0){
            puts(" ");
            struct palavra pal;
            pal.word[0] = 0;
            struct no_lista *prox = NULL;
            int control = 0;
            while (seguinte(pa,&pal)){
                char aux[MAX] = "";
                strtobase_u8(aux, pal.word);
                if((int) pal.word[0] == i_first){
                    printf("%s", pal.word);
                    for (prox = pal.indice.raiz; prox != NULL; prox = prox->pseg) {
                        printf(" ");
                        printf("%d", prox->pos);
                    }
                    printf("\n");
                    control++;
                }
            }
            if(control==0) printf("Não existe nenhuma palavra no ficheiro começada pela letra %c\n",  (char) i_first);
            i_first++;
            free(prox);
        }
        puts(" ");
        return true;
    }
}


void get_pos(struct arvore_binaria *pa, struct lista *posi) {
    //cria uma lista apenas com todas as posicoes de todas as palavras, ordenadas por ordem crescente
    struct palavra pal;
    pal.word[0] = 0;
    struct no_lista *prox = NULL;
    while (seguinte(pa, &pal)) {
        for (prox = pal.indice.raiz; prox != NULL; prox = prox->pseg) {
            colocar_lista(posi, prox->pos);
        }
    }
    free(prox);
}


static int findant(int pos, struct lista *posicoes){
    //procura o indice da palavra que se situa 10 palavras atras da palavra inserida pelo utilizador
    struct no_lista * prox = NULL, *prox2 = NULL;
    for (prox = posicoes->raiz; prox != NULL; prox = prox->pseg) {
        int k = 0;
        for (prox2 = prox; prox2 != NULL; prox2 = prox2->pseg) {
            if ((prox2->pos == pos) && (k == 10))
                return prox->pos;
            ++k;
        }
    }
    free(prox);
    free(prox2);
    return 0;
}


static int findlen(int pos, struct arvore_binaria *pa) {
    //devolve o comprimento de uma palavra da arvore
    struct palavra pal;
    pal.word[0] = 0;
    struct no_lista * prox = NULL;
    while (seguinte(pa, &pal)) {
        for (prox = pal.indice.raiz; prox != NULL; prox = prox->pseg) {
            if (prox->pos == pos) {
                return (int) strlen(pal.word);
            }
        }
    }
    free(prox);
    return -1;
}


static int findlast(int pos, struct lista *posicoes, struct arvore_binaria *pa){
    //devolve a posicao do ultimo caracter da palavra que esta 5 palavras a frente da palavra inserida pelo utilizador
    struct no_lista * prox = NULL, *prox2 = NULL;
    for (prox = posicoes->raiz; prox != NULL; prox = prox->pseg) {
        if(prox->pos == pos){
            int k = 0;
            int aux = 0;
            for (prox2 = prox; prox2 != NULL && k<=5; prox2=prox2->pseg) {
                aux = prox2->pos;
                ++k;
            }
            return aux + findlen(aux, pa);
        }
    }
    free(prox2);
    free(prox);
    return -1;
}


static void contexto(struct lista *posicoes, struct arvore_binaria *pa, char *pal, FILE *in){
    //funcao que mostra o contexto de uma palavra
    char word[MAX]; strcpy(word, pal);
    struct no *f;
    f = find(pa->raiz, word);
    if (f == NULL) {
        printf("A palavra não existe no ficheiro!\n");
    }else {
        struct no_lista *prox = NULL;
        for (prox = f->gente.indice.raiz; prox != NULL; prox = prox->pseg){
            int pos = prox->pos;
            int ant = findant(pos, posicoes);
            int last = findlast(pos, posicoes, pa);
            int comp = last - ant;
            printf("\n%d\t", pos);
            fseek(in, ant, SEEK_SET);
            char cont[MAX] = "";
            fread(cont, sizeof(char), comp, in);
            printf("%s\n \n", cont);
        }
        free(prox);
    }
}


void askfornumber(struct arvore_binaria *pa, struct lista *posicoes, FILE *ori){
    //pede um numero ao utilizador, e conforme a opçao correspondente, executa uma funcao
    char num[MAX] = "";
    printf("1 - Procurar as palavras começadas por uma letrs/gama de letras;\n");
    printf("2 - Mostrar o contexto de uma palavra;\n");
    printf("3 - Sair\n");
    while(true) {
        printf("Insira o número correto, conforme a operação desejada:\n");
        scanf("%1s", num);
        char resto[MAX] = "";
        scanf("%[^\n]", resto);
        char *ptr;
        int p = (int) strtol(&num[0], &ptr, 10);

        if(p>3 || p<1) {
            printf("Número inválido\n");
            continue;
        }
        else{
            if(p==3){
                break;
            }
            else {
                char aux[MAX] = "";
                if (p == 1) {
                    printf("Insira a letra ou gama de letras (na forma letra espaço letra p.ex(al)): ");
                    scanf("%s", aux);
                    if (!encontra_letra(pa, aux))
                        continue;
                }
                if (p == 2) {
                    printf("Insira a palavra: ");
                    scanf("%s", aux);
                    contexto(posicoes, pa, aux, ori);
                }
            }
        }
    }
}


/*static int encontra_str(struct arvore_binaria *pa, char *sub){
    struct palavra pal;
    pal.word[0] = 0;
    struct no_lista *prox;
    int control = 0;
    while (seguinte(pa, &pal)) {
        unsigned long comp = strlen(sub);
        int aux=0;
        for (int i = 0; i < comp; ++i) {
            if(pal.word[i]==sub[i])
                aux++;
        }
        if(aux == comp) {
            printf("%s", pal.word);
            for (prox = pal.indice.raiz; prox != NULL; prox = prox->pseg) {
                printf(" ");
                printf("%d", prox->pos);
            }
            puts("\n");
            control++;
        }
    }
    if(control == 0) printf("A palavra que escolheu não pertence a nenhuma palavra do ficheiro!\n");
    return control;
}*/

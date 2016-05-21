/*
 * pavilhao.c
 *
 */
// fazer todo o TAD usando a estrutura aqui dada

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "fila.h"
#include "dicionario.h"
#include "cliente.h"
#include "pavilhao.h"

#define DOBRO 2
#define MAXPAV 2000
struct _pavilhao{
   	dicionario pessoas; //colecao de clientes no sistema
    cliente * trampolins;
    fila filaTrampolins;//fila para os trampolins
    float caixa; //valor em caixa
    int nTrampolins;
    int nTrampolinsLivres;
    int sCafe;
    int sSumo;
    int sBolo;
    float vCafe;
    float vSumo;
    float vBolo;
};

/***********************************************
 criapavilhao - Criacao da instancia da estrutura associada a uma pavilhao.
 Parametros: 	nPessoas - numero previsto de pessoas;
 precoNormal - preco da lavagem normal (a especial é o dobro)
 Retorno: 	apontador para a instancia criada
 Pre-condicoes: nPessoas > 0 && precoNormal > 0
 ***********************************************/
pavilhao criaPavilhao(int nTrampolins, int sCafe, float vCafe ,int sSumo,float vSumo,int sBolo , float vBolo ){
    pavilhao p = (pavilhao) malloc(sizeof(struct _pavilhao)); // alloca memoria para a estrutura da pavilhao
    if (p==NULL)                                           // verifica se esta memoria foi allocada
        return NULL;
    p->pessoas = criaDicionario(MAXPAV,0);                       // cria a fila de pessoas
    if (p->pessoas==NULL){                                 // se não foi possivel criar a fila, vai libertar a memoria da pavilhao
        free(p);
        return NULL;
    }
    p->filaTrampolins = criaFila(nTrampolins);
    if (p->filaTrampolins == NULL) {
        destroiDicionario(p->pessoas);
        free(p);
        return NULL;
    }
    p->trampolins = malloc(sizeof(cliente)*nTrampolins);
    if (p->trampolins == NULL) {
        destroiDicionario(p->pessoas);
        destroiFila(p->filaTrampolins);
        free(p);
        return NULL;
    }
    p->caixa =  0.0;
    p->sCafe = sCafe;
    p->sSumo = sSumo;
    p->sBolo = sBolo;
    p->vCafe = vCafe;
    p->vSumo = vSumo;
    p->vBolo = vBolo;
    p->nTrampolins = nTrampolins;
    p->nTrampolinsLivres = nTrampolins ;
    return p;
}

/***********************************************
 destroipavilhao - Liberta a memoria ocupada pela estrutura associada a pavilhao, assim como as pessoas na pavilhao, caso existam.
 Parametros: 	c - pavilhao a destruir
 Pre-condicoes: c != NULL
 ***********************************************/
void destroiPavilhao(pavilhao c){
    destroiDicEElems(c->pessoas, destroiGenCliente); // destroi a fila e os elementos (se estes existirem)
    destroiFilaEElems(c->filaTrampolins, destroiGenCliente);
    free(c->trampolins);
    free(c);
}

/***********************************************
 entrapavilhao - adiciona o veiculo com o contribuinte dado e a lavagem escolhida.
 Parametros: 	c - pavilhao;	numContribuinte - numero de contribuinte;
 mat - matricula;	lav - tipo de lavagem
 Pre-condicoes: c != NULL && mat != NULL && numC > 0 && ((lav == 'N') || (lav == 'E'))
 ***********************************************/
void entraPavilhao(pavilhao c, int numContribuinte, int numCidadao, char * nome){
    adicionaElemDicionario(c->pessoas, &numCidadao, criaCliente(numContribuinte, numCidadao, nome));
}

/***********************************************
 pessoaspavilhao - retorna o numero de pessoas na pavilhao.
 Parametros: 	c - pavilhao
 Pre-condicoes: c != NULL
 ***********************************************/
int pessoasPavilhao(pavilhao c){
    return tamanhoDicionario(c->pessoas);
}
/***********************************************
 caixapavilhao - retorna o valor em caixa.
 Parametros: 	c - pavilhao
 Pre-condicoes: c != NULL
 ***********************************************/
float caixaPavilhao(pavilhao c){
    return c->caixa;
}

cliente saiPavilhao(pavilhao p, int numCidadao, int * perm){
    cliente c = NULL;
    if (existeElemDicionario(p->pessoas, &numCidadao)) {
        c = elementoDicionario(p->pessoas, &numCidadao);
        if (isTrampolins(c)) {
            * perm = 0;
        }else{
            * perm = 1;
            removeElemDicionario(p->pessoas, &numCidadao);
        }
        return c;
    }else{
        return NULL;
    }
}
void entraFilaTrampolins(pavilhao p , int numCidadao){
    cliente c = elementoDicionario(p->pessoas, &numCidadao);
    adicionaElemFila(p->filaTrampolins,c);
    setTrampolins(c);
}
void adicionaVecTrampolin(pavilhao p , cliente c){
    int i;
    for (i = 0; i < p->nTrampolins; i++) {
        if (p->trampolins[i] == NULL) {
            p->trampolins[i] = c;
            break;
        }
    }
}

cliente removeVecTrampolin(pavilhao p, int numCidadao){
    cliente c = NULL;
    int i;
    for (i = 0; i < p->nTrampolins; i++) {
        if (cidadaoCliente(p->trampolins[i]) == numCidadao) {
            c=p->trampolins[i];
            p->trampolins[i] = NULL;
            break;
        }
    }

    return c;
}

int entraTrampolins(pavilhao p, int mEntrada){
    int numPessoas;
    cliente c = NULL;
    while(!(p->nTrampolinsLivres == 0 || vaziaFila(p->filaTrampolins))){
        c = removeElemFila(p->filaTrampolins);
        entraTempo(c, mEntrada);
        adicionaVecTrampolin(p,c);
        numPessoas++;
        p->nTrampolinsLivres --;
    }
    return numPessoas;
}
int stockCafe(pavilhao c){
    return c->sCafe;
}
int stockSumo(pavilhao c){
    return c->sSumo;
}
int stockBolo(pavilhao c){
    return c->sBolo;
}
void saiTrampolins(pavilhao p, int nTempo , int numCidadao){
    cliente c = removeVecTrampolin(p,numCidadao);
    int aux  = cidadaoCliente(c);
    adicionaTempo(c,nTempo - mEntrada(c));
    adicionaElemDicionario(p->pessoas,&aux, c);
    removeTrampolins(c);
    p->nTrampolinsLivres++;

}

int existePavilhao(pavilhao p , int numCidadao){
    return existeElemDicionario(p->pessoas, &numCidadao);
}

int pessoaTrampolin(pavilhao p, char * nome, int nTrampolim){
    if (p->trampolins[nTrampolim-1] == NULL) {
        return 1;
    }else if(nTrampolim >= p->nTrampolins){
        return 0;
    }else{
       nome = nomeCliente(p->trampolins[nTrampolim-1]);
       return 2;
    }
}
float sumo(pavilhao p ,int quantidade){
    float r;
    if (quantidade < p->sSumo ) {
        r = quantidade * p->vSumo;
        p->sSumo -= quantidade;
        return r;
    }else{
    return -1;
    }
}
float cafe(pavilhao p, int quantidade){
    float r;
    if (quantidade < p->sCafe ) {
        r = quantidade * p->vCafe;
        p->sCafe -= quantidade;
        return r;
    }else{
        return -2;
    }
}
float bolo(pavilhao p, int quantidade){
    float r;
    if (quantidade < p->sBolo ) {
        r = quantidade * p->vBolo;
        p->sBolo -= quantidade;
        return r;
    }else{
        return -3;
    }
}
int consumo(pavilhao p ,char tipo ,int quantidade, int numCidadao){
    tipo = toupper(tipo);
    cliente c ;
    float conta = 0.0;
    switch (tipo){
        case 'C':conta = cafe(p, quantidade);break;
        case 'S':conta = sumo(p, quantidade);break;
        case 'B':conta = bolo(p, quantidade);break;
    }
    if (conta < 0) {
        return -1;
    }else{
        c = elementoDicionario(p->pessoas, &numCidadao);
        adicionaConta(c, conta);
        return 1;
    }
}
void fechaPavilhao(pavilhao p){
    iterador it = iteradorChaveDicionario(p->pessoas);
    cliente c;
    int numCidadao;
    int perm;
    while (temSeguinteIterador(it)) {
        numCidadao = (int)seguinteIterador(it);
        c = saiPavilhao(p, numCidadao, &perm);
        if (perm == 0 ) {
            saiTrampolins(p, 24*60, numCidadao);
            c = saiPavilhao(p, numCidadao, &perm);
        }
    }
    destroiIterador(it);
}
int trampolinsLivres(pavilhao c){
    return c->nTrampolinsLivres;
}
cliente clienteEmPavilhao(pavilhao p, int numCidadao){
    return elementoDicionario(p->pessoas, &numCidadao);
}
int vaziaFilaTrampolins(pavilhao c){
    return vaziaFila(c->filaTrampolins);
}
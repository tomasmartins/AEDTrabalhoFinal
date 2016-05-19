/*
 * pavilhao.c
 *
 */
// fazer todo o TAD usando a estrutura aqui dada

#include <stdio.h>
#include <stdlib.h>

#include "fila.h"
#include "dicionario.h"
#include "cliente.h"
#include "pavilhao.h"

#define DOBRO 2
#define MAXPAV 2000
struct _pavilhao{
   	dicionario pessoas; //colecao de clientes no sistema
    dicionario trampolins;
    fila filaTrampolins;//fila para os trampolins
    float caixa; //valor em caixa
    int nTrampolins;
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
        free(p);
        return NULL;
    }
    p->trampolins = criaDicionario(nTrampolins, 0);
    if (p->trampolins == NULL) {
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
    return p;
}

/***********************************************
 destroipavilhao - Liberta a memoria ocupada pela estrutura associada a pavilhao, assim como as pessoas na pavilhao, caso existam.
 Parametros: 	c - pavilhao a destruir
 Pre-condicoes: c != NULL
 ***********************************************/
void destroiPavilhao(pavilhao c){
    destroiDicEElems(c->pessoas, destroiGenCliente); // destroi a fila e os elementos (se estes existirem)
    destroiDicEElems(c->trampolins, destroiGenCliente);
    destroiFilaEElems(c->filaTrampolins, destroiGenCliente);
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

cliente saiPavilhao(pavilhao p, int numCidadao){
    cliente c;
    c = removeElemDicionario(p->pessoas, &numCidadao);
    return c;
}
void entraFilaTrampolins(pavilhao p , int numCidadao){
    adicionaElemFila(p->filaTrampolins,elementoDicionario(p->pessoas, &numCidadao));
}

int entraTrampolins(pavilhao p){
    int numPessoas;
    cliente c ;
    while(p->nTrampolins == 0 || vaziaFila(p->filaTrampolins)){
        c = removeElemFila(p->filaTrampolins);
        adicionaElemDicionario(p->pessoas, cidadaoCliente(c),c);
        numPessoas++;
        p->nTrampolins--;
    }
    return numPessoas;
}

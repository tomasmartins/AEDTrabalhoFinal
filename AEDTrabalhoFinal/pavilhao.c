/*
 * Módulo: pavilhao.c
 * Data: 03/06/2016
 * Descricao: TAD do pavilhao usado
 * Autores: Miguel Real e Tomas Martins
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "fila.h"
#include "dicionario.h"
#include "cliente.h"
#include "pavilhao.h"

#define DOBRO 2
#define INIPAV 1500
#define MINTRAMP 30
#define PRECOTRAMP 5

struct _pavilhao{
   	dicionario pessoas; //colecao de clientes no sistema
    cliente * trampolins;
    fila filaTrampolins;//fila para os trampolins
    float caixa; //valor em caixa
    int nTrampolins;
    int nTrampolinsLivres;
    struct {
        int stock;
        float preco;
    } produto[3];
};

/***********************************************
 criapavilhao - Criacao da instancia da estrutura associada a um pavilhao.
 Parametros: 	nTrampolins - numero de Trampolins;
 sCafe - stock de cafe;
 vCafe - preco do cafe;
 sSumo - stock de sumo;
 vSumo - preco do sumo;
 sBolo - stock de bolo;
 vBolo - preco do bolo;
 Retorno: 	apontador para a instancia criada
 Pre-condicoes: nPessoas > 0 && precoNormal > 0 && sCafe > 0 && vCafe > 0
 && sSumo > 0 && vSumo > 0 && sBolo > 0 && vBolo > 0
 ***********************************************/
pavilhao criaPavilhao(int nTrampolins, int sCafe, float vCafe ,int sSumo,float vSumo,int sBolo , float vBolo ){
    int i;
	pavilhao p = (pavilhao) malloc(sizeof(struct _pavilhao));
    if (p==NULL)
        return NULL;
    p->pessoas = criaDicionario(INIPAV,0);                      
    if (p->pessoas==NULL){                                
        free(p);
        return NULL;
    }
    p->filaTrampolins = criaFila(nTrampolins);
    if (p->filaTrampolins == NULL) {
        destroiDicionario(p->pessoas);
        free(p);
        return NULL;
    }
    p->trampolins = (cliente *) malloc(sizeof(cliente)*nTrampolins);
    
    if (p->trampolins == NULL) {
        destroiDicionario(p->pessoas);
        destroiFila(p->filaTrampolins);
        free(p);
        return NULL;
    }
    p->caixa =  0.0;
    p->produto[0].preco = vCafe;
    p->produto[0].stock = sCafe;
    p->produto[1].preco = vSumo;
    p->produto[1].stock = sSumo;
    p->produto[2].preco = vBolo;
    p->produto[2].stock = sBolo;
    p->nTrampolins = nTrampolins;
    p->nTrampolinsLivres = nTrampolins ;
    for (i = 0; i < nTrampolins; i++) {
            p->trampolins[i] = NULL;
        }
    return p;
}

/***********************************************
 destroiPavilhao - Liberta a memoria ocupada pela estrutura associada ao pavilhao, assim como os clientes no pavilhao, caso existam.
 Parametros: 	p - pavilhao a destruir
 Pre-condicoes: p != NULL
 ***********************************************/
void destroiPavilhao(pavilhao c){
    destroiDicEElems(c->pessoas, destroiGenCliente); // destroi a fila e os elementos (se estes existirem)
    destroiFilaEElems(c->filaTrampolins, destroiGenCliente);
    free(c->trampolins);
    free(c);
}

/***********************************************
 entraPavilhao - adiciona o cliente com o contribuinte, o numero de cidadao e o nome dados.
 Parametros: 	p - pavilhao;
 numContribuinte - numero contribuinte;
 numCidadao - numero cidadao;
 nome - nome;
 Pre-condicoes: p != NULL && numC > 0 && numCidadao > 0 && (nome != NULL)
 ***********************************************/
void entraPavilhao(pavilhao c, int numContribuinte, int numCidadao, char * nome){
    adicionaElemDicionario(c->pessoas, &numCidadao, criaCliente(numContribuinte, numCidadao, nome));
}

/***********************************************
 caixaPavilhao - retorna o valor em caixa.
 Parametros: 	p - pavilhao
 Pre-condicoes: p != NULL
 ***********************************************/
float caixaPavilhao(pavilhao c){
    return c->caixa;
}

/***********************************************
 clienteEmPavilhao - Verifica se existe o cliente no pavilhao.
 Parametros: 	p - pavilhao;	numCidadao - numero de cidadao;
 Pre-condicoes: p != NULL && numCidadao > 0
 ***********************************************/
cliente clienteEmPavilhao(pavilhao p, int numCidadao){
    return elementoDicionario(p->pessoas, &numCidadao);
}

/***********************************************
 saiPavilhao - Retira a pessoa do pavilhao e atualiza o valor a pagar.
 Parametros: 	p - pavilhao;	numCidadao - numero de cidadao;
 perm - permissao para sair;
 Pre-condicoes: p != NULL && numCidadao > 0
 ***********************************************/
cliente saiPavilhao(pavilhao p, int numCidadao, int * perm){
    cliente c = NULL;
    int tempo = 0;
    float conta = 0;
    * perm = 2;
    if (existeElemDicionario(p->pessoas, &numCidadao)) {
        c = elementoDicionario(p->pessoas, &numCidadao);
        if (isTrampolins(c)) {
            * perm = 0;
        }else{
            * perm = 1;
            tempo = mTotais(c);
            conta = (tempo/MINTRAMP) *PRECOTRAMP;
                        if (tempo%MINTRAMP != 0) {
                            conta +=5;
                        }
            if (contaCliente(c) == 0 && tempo == 0) {
                conta = 5;
            }
            adicionaConta(c, conta);
            p->caixa += conta;
            removeElemDicionario(p->pessoas, &numCidadao);
        }
        return c;
    }else{
        return NULL;
    }
}
/***********************************************
 fechaPavilhao - Fecha o pavilhao, atualiza as contas e as pessoas.
 Parametros: 	p - pavilhao;
 Pre-condicoes: p != NULL
 ***********************************************/
void fechaPavilhao(pavilhao p){
    iterador it = iteradorDicionario(p->pessoas);
    cliente c;
    int perm;
    saiFila(p);
    while (temSeguinteIterador(it)) {
        c = seguinteIterador(it);
        saiPavilhao(p, cidadaoCliente(c), &perm);
        if (perm == 0 ) {
            saiTrampolins(p, 24*60, cidadaoCliente(c));
            saiPavilhao(p, cidadaoCliente(c), &perm);
        }
    }
    destroiIterador(it);
}

/***********************************************
 entraFilaTrampolins - Move a pessoa para a fila dos trampolins.
 Parametros: 	p - pavilhao;	numCidadao - numero de cidadao;
 Pre-condicoes: p != NULL && numCidadao > 0
 ***********************************************/
void entraFilaTrampolins(pavilhao p , int numCidadao){
    cliente c = elementoDicionario(p->pessoas, &numCidadao);
    adicionaElemFila(p->filaTrampolins,c);
    setTrampolins(c);
}
/***********************************************
 saiFila - Retira todas as pessoa da fila para poder encerrar o pavilhao.
 Parametros: 	p - pavilhao;
 Pre-condicoes: p != NULL
 ***********************************************/
void saiFila(pavilhao p){
    while (!vaziaFila(p->filaTrampolins)) {
        cliente c = removeElemFila(p->filaTrampolins);
        removeTrampolins(c);
    }
}
/***********************************************
 adicionaVecTrampolim - adiciona uma pessoa ao vector dos trampolins.
 Parametros: 	p - pavilhao;	c - cliente;
 Pre-condicoes: p != NULL && c != NULL
 ***********************************************/
void adicionaVecTrampolim(pavilhao p , cliente c){
    int i;
    for (i = 0; i < p->nTrampolins; i++) {
        if (p->trampolins[i] == NULL) {
            p->trampolins[i] = c;
            break;
        }
    }
}

/***********************************************
 removeVecTrampolin - remove a pessoa do vector dos trampolins.
 Parametros: 	p - pavilhao;	numCidadao - numero de cidadao;
 Pre-condicoes: p != NULL && numCidadao > 0
 ***********************************************/
cliente removeVecTrampolim(pavilhao p, int numCidadao){
    cliente c = NULL;
    int i;
    for (i = 0; i < p->nTrampolins; i++) {
        if (p->trampolins[i] != NULL) {
            if (cidadaoCliente(p->trampolins[i]) == numCidadao) {
                c = p->trampolins[i];
                p->trampolins[i] = NULL;
                break;
            }
        }
    }
    return c;
}

/***********************************************
 entraTrampolins - Move o maximo de pessoas da fila dos trampolins para todos os trampolins livres.
 Parametros: 	p - pavilhao;	mEntrada - minutos de entrada do cliente;
 Pre-condicoes: p != NULL && mEntrada > 0
 ***********************************************/
int entraTrampolins(pavilhao p, int mEntrada){
    int numPessoas=0;
    cliente c = NULL;
    while(!(p->nTrampolinsLivres == 0 || vaziaFila(p->filaTrampolins))){
        c = removeElemFila(p->filaTrampolins);
        entraTempo(c, mEntrada);
        adicionaVecTrampolim(p,c);
        numPessoas++;
        p->nTrampolinsLivres --;
    }
    return numPessoas;
}

/***********************************************
 saiTrampolins - Retira a pessoa dos trampolins para o pavilhao e adiciona .
 Parametros: 	p - pavilhao;	nTempo - tempo de permanencia do cliente;
 numCidadao - numero de cidadao;
 Pre-condicoes: p != NULL && nTempo > 0 && numCidadao > 0
 ***********************************************/
void saiTrampolins(pavilhao p, int nTempo , int numCidadao){
    cliente c = removeVecTrampolim(p,numCidadao);
    int aux  = cidadaoCliente(c);
    adicionaTempo(c,nTempo - mEntrada(c));
    adicionaElemDicionario(p->pessoas,&aux, c);
    removeTrampolins(c);
    p->nTrampolinsLivres++;
}
/***********************************************
 pessoaTrampolim - Verifica se existe a pessoa no trampolim dado.
 Parametros: 	p - pavilhao;	nome - nome da pessoa;
 nTrampolim - numero do trampolim;
 Pre-condicoes: p != NULL && nome != NULL && numTrampolim > 0
 ***********************************************/
int pessoaTrampolim(pavilhao p, char * nome, int nTrampolim){
    if (nTrampolim > p->nTrampolins ) {
        return 0;
    }else if(p->trampolins[nTrampolim-1] == NULL){
        return 1;
    }else{
    	strcpy(nome,nomeCliente(p->trampolins[nTrampolim-1]));
    	return 2;
    }
}

/***********************************************
 trampolinsLivres - retorna o numero de trampolins livres.
 Parametros: 	p - pavilhao;
 Pre-condicoes: p != NULL
 ***********************************************/
int trampolinsLivres(pavilhao c){
    return c->nTrampolinsLivres;
}

/***********************************************
 vaziaFilaTrampolins - retorna 1 se a fila estiver vazia.
 Parametros: 	p - pavilhao;
 Pre-condicoes: p != NULL
 ***********************************************/
int vaziaFilaTrampolins(pavilhao c){
    return vaziaFila(c->filaTrampolins);
}

/***********************************************
 stock - retorna o stock do produto do tipo dado.
 Parametros: 	p - pavilhao; tipo - tipo de produto;
 Pre-condicoes: p != NULL && tipo > 0
 ***********************************************/
int stock(pavilhao p,int tipo){
    return p->produto[tipo].stock;
}

/***********************************************
 calculaConta - calcula o valor a pagar.
 Parametros: 	p - pavilhao; tipo - tipo de produto;
 quantidade - quantidade;
 Pre-condicoes: p != NULL && tipo > 0
 ***********************************************/
float calculaConta(pavilhao p , int quantidade , int tipo){
    if (p->produto[tipo].stock - quantidade < 0) {
        return -1;
    }else{
        p->produto[tipo].stock -= quantidade;
        return (quantidade * p->produto[tipo].preco);
    }
}
/***********************************************
 consumo - Regista a compra de um produto no cliente.
 Parametros: 	p - pavilhao;	tipo - tipo do consumo;
 numCidadao - numero do cidadao; quantidade- quantidade;
 Pre-condicoes: p != NULL && tipo > 0 && quantidade > 0
 && numCidadao > 0
 ***********************************************/
int consumo(pavilhao p ,char tipo ,int quantidade, int numCidadao){
    tipo = toupper(tipo);
    cliente c ;
    float conta = 0.0;
    switch (tipo){
        case 'C':conta = calculaConta(p, quantidade,0);break;
        case 'S':conta = calculaConta(p, quantidade,1);break;
        case 'B':conta = calculaConta(p, quantidade,2);break;
    }
    if (conta < 0) {
        return -1;
    }else{
        c = elementoDicionario(p->pessoas, &numCidadao);
        adicionaConta(c, conta);
        p->caixa += conta;
        return 1;
    }
}

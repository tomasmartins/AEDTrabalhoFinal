/*
 * pavilhao.c
 *
 */
// fazer todo o TAD usando a estrutura aqui dada

#include <stdio.h>
#include <stdlib.h>

#include "fila.h"
#include "cliente.h"
#include "pavilhão.h"

#define DOBRO 2
#define MAXPAV
struct _pavilhao{
   	fila pessoas; //colecao de clientes no sistema
    float caixa; //valor em caixa
};

/***********************************************
 criapavilhao - Criacao da instancia da estrutura associada a uma pavilhao.
 Parametros: 	nPessoas - numero previsto de pessoas;
 precoNormal - preco da lavagem normal (a especial é o dobro)
 Retorno: 	apontador para a instancia criada
 Pre-condicoes: nPessoas > 0 && precoNormal > 0
 ***********************************************/
pavilhao criaPavilhao(int nPessoas, float precoNormal){
    pavilhao p = (pavilhao) malloc(sizeof(struct _pavilhao)); // alloca memoria para a estrutura da pavilhao
    if (p==NULL)                                           // verifica se esta memoria foi allocada
        return NULL;
    p->pessoas = criaFila(nPessoas);                       // cria a fila de pessoas
    if (p->pessoas==NULL){                                 // se não foi possivel criar a fila, vai libertar a memoria da pavilhao
        free(p);
        return NULL;
    }
    p->caixa =  0.0;
    return p;
}

/***********************************************
 destroipavilhao - Liberta a memoria ocupada pela estrutura associada a pavilhao, assim como as pessoas na pavilhao, caso existam.
 Parametros: 	c - pavilhao a destruir
 Pre-condicoes: c != NULL
 ***********************************************/
void destroiPavilhao(pavilhao c){
    destroiFilaEElems(c->pessoas, destroiGenCliente); // destroi a fila e os elementos (se estes existirem)
    free(c);
}

/***********************************************
 entrapavilhao - adiciona o veiculo com o contribuinte dado e a lavagem escolhida.
 Parametros: 	c - pavilhao;	numC - numero de contribuinte;
 mat - matricula;	lav - tipo de lavagem
 Pre-condicoes: c != NULL && mat != NULL && numC > 0 && ((lav == 'N') || (lav == 'E'))
 ***********************************************/
void entraPavilhao(pavilhao c, int numContribuinte, int numCidadao, char * nome){
    cliente p = criaCliente(numContribuinte, numCidadao, nome);
    adicionaElemFila(c->pessoas, p);
}

/***********************************************
 pessoaspavilhao - retorna o numero de pessoas na pavilhao.
 Parametros: 	c - pavilhao
 Pre-condicoes: c != NULL
 ***********************************************/
int pessoasPavilhao(pavilhao c){
    return tamanhoFila(c->pessoas);
}

/***********************************************
 caixapavilhao - retorna o valor em caixa.
 Parametros: 	c - pavilhao
 Pre-condicoes: c != NULL
 ***********************************************/
float caixaPavilhao(pavilhao c){
    return c->caixa;
}
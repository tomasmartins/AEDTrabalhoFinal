/*
 * Módulo: cliente.c
 * Data: 03/06/2016
 * Descricao: TAD do cliente
 * Autores: Miguel Real e Tomas Martins
 *
 */
#include <stdlib.h>
#include <string.h>

#include "cliente.h"


struct _cliente{
    int numContribuinte;
    int numCidadao;
    char nome[50];
    int mEntrada;
    int mTotais;
    float conta;
    int isTrampolin;
};

/***********************************************
 criaCliente - Criacao da instancia da estrutura associada a uma cliente.
 Parametros: numC - numero contribuinte;
 numCidadao - numero cidadao;
 nome - nome
 Retorno: 	apontador para a instancia criada
 Pre-condicoes: 	numC > 0 && numCidadao > 0 && (nome != NULL)
 ***********************************************/
cliente criaCliente(int numContribuinte, int numCidadao, char * nome){
    cliente c = (cliente) malloc(sizeof(struct _cliente));
    if (c == NULL) // verifica se foi possivel alocar a memoria
        return NULL;
    strcpy(c->nome,nome);// Atribui os dados correspondentes ao cliente
    c->numContribuinte = numContribuinte;
    c->numCidadao = numCidadao;
    c->mEntrada = 0;
    c->mTotais = 0;
    c->conta = 0.0;
    c->isTrampolin = 0;
    return c;
    
}

/***********************************************
 destroiCliente - Liberta a memoria ocupada pela estrutura associada a cliente.
 Parametros: 	c - cliente a destruir
 Pre-condicoes: 	c != NULL
 ***********************************************/
void destroiCliente(cliente c){
    free(c);
}

/***********************************************
 destroiGenCliente - Liberta a memoria ocupada pela estrutura associada a cliente.
 Parametros: 	c - cliente a destruir do tipo void *
 Pre-condicoes: 	c != NULL
 ***********************************************/
void destroiGenCliente(void * c){
    destroiCliente((cliente) c);
}

/***********************************************
 nomeCliente - retorna o nome do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
char * nomeCliente(cliente c){
    return c->nome;
}

/***********************************************
 contribuinteCliente - retorna o numero de contribuinte do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
int contribuinteCliente(cliente c){
    return c->numContribuinte;
}

/***********************************************
 cidadaoCliente - retorna a numero de cidadao do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
int cidadaoCliente(cliente c){
    return c->numCidadao;
}

/***********************************************
 contaCliente - retorna a conta do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
float contaCliente(cliente c){
    return c->conta;
}

/***********************************************
 entraTempo - guarda os tempo de entrada em minutos no cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
void entraTempo(cliente c , int mEntrada){
    c->mEntrada = mEntrada;
}

/***********************************************
 mEntrada - Retorna os minutos de entrada do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
int mEntrada(cliente c){
    return c->mEntrada;
}

/***********************************************
 adicionaTempo - Adiciona minutos ao tempo total de permanencia do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
void adicionaTempo(cliente c , int adTotal){
    c->mTotais += adTotal;
}

/***********************************************
 mTotais - Retorna os minutos de permanencia totais do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
int mTotais(cliente c){
    return c->mTotais;
}

/***********************************************
 adicionaConta - Retorna os minutos de permanencia totais do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
void adicionaConta(cliente c, float adConta){
    c->conta += adConta;
}

/***********************************************
 setTrampolins- Torna 1 a variavel que indica se o cliente esta nos trampolins.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
void setTrampolins(cliente c){
    c->isTrampolin = 1;
}

/***********************************************
 removeTrampolins - Torna 0 a variavel que indica se o cliente esta nos trampolins.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
void removeTrampolins(cliente c){
    c->isTrampolin = 0;
}

/***********************************************
 isTrampolins - Retorna os a variavel que indica se o cliente esta nos trampolins.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
int isTrampolins(cliente c){
    return c->isTrampolin;
}

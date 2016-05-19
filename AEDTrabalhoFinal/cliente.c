/*
 * cliente.c
 *
 */

// FAZER

#include <stdlib.h>
#include <string.h>

#include "cliente.h"


struct _cliente{
	int numContribuinte;
	int numCidadao;
	char nome[50];
    float preco;
};

/***********************************************
 criaCliente - Criacao da instancia da estrutura associada a uma cliente.
 Parametros: numC - numero contribuinte;
 lav - tipo de lavagem;
 mat - matricula
 Retorno: 	apontador para a instancia criada
 Pre-condicoes: 	numC > 0 && (lav == 'N' || lav == 'E') && (mat != NULL)
 ***********************************************/
cliente criaCliente(int numContribuinte, int numCidadao, char * nome){
    cliente c = (cliente) malloc(sizeof(struct _cliente));
    if (c == NULL) // verifica se foi possivel alocar a memoria
        return NULL;
    strcpy(c->nome,nome);// Atribui os dados correspondentes ao cliente
    c->numContribuinte = numContribuinte;
    c->numCidadao = numCidadao;
    c->preco = 0.0;
    return c;
    
}

/***********************************************
 destroiCliente - Liberta a memoria ocupada pela estrutura associada a cliente.
 Parametros: 	p - cliente a destruir
 Pre-condicoes: 	p != NULL
 ***********************************************/
void destroiCliente(cliente c){
    free(c);
}

/***********************************************
 destroiGenCliente - Liberta a memoria ocupada pela estrutura associada a cliente.
 Parametros: 	p - cliente a destruir do tipo void *
 Pre-condicoes: 	p != NULL
 ***********************************************/
void destroiGenCliente(void * c){
    destroiCliente((cliente) c);
}

/***********************************************
 lavagemCliente - retorna o nome do cliente.
 Parametros:		p - cliente
 Pre-condicoes: 	p != NULL
 ***********************************************/
char * nomeCliente(cliente c){
    return c->nome;
}

/***********************************************
 contribuinteCliente - retorna o numero de contribuinte do cliente.
 Parametros:		p - cliente
 Pre-condicoes: 	p != NULL
 ***********************************************/
int contribuinteCliente(cliente p){
    return p->numContribuinte;
}

/***********************************************
 matriculaCliente - retorna a numero de cidadao do cliente.
 Parametros:		p - cliente
 Pre-condicoes: 	p != NULL
 ***********************************************/
void * cidadaoCliente(cliente p){
    return &(p->numCidadao);
}

float precoCliente(cliente c){
    return c->preco;
}


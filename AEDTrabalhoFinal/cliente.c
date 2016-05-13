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
	char lav;
	char mat[9];
};

/***********************************************
 criaCliente - Criacao da instancia da estrutura associada a uma cliente.
 Parametros: numC - numero contribuinte;
 lav - tipo de lavagem;
 mat - matricula
 Retorno: 	apontador para a instancia criada
 Pre-condicoes: 	numC > 0 && (lav == 'N' || lav == 'E') && (mat != NULL)
 ***********************************************/
cliente criaCliente(int numC, char lav,char * mat){
    cliente c = (cliente) malloc(sizeof(struct _cliente));
    if (c == NULL) // verifica se foi possivel alocar a memoria
        return NULL;
    strcpy(c->mat,mat);// Atribui os dados correspondentes ao cliente
    c->lav = lav;
    c->numC = numC;
    return c;
    
}

/***********************************************
 destroiCliente - Liberta a memoria ocupada pela estrutura associada a cliente.
 Parametros: 	p - cliente a destruir
 Pre-condicoes: 	p != NULL
 ***********************************************/
void destroiCliente(cliente p){
    free(p);
}

/***********************************************
 destroiGenCliente - Liberta a memoria ocupada pela estrutura associada a cliente.
 Parametros: 	p - cliente a destruir do tipo void *
 Pre-condicoes: 	p != NULL
 ***********************************************/
void destroiGenCliente(void * p){
    destroiCliente((cliente) p);
}

/***********************************************
 lavagemCliente - retorna o tipo de lavagem escolhido pelo cliente.
 Parametros:		p - cliente
 Pre-condicoes: 	p != NULL
 ***********************************************/
char lavagemCliente(cliente p){
    return p->lav;
}

/***********************************************
 contribuinteCliente - retorna o numero de contribuinte do cliente.
 Parametros:		p - cliente
 Pre-condicoes: 	p != NULL
 ***********************************************/
int contribuinteCliente(cliente p){
    return p->numC;
}

/***********************************************
 matriculaCliente - retorna a matricula do cliente.
 Parametros:		p - cliente
 Pre-condicoes: 	p != NULL
 ***********************************************/
char* matriculaCliente(cliente p){
    return p->mat;
}


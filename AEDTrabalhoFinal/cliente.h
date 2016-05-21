/*
 * cliente.h
 *
 *  Created on: 16 de Abr de 2016
 *      Author: fernanda
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

typedef struct _cliente * cliente;

/***********************************************
criaCliente - Criacao da instancia da estrutura associada a uma cliente.
Parametros: numC - numero contribuinte;
			lav - tipo de lavagem;
			mat - matricula
Retorno: 	apontador para a instancia criada
Pre-condicoes: 	numC > 0 && (lav == 'N' || lav == 'E') && (mat != NULL)
***********************************************/
cliente criaCliente(int numContribuinte, int numCidadao, char * nome);

/***********************************************
destroiCliente - Liberta a memoria ocupada pela estrutura associada a cliente.
Parametros: 	p - cliente a destruir
Pre-condicoes: 	p != NULL
***********************************************/
void destroiCliente(cliente c);

/***********************************************
destroiGenCliente - Liberta a memoria ocupada pela estrutura associada a cliente.
Parametros: 	p - cliente a destruir do tipo void *
Pre-condicoes: 	p != NULL
***********************************************/
void destroiGenCliente(void * c);

/***********************************************
lavagemCliente - retorna o tipo de lavagem escolhido pelo cliente.
Parametros:		p - cliente
Pre-condicoes: 	p != NULL
***********************************************/
char * nomeCliente(cliente c);

/***********************************************
contribuinteCliente - retorna o numero de contribuinte do cliente.
Parametros:		p - cliente
Pre-condicoes: 	p != NULL
***********************************************/
int contribuinteCliente(cliente c);

/***********************************************
 contribuinteCliente - retorna o numero de cidadao do cliente.
 Parametros:		p - cliente
 Pre-condicoes: 	p != NULL
 ***********************************************/
int cidadaoCliente(cliente c);
float precoCliente(cliente c);
void entraTempo(cliente c , int mEntrada);
void adicionaTempo(cliente c , int adTotal);
int mTotais(cliente c);
void adicionaConta(cliente c, float adConta);
int mEntrada(cliente c);
void adicionaTempo(cliente c , int adTotal);
int mTotais(cliente c);
void adicionaConta(cliente c, float adConta);
void setTrampolins(cliente c);
void removeTrampolins(cliente c);
int isTrampolins(cliente c);
#endif /* PESSOA_H_ */

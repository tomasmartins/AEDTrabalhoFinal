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
cliente criaCliente(int numC, char lav,char * mat);

/***********************************************
destroiCliente - Liberta a memoria ocupada pela estrutura associada a cliente.
Parametros: 	p - cliente a destruir
Pre-condicoes: 	p != NULL
***********************************************/
void destroiCliente(cliente p);

/***********************************************
destroiGenCliente - Liberta a memoria ocupada pela estrutura associada a cliente.
Parametros: 	p - cliente a destruir do tipo void *
Pre-condicoes: 	p != NULL
***********************************************/
void destroiGenCliente(void * p);

/***********************************************
lavagemCliente - retorna o tipo de lavagem escolhido pelo cliente.
Parametros:		p - cliente
Pre-condicoes: 	p != NULL
***********************************************/
char lavagemCliente(cliente p);

/***********************************************
contribuinteCliente - retorna o numero de contribuinte do cliente.
Parametros:		p - cliente
Pre-condicoes: 	p != NULL
***********************************************/
int contribuinteCliente(cliente p);

/***********************************************
matriculaCliente - retorna a matricula do cliente.
Parametros:		p - cliente
Pre-condicoes: 	p != NULL
***********************************************/
char* matriculaCliente(cliente p);

#endif /* PESSOA_H_ */

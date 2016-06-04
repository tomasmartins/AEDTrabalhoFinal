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
 Parametros: numContribuinte - numero contribuinte;
 numCidadao - numero cidadao;
 nome - nome
 Retorno: 	apontador para a instancia criada
 Pre-condicoes: numContribuinte > 0 && numCidadao > 0 && (nome != NULL)
 ***********************************************/
cliente criaCliente(int numContribuinte, int numCidadao, char * nome);

/***********************************************
 destroiCliente - Liberta a memoria ocupada pela estrutura associada a cliente.
 Parametros: 	c - cliente a destruir
 Pre-condicoes: 	c != NULL
 ***********************************************/
void destroiCliente(cliente c);

/***********************************************
 destroiGenCliente - Liberta a memoria ocupada pela estrutura associada a cliente.
 Parametros: 	c - cliente a destruir do tipo void *
 Pre-condicoes: 	c != NULL
 ***********************************************/
void destroiGenCliente(void * c);

/***********************************************
 nomeCliente - retorna o nome do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
char * nomeCliente(cliente c);

/***********************************************
 contribuinteCliente - retorna o numero de contribuinte do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
int contribuinteCliente(cliente c);

/***********************************************
 cidadaoCliente - retorna o numero de cidadao do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
int cidadaoCliente(cliente c);

/***********************************************
 contaCliente - retorna a conta do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
float contaCliente(cliente c);

/***********************************************
 entraTempo - guarda os tempo de entrda em minutos no cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
void entraTempo(cliente c , int mEntrada);

/***********************************************
 adicionaTempo - Adiciona minutos ao tempo total de permanencia do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
void adicionaTempo(cliente c , int adTotal);

/***********************************************
 mTotais - Retorna os minutos de permanencia totais do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
int mTotais(cliente c);

/***********************************************
 adicionaConta - Retorna os minutos de permanencia totais do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
void adicionaConta(cliente c, float adConta);

/***********************************************
 mEntrada - Retorna os minutos de entrada do cliente.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
int mEntrada(cliente c);

/***********************************************
 setTrampolins- Torna 1 a variavel que indica se o cliente esta nos trampolins.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
void setTrampolins(cliente c);

/***********************************************
 removeTrampolins - Torna 0 a variavel que indica se o cliente esta nos trampolins.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
void removeTrampolins(cliente c);

/***********************************************
 isTrampolins - Retorna os a variavel que indica se o cliente esta nos trampolins.
 Parametros:		c - cliente
 Pre-condicoes: 	c != NULL
 ***********************************************/
int isTrampolins(cliente c);
#endif /* CLIENTE_H_ */

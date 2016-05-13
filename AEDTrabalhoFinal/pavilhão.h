/*
 * pavilhao.h
 *
 *  Created on: 16 de Abr de 2016
 *      Author: fernanda
 */

#ifndef pavilhao_H_
#define pavilhao_H_

/* Tipo do TAD pavilhao */
typedef struct _pavilhao * pavilhao;

/***********************************************
criapavilhao - Criacao da instancia da estrutura associada a uma cantina.
Parametros: 	nPessoas - numero previsto de pessoas;
		precoNormal - preco da lavagem normal (a especial Ž o dobro)
Retorno: 	apontador para a instancia criada
Pre-condicoes: nPessoas > 0 && precoNormal > 0
***********************************************/
pavilhao criaPavilhao(int nPessoas, float precoNormal);

/***********************************************
destroiCantina - Liberta a memoria ocupada pela estrutura associada a cantina, assim como as pessoas na cantina, caso existam.
Parametros: 	c - pavilhao a destruir
Pre-condicoes: c != NULL
***********************************************/
void destroiPavilhao(pavilhao c);

/***********************************************
entrapavilhao - adiciona o veiculo com o contribuinte dado e a lavagem escolhida.
Parametros: 	c - pavilhao;	numC - numero de contribuinte;
				mat - matricula;	lav - tipo de lavagem
Pre-condicoes: c != NULL && mat != NULL && numC > 0 && ((lav == 'N') || (lav == 'E'))
***********************************************/
void entraPavilhao(pavilhao c, int numC, char* mat, char lav);

/***********************************************
pessoaspavilhao - retorna o numero de pessoas na pavilhao.
Parametros: 	c - pavilhao
Pre-condicoes: c != NULL
***********************************************/
int pessoasPavilhao(pavilhao c);

/***********************************************
regLavagempavilhao - simula o fim da lavagem do veiculo que se encontra h‡ mais tempo na pavilhao, e retorna o cliente.
Neste momento regista/actualiza a lavagem e o valor em caixa.
Parametros: 	c - pavilhao
Retorno: 	cliente ha mais tempo
Pre-condicoes: c != NULL && pessoaspavilhao(c) > 0
***********************************************/
cliente regLavagemPavilhao(pavilhao c);

/***********************************************
lavagempavilhao - retorna o numero de lavagens registadas do tipo indicado.
Parametros:	c - pavilhao; lav - tipo de lavagem
Pre-condicoes: c != NULL && ((lav == 'N') || (lav == 'E'))
***********************************************/
int  lavagemPavilhao(pavilhao c, char lav);

/***********************************************
caixapavilhao - retorna o valor em caixa.
Parametros: 	c - pavilhao
Pre-condicoes: c != NULL
***********************************************/
float  caixaPavilhao(pavilhao c);

#endif /* pavilhao_H_ */

/*
 * maquina.h
 *
 *  Created on: 16 de Abr de 2016
 *      Author: fernanda
 */

#ifndef MAQUINA_H_
#define MAQUINA_H_

/* Tipo do TAD maquina */
typedef struct _maquina * maquina;

/***********************************************
criaMaquina - Criacao da instancia da estrutura associada a uma cantina.
Parametros: 	nPessoas - numero previsto de pessoas;
		precoNormal - preco da lavagem normal (a especial Ž o dobro)
Retorno: 	apontador para a instancia criada
Pre-condicoes: nPessoas > 0 && precoNormal > 0
***********************************************/
maquina criaMaquina(int nPessoas, float precoNormal);

/***********************************************
destroiCantina - Liberta a memoria ocupada pela estrutura associada a cantina, assim como as pessoas na cantina, caso existam.
Parametros: 	c - maquina a destruir
Pre-condicoes: c != NULL
***********************************************/
void destroiMaquina(maquina c);

/***********************************************
entraMaquina - adiciona o veiculo com o contribuinte dado e a lavagem escolhida.
Parametros: 	c - maquina;	numC - numero de contribuinte;
				mat - matricula;	lav - tipo de lavagem
Pre-condicoes: c != NULL && mat != NULL && numC > 0 && ((lav == 'N') || (lav == 'E'))
***********************************************/
void entraMaquina(maquina c, int numC, char* mat, char lav);

/***********************************************
pessoasMaquina - retorna o numero de pessoas na maquina.
Parametros: 	c - maquina
Pre-condicoes: c != NULL
***********************************************/
int pessoasMaquina(maquina c);

/***********************************************
regLavagemMaquina - simula o fim da lavagem do veiculo que se encontra h‡ mais tempo na maquina, e retorna o cliente.
Neste momento regista/actualiza a lavagem e o valor em caixa.
Parametros: 	c - maquina
Retorno: 	cliente ha mais tempo
Pre-condicoes: c != NULL && pessoasMaquina(c) > 0
***********************************************/
cliente regLavagemMaquina(maquina c);

/***********************************************
lavagemMaquina - retorna o numero de lavagens registadas do tipo indicado.
Parametros:	c - maquina; lav - tipo de lavagem
Pre-condicoes: c != NULL && ((lav == 'N') || (lav == 'E'))
***********************************************/
int  lavagemMaquina(maquina c, char lav);

/***********************************************
caixaMaquina - retorna o valor em caixa.
Parametros: 	c - maquina
Pre-condicoes: c != NULL
***********************************************/
float  caixaMaquina(maquina c);

#endif /* MAQUINA_H_ */

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
pavilhao criaPavilhao(int nTrampolins, int sCafe, float vCafe ,int sSumo,float vSumo,int sBolo , float vBolo );

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
void entraPavilhao(pavilhao p, int numContribuinte, int numCidadao, char * nome);

/***********************************************
pessoaspavilhao - retorna o numero de pessoas na pavilhao.
Parametros: 	c - pavilhao
Pre-condicoes: c != NULL
***********************************************/
int pessoasPavilhao(pavilhao c);

/***********************************************
caixapavilhao - retorna o valor em caixa.
Parametros: 	c - pavilhao
Pre-condicoes: c != NULL
***********************************************/
float  caixaPavilhao(pavilhao c);

/***********************************************
 saipavilhao - adiciona o veiculo com o contribuinte dado e a lavagem escolhida.
 Parametros: 	c - pavilhao;	numC - numero de contribuinte;
 mat - matricula;	lav - tipo de lavagem
 Pre-condicoes: c != NULL && mat != NULL && numC > 0 && ((lav == 'N') || (lav == 'E'))
 ***********************************************/
cliente saiPavilhao(pavilhao p, int numCidadao, int * perm);

void entraFilaTrampolins(pavilhao p , int numContribuinte);

int entraTrampolins(pavilhao p, int mEntrada);
int stock(pavilhao p,int tipo);

void saiTrampolins(pavilhao p, int nTempo , int numCidadao);
int pessoaTrampolin(pavilhao p, char * nome, int nTrampolim);
void fechaPavilhao(pavilhao p);
int consumo(pavilhao p ,char tipo ,int quantidade, int numCidadao);
int trampolinsLivres(pavilhao c);
cliente clienteEmPavilhao(pavilhao p, int numCidadao);
int vaziaFilaTrampolins(pavilhao c);
float calculaConta(pavilhao p , int quantidade , int tipo);
#endif /* pavilhao_H_ */

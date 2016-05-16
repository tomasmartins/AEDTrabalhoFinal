/*
 * dicionario.c
 */
#include <stdlib.h>
#include "iterador.h"
#include "dicionario.h"
#include "chaves.h"
#include "tuplo.h"

/*  Estrutura de dados do tipo de dados: dicionario ---> os elementos não podem ser repetidos com base num identificador (chave) dos elementos */
struct _dicionario{
	tuplo * elems; // apontador para vector de tuplos (chave,elemento)
	int numElems;
	int capacidade;
	int tipoCh; // 0-inteiro; 1-string
};

/* Prototipos das funcoes associadas a um dicionario */

/***********************************************
criaDicionario - Criacao da instancia da estrutura associada a um dicionario.
Parametros:
     cap - capacidade prevista do dicionario
     TipoChave – 0 – inteiro, 1 - string
Retorno: apontador para a  instancia criada
Pre-condicoes:
***********************************************/
dicionario criaDicionario(int cap, int tipoChave){
	dicionario d;
	d = (dicionario) malloc(sizeof(struct _dicionario));
	if ( d == NULL) return NULL;
	d->elems = (tuplo *) malloc(sizeof(tuplo) * cap);
	if (d->elems == NULL){
		free(d);
		return NULL;
	}
	d->numElems = 0;
	d->capacidade = cap;
	d->tipoCh =tipoChave;
	return d;
}

/***********************************************
destroiDicionario - Liberta a memoria ocupada pela instancia da estrutura associada ao dicionario.
Parametros:	d - dicionario a destruir
Retorno:
Pre-condicoes: d != NULL
***********************************************/
void destroiDicionario (dicionario d ){
	int i;
	for(i=0;i<d->numElems;i++)
		destroiTuplo(d->elems[i]);
	free(d->elems);
	free(d);
}

/***********************************************
destroiDicEElems - Liberta a memoria ocupada pela instancia da estrutura associada ao dicionario e os elementos.
Parametros:
	d - dicionario a destruir	destroi - função para destruição os elementos
Retorno:
Pre-condicoes: d != NULL
***********************************************/
void destroiDicEElems(dicionario d, void (*destroi)(void *) ){
	int i;
	for(i=0;i < d->numElems;i++){
		destroi(segTuplo(d->elems[i]));
		destroiTuplo(d->elems[i]);
	}
	free(d->elems);
	free(d);
}

/***********************************************
vazioDicionario - Indica se o dicionario está vazio.
Parametros:
	d - dicionario
Retorno: 1- caso dicionario vazio; 0 - caso contrário
Pre-condicoes: d != NULL
***********************************************/
int vazioDicionario(dicionario d){
	if (d->numElems == 0)
		return 1;
	return 0;
}

/***********************************************
tamanhoDicionario - Consulta o numero de elementos no dicionario.
Parametros:
	d - dicionario
Retorno: numero de elementos no dicionario
Pre-condicoes: d != NULL
***********************************************/
int tamanhoDicionario(dicionario d){
	return d->numElems;
}
/* Função para calcular a posição dum dado elemento no vector */
int posElemDicionario(dicionario d, void * ch){
	int i;
	for (i = 0; i<d->numElems;i++)
		if (igualChaves(ch,priTuplo(d->elems[i]),d->tipoCh) == 1)
			return i;
	return -1;
}
/***********************************************
existeElemDicionario – Indica se o elemento  com a chave dada existe no dicionario.
Parametros:
	d – dicionario
	ch – endereço da chave do elemento
Retorno: retorna 1 se existir, e 0, caso contrário
Pre-condicoes: d != NULL
***********************************************/
int existeElemDicionario(dicionario d, void * ch){
	if (posElemDicionario(d,ch) != -1)
		return 1;
	return 0;
}

/***********************************************
elementoDicionario - retorna o elemento no dicionario com a chave dada
Parametros:
	d – dicionario	ch - endereco da chave do elemento
Retorno: retorna o elemento
Pre-condicoes: d != NULL
***********************************************/
void * elementoDicionario(dicionario d, void * ch){
	int pos = posElemDicionario(d,ch);
	if (pos != -1)
		return segTuplo(d->elems[pos]);
	return NULL;
}
/* Aumenta o vector do dicionario */
void incDicionario (dicionario d){
	int i = 0;
	tuplo* aux = (tuplo *)malloc(sizeof(tuplo) * d->capacidade*2); // duplica
	for (;i<d->numElems;i++)
		aux[i] = d->elems[i];
	free(d->elems);
	d->elems = aux;
	d->capacidade = d->capacidade * 2;
}

/***********************************************
adicionaElemDicionario - Adiciona o elemento dado no dicionario, se não existir um elemento com a mesma chave.
Parametros:
	d – dicionario
	ch - endereço da chave do elemento
	elem - endereco do elemento
Retorno: Retorna 1 se adicionar, e 0, caso contrário
Pre-condicoes: d != NULL
***********************************************/
int adicionaElemDicionario(dicionario d, void * ch, void * elem){
	int pos = posElemDicionario(d,ch);
	if (pos != -1)
		return 0;
	if (d->numElems == d->capacidade)
		incDicionario(d);
	d->elems[d->numElems++] = criaTuplo(d->tipoCh,ch,elem);
	return 1;
}

/***********************************************
removeElemDicionario - Remove o elemento com a chave dada no dicionario, se existir.
Parametros:
	d – dicionario	ch – endereco da chave
Retorno: Retorna o elemento, caso exista ou NULL, caso contrario
Pre-condicoes: d != NULL
***********************************************/
void * removeElemDicionario(dicionario d, void * ch){
	void * elem;
	int pos = posElemDicionario(d,ch);
	if (pos == -1)
		return NULL;
	elem = segTuplo(d->elems[pos]);
	destroiTuplo(d->elems[pos]);
	d->elems[pos] = d->elems[--d->numElems];
	return elem;
}

/***********************************************
iteradorDicionario - Cria e devolve um iterador para os elementos do dicionario.
Parametros:
d - dicionario
Retorno: iterador do dicionario
Pre-condicoes: d != NULL && vazioDicionario(d)!=1
***********************************************/
iterador iteradorDicionario(dicionario d){
	int i;
	// vector com os elementos do dicionário
	void * * aux = (void * *) malloc(sizeof(void *)* d->numElems);
	for(i=0;i<d->numElems;i++)
		aux[i]=segTuplo(d->elems[i]);
	return criaIterador(aux,d->numElems);
}

/***********************************************
iteradorChaveDicionario - Cria e devolve um iterador para as chaves dos elementos guardados no dicionario.
Parametros: d - dicionario
Retorno: iterador das chaves dos elementos no dicionario
Pre-condicoes: d != NULL && vazioDicionario(d)!=1
***********************************************/
iterador iteradorChaveDicionario(dicionario d){

	int i;
	// vector com as chaves dos elementos do dicionário
	void * * aux = (void * *) malloc(sizeof(void *)* d->numElems);
	for(i=0;i<d->numElems;i++)
		aux[i]=priTuplo(d->elems[i]);
	return criaIterador(aux,d->numElems);
}



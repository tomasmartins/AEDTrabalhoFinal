/*
 * tuplo.h
 *
 */

#ifndef TUPLO_H_
#define TUPLO_H_

/* Tipo do TAD tuplo */
typedef struct _tuplo * tuplo;

/* Prot�tipos das fun��es associadas a um tuplo - TAD tuplo */

/***********************************************
criaTuplo - Cria��o da inst�ncia da estrutura associada a um tuplo.
Par�metros:
	tipoPri � 0 � inteiro, 1 - string
	pri - primeiro elemento a guardar no tuplo (void *)
	seg - segundo elemento a guardar no tuplo (void *)
Retorno: apontador para a inst�ncia criada
Pr�-condi��es:
***********************************************/
tuplo criaTuplo(int tipoPri, void * pri, void * seg);

/***********************************************
destroiTuplo - Liberta a mem�ria ocupada pela inst�ncia da estrutura associada ao tuplo.
Par�metros:
	t - tuplo a destruir
Retorno:
Pr�-condi��es: t != NULL
***********************************************/
void destroiTuplo(tuplo t);

/***********************************************
priTuplo - Retorna o primeiro elemento no tuplo dado.
Par�metros:
	t - tuplo
Retorno: elemento (void *)
Pr�-condi��es: t != NULL
***********************************************/
void * priTuplo(tuplo t);

/***********************************************
segTuplo - Retorna o segundo elemento no tuplo dado.
Par�metros:
	t - tuplo
Retorno: elemento (void *)
Pr�-condi��es: t != NULL
***********************************************/
void * segTuplo(tuplo t);

#endif /* TUPLO_H_ */

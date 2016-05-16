/*
 * chaves.h
 */

#ifndef _H_CHAVES
#define _H_CHAVES

/***********************************************
igualChaves - Indica se duas chaves de um dado tipo s�o iguais.
Par�metros:
	ch1 - chave (void *)
	ch2 - chave (void *)
	tipo - 0 - inteiro; 1- string
Retorno: 1 - caso as chaves sejam iguais; 0- caso contr�rio
Pr�-condi��es: a1 != NULL && a2 != NULL
**********************************************/
int igualChaves (void * ch1, void * ch2, int tipo);


#endif /* CHAVES_H_ */

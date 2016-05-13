/*
 * maquina.c
 *
 */
// fazer todo o TAD usando a estrutura aqui dada

#include <stdio.h>
#include <stdlib.h>

#include "fila.h"
#include "cliente.h"
#include "maquina.h"

#define DOBRO 2

struct _maquina{
   	fila pessoas; //colecao de clientes no sistema
	int nNormal; //numero de lavagens normais registadas e pagas
	int nEspecial; // numero de lavagens especiais registadas e pagas
	float preco; // preco da lavagem normal
	float caixa; //valor em caixa
};

/***********************************************
 criaMaquina - Criacao da instancia da estrutura associada a uma maquina.
 Parametros: 	nPessoas - numero previsto de pessoas;
 precoNormal - preco da lavagem normal (a especial é o dobro)
 Retorno: 	apontador para a instancia criada
 Pre-condicoes: nPessoas > 0 && precoNormal > 0
 ***********************************************/
maquina criaMaquina(int nPessoas, float precoNormal){
    maquina c = (maquina) malloc(sizeof(struct _maquina)); // alloca memoria para a estrutura da maquina
    if (c==NULL)                                           // verifica se esta memoria foi allocada
        return NULL;
    c->pessoas = criaFila(nPessoas);                       // cria a fila de pessoas
    if (c->pessoas==NULL){                                 // se não foi possivel criar a fila, vai libertar a memoria da maquina
        free(c);
        return NULL;
    }
    c->nNormal = 0;  //inicializa o numero de lavagens e o dinheiro em caixa a 0
    c->nEspecial = 0;
    c->caixa =  0.0;
    c->preco = precoNormal;//atribui o preço de cada lavagem
    return c;
}

/***********************************************
 destroimaquina - Liberta a memoria ocupada pela estrutura associada a maquina, assim como as pessoas na maquina, caso existam.
 Parametros: 	c - maquina a destruir
 Pre-condicoes: c != NULL
 ***********************************************/
void destroiMaquina(maquina c){
    destroiFilaEElems(c->pessoas, destroiGenCliente); // destroi a fila e os elementos (se estes existirem)
    free(c);
}

/***********************************************
 entraMaquina - adiciona o veiculo com o contribuinte dado e a lavagem escolhida.
 Parametros: 	c - maquina;	numC - numero de contribuinte;
 mat - matricula;	lav - tipo de lavagem
 Pre-condicoes: c != NULL && mat != NULL && numC > 0 && ((lav == 'N') || (lav == 'E'))
 ***********************************************/
void entraMaquina(maquina c, int numC, char* mat, char lav){
    cliente p = criaCliente(numC, lav, mat);
    adicionaElemFila(c->pessoas, p);
}

/***********************************************
 pessoasMaquina - retorna o numero de pessoas na maquina.
 Parametros: 	c - maquina
 Pre-condicoes: c != NULL
 ***********************************************/
int pessoasMaquina(maquina c){
    return tamanhoFila(c->pessoas);
}

/***********************************************
 regLavagemMaquina - simula o fim da lavagem do veiculo que se encontra há mais tempo na maquina, e retorna o cliente.
 Neste momento regista/actualiza a lavagem e o valor em caixa.
 Parametros: 	c - maquina
 Retorno: 	cliente ha mais tempo
 Pre-condicoes: c != NULL && pessoasMaquina(c) > 0
 ***********************************************/
cliente regLavagemMaquina(maquina c){
    cliente p = removeElemFila(c->pessoas);
    if(lavagemCliente(p)=='N'){// incrementa o numero de lavagens efectuadas
        c->nNormal++;
        c->caixa += c->preco;// atualiza o valor em caixa
    }
    else{
        c->nEspecial++;
        c->caixa += (c->preco*DOBRO);// atualiza o valor em caixa
    }
    return p;
}

/***********************************************
 lavagemMaquina - retorna o numero de lavagens registadas do tipo indicado.
 Parametros:	c - maquina; lav - tipo de lavagem
 Pre-condicoes: c != NULL && ((lav == 'N') || (lav == 'E'))
 ***********************************************/
int lavagemMaquina(maquina c, char lav){
    if(lav == 'E'){ //Se o for a lavagem especial retorna o numero de lavagem especiais se não for especial tem de ser Normal
        return c->nEspecial;
    }
    return c->nNormal;
}

/***********************************************
 caixaMaquina - retorna o valor em caixa.
 Parametros: 	c - maquina
 Pre-condicoes: c != NULL
 ***********************************************/
float caixaMaquina(maquina c){
    return c->caixa;
}
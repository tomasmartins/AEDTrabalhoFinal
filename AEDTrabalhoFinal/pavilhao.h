/*
 * Módulo: pavilhao.h
 * Data: 03/06/2016
 * Descricao: ficheiro .h do TAD pavilhao
 * Autores: Miguel Real e Tomas Martins
 */

#ifndef pavilhao_H_
#define pavilhao_H_
/* Tipo do TAD pavilhao */
typedef struct _pavilhao * pavilhao;

/***********************************************
 criapavilhao - Criacao da instancia da estrutura associada a um pavilhao.
 Parametros: 	nTrampolins - numero de Trampolins;
 sCafe - stock de cafe;
 vCafe - preco do cafe;
 sSumo - stock de sumo;
 vSumo - preco do sumo;
 sBolo - stock de bolo;
 vBolo - preco do bolo;
 Retorno: 	apontador para a instancia criada
 Pre-condicoes: nPessoas > 0 && precoNormal > 0
 ***********************************************/
pavilhao criaPavilhao(int nTrampolins, int sCafe, float vCafe ,int sSumo,float vSumo,int sBolo , float vBolo );

/***********************************************
 destroiPavilhao - Liberta a memoria ocupada pela estrutura associada ao pavilhao, assim como os clientes no pavilhao, caso existam.
 Parametros: 	p - pavilhao a destruir
 Pre-condicoes: p != NULL
 ***********************************************/
void destroiPavilhao(pavilhao p);

/***********************************************
 entraPavilhao - adiciona o cliente com o contribuinte, o numero de cidadao e o nome dados.
 Parametros: 	p - pavilhao;
 numContribuinte - numero contribuinte;
 numCidadao - numero cidadao;
 nome - nome;
 Pre-condicoes: p != NULL && numC > 0 && numCidadao > 0 && (nome != NULL)
 ***********************************************/
void entraPavilhao(pavilhao p, int numContribuinte, int numCidadao, char * nome);

/***********************************************
 caixaPavilhao - retorna o valor em caixa.
 Parametros: 	p - pavilhao
 Pre-condicoes: p != NULL
 ***********************************************/
float  caixaPavilhao(pavilhao p);

/***********************************************
 clienteEmPavilhao - Verifica se existe o cliente no pavilhao.
 Parametros: 	p - pavilhao;	numCidadao - numero de cidadao;
 Pre-condicoes: p != NULL && numCidadao > 0
 ***********************************************/
cliente clienteEmPavilhao(pavilhao p, int numCidadao);

/***********************************************
 saiPavilhao - Retira a pessoa do pavilhao e atualiza o valor a pagar.
 Parametros: 	p - pavilhao;	numCidadao - numero de cidadao;
 perm - permissao para sair;
 Pre-condicoes: p != NULL && numCidadao > 0
 ***********************************************/
cliente saiPavilhao(pavilhao p, int numCidadao, int * perm);

/***********************************************
 fechaPavilhao - Fecha o pavilhao, atualiza as contas e as pessoas.
 Parametros: 	p - pavilhao;
 Pre-condicoes: p != NULL
 ***********************************************/
void fechaPavilhao(pavilhao p);

/***********************************************
 entraFilaTrampolins - Move a pessoa para a fila dos trampolins.
 Parametros: 	p - pavilhao;	numContribuinte - numero de contribuinte;
 Pre-condicoes: p != NULL && numContribuinte > 0
 ***********************************************/
void entraFilaTrampolins(pavilhao p , int numContribuinte);

/***********************************************
 adicionaVecTrampolim - adiciona uma pessoa ao vector dos trampolins.
 Parametros: 	p - pavilhao;	c - cliente;
 Pre-condicoes: p != NULL && c != NULL
 ***********************************************/
void adicionaVecTrampolim(pavilhao p , cliente c);

/***********************************************
 removeVecTrampolin - remove a pessoa do vector dos trampolins.
 Parametros: 	p - pavilhao;	numCidadao - numero de cidadao;
 Pre-condicoes: p != NULL && numCidadao > 0
 ***********************************************/
cliente removeVecTrampolim(pavilhao p, int numCidadao);

/***********************************************
 entraTrampolins - Move o maximo de pessoas da fila dos trampolins para todos os trampolins livres.
 Parametros: 	p - pavilhao;	mEntrada - minutos de entrada do cliente;
 Pre-condicoes: p != NULL && mEntrada > 0
 ***********************************************/
int entraTrampolins(pavilhao p, int mEntrada);

/***********************************************
 saiTrampolins - Retira a pessoa dos trampolins para o pavilhao e adiciona .
 Parametros: 	p - pavilhao;	nTempo - tempo de permanencia do cliente;
 numCidadao - numero de cidadao;
 Pre-condicoes: p != NULL && nTempo > 0 && numCidadao > 0
 ***********************************************/
void saiTrampolins(pavilhao p, int nTempo , int numCidadao);

/***********************************************
 pessoaTrampolim - Verifica se existe a pessoa no trampolim dado.
 Parametros: 	p - pavilhao;	nome - nome da pessoa;
 nTrampolim - numero do trampolim;
 Pre-condicoes: p != NULL && nome != NULL && numTrampolim > 0
 ***********************************************/
int pessoaTrampolim(pavilhao p, char * nome, int nTrampolim);

/***********************************************
 trampolinsLivres - retorna o numero de trampolins livres.
 Parametros: 	p - pavilhao;
 Pre-condicoes: p != NULL
 ***********************************************/
int trampolinsLivres(pavilhao P);

/***********************************************
 vaziaFilaTrampolins - retorna 1 se a fila estiver vazia.
 Parametros: 	p - pavilhao;
 Pre-condicoes: p != NULL
 ***********************************************/
int vaziaFilaTrampolins(pavilhao p);

/***********************************************
 stock - retorna o stock do produto do tipo dado.
 Parametros: 	p - pavilhao; tipo - tipo de produto;
 Pre-condicoes: p != NULL && tipo > 0
 ***********************************************/
int stock(pavilhao p,int tipo);

/***********************************************
 calculaConta - calcula o valor a pagar.
 Parametros: 	p - pavilhao; tipo - tipo de produto;
 quantidade - quantidade;
 Pre-condicoes: p != NULL && tipo > 0
 ***********************************************/
float calculaConta(pavilhao p , int quantidade , int tipo);

/***********************************************
 consumo - Regista a compra de um produto no cliente.
 Parametros: 	p - pavilhao;	tipo - tipo do consumo;
 numCidadao - numero do cidadao; quantidade- quantidade;
 Pre-condicoes: p != NULL && tipo > 0 && quantidade > 0
 && numCidadao > 0
 ***********************************************/
int consumo(pavilhao p ,char tipo ,int quantidade, int numCidadao);
/***********************************************
 saiFila - Retira todas as pessoa da fila para poder encerrar o pavilhao.
 Parametros: 	p - pavilhao;
 Pre-condicoes: p != NULL
 ***********************************************/
void saiFila(pavilhao p);

#endif /* pavilhao_H_ */
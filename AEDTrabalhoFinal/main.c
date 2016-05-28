/*
 * main_interpreta.c
 *
 *  Created on: 12 de April de 2016
 *      Author: carmen
 */
#include <stdio.h>
#include <ctype.h>

/* TAD usado */

#include "cliente.h"
#include "pavilhao.h"
#include "tuplo.h"
#include "chaves.h"
#include "cliente.h"
#include "dicionario.h"
#include "cliente.h"
#include "fila.h"
#include "iterador.h"
#define MAXLINHA 30

void interpretador(pavilhao r);

int main(void){
    char linha[MAXLINHA];
    int nTrampolins,sCafe,sSumo,sBolo;
    float vCafe,vSumo,vBolo;
    
    setvbuf(stdout,NULL,_IONBF, 0);
    fgets(linha, MAXLINHA, stdin);
    sscanf(linha,"%d",&nTrampolins);
    fgets(linha, MAXLINHA, stdin);
    sscanf(linha,"%d %f",&sCafe,&vCafe);
    fgets(linha, MAXLINHA, stdin);
    sscanf(linha,"%d %f",&sSumo,&vSumo);
    fgets(linha, MAXLINHA, stdin);
    sscanf(linha,"%d %f",&sBolo,&vBolo);
    if ((nTrampolins >0) && (sCafe >0) && (vCafe >0) && (sSumo >0) && (vSumo >0) && (sBolo >0) && (vBolo >0)){
        pavilhao  fct= criaPavilhao(nTrampolins, sCafe, vCafe, sSumo, vSumo, sBolo, vBolo);
        printf("Abertura pavilhao.\n");
        interpretador(fct);
        destroiPavilhao(fct);
    }
    return 0;
}

void registaEntrada(pavilhao c, char * linha){
    char  nome[50]; char l;
    int numCidadao, numContribuinte;
    sscanf(linha,"%c %d %d\n",&l,&numCidadao,&numContribuinte);
    scanf(" %s" ,nome);
    getchar(); //Clean the buffer
    if(existePavilhao(c, numCidadao))
        printf("Pessoa ja no pavilhao.\n");
    else{
        entraPavilhao(c, numContribuinte, numCidadao, nome);
        printf("Entrada autorizada.\n");
    }
    
}
//***********************************************************************

void entradaFila(pavilhao c, char * linha){
    int numCidadao;
    char l;
    sscanf(linha,"%c %d",&l,&numCidadao);
    
    if((existePavilhao(c, numCidadao))!=1)
        printf("Pessoa nao esta no pavilhao.\n");
    else{
        entraFilaTrampolins(c, numCidadao);
        printf("Entrada autorizada.\n");
    }
    
}

//************************************************************************

void OPENTHEGATES(pavilhao c, char * linha){
    int hora, minutos, tEntrada;
    char l;
    sscanf(linha,"%c %d %d",&l,&hora,&minutos);
    tEntrada=(60*hora)+minutos;
    
    if((trampolinsLivres(c))==0){
        printf("Trampolins ocupados.\n");
    }else{
        if(vaziaFilaTrampolins(c)){
            printf("Fila vazia.\n");
        }else{
            printf("Entrada de %d pessoas nos trampolins.\n", entraTrampolins(c, tEntrada));
        }
        
        
    }
    //************************************************************************
}
void pessoaTrampolins(pavilhao c , char * linha){
    int nTrampolin;
    char nome[50], l;
    int perm;
    sscanf(linha,"%c %d",&l,&nTrampolin);
    perm = pessoaTrampolin(c, nome, nTrampolin);
    if (perm == 0) {
        printf("Trampolim inexistente.\n");
    }else if (perm == 1){
        printf("Trampolim vazio.\n");
    }else{
        printf("Pessoa %s esta no trampolim.\n", nome);
    }
}

//************************************************************************

void saiTrampolin(pavilhao p, char * linha){
    int numCidadao;
    int hora;
    int minutos;
    char l;
    sscanf(linha, "%c %d %d:%d",&l,&numCidadao,&hora,&minutos);
    minutos += hora*60;
    if (minutos <= mEntrada(clienteEmPavilhao(p,numCidadao))) {
        printf("Saida trampolim nao autorizada.\n");
    }else if (existePavilhao(p, numCidadao)){
        saiTrampolins(p, minutos, numCidadao);
        printf("Saida trampolim autorizada.\n");
    } else {
        printf("Pessoa n„o esta no pavilhao.\n");
    }
}

//************************************************************************

void registaCompra(pavilhao p, char * linha){
    char tipoConsumo,l;
    int quantidade, numCidadao;
    cliente c;

    if (sscanf(linha,"%c %c %d %d",&l,&tipoConsumo,&quantidade,&numCidadao)!=4)
        printf("Dados invalidos.\n");
    else{
        c = clienteEmPavilhao(p, numCidadao);
        if(isTrampolins(c))
            printf("Venda nao autorizada.\n");
        else{
            if((existePavilhao(p, numCidadao))!=1)
                printf("Pessoa nao esta no pavilhao.\n");
            else{
                tipoConsumo = toupper(tipoConsumo);
                if (tipoConsumo=='C'||tipoConsumo=='B'||tipoConsumo=='S'){
                    if(consumo(p,tipoConsumo,quantidade,numCidadao)==-1)
                        printf("Produto %c esgotado.",tipoConsumo);
                    if(consumo(p,tipoConsumo,quantidade,numCidadao)==1)
                        printf("Venda autorizada.\n");
                }
                else
                    printf("Dados invalidos.\n");
            }
        }
    }
}
//************************************************************************

void registaSaidaPavilhao(pavilhao p, char * linha){
    int numCidadao;
    char l;
    cliente c;
    int perm;
    sscanf(linha,"%c %d",&l,&numCidadao);
    c = saiPavilhao(p, numCidadao, &perm);
    if (perm == 0) {
        printf("Saida nao autorizada.\n");
    }else if (perm == 1){
        printf("Saida autorizada, valor a pagar %.2f euros.\n",contaCliente(c));
    }else{
        printf("Pessoa nao esta no pavilhao\n");
    }
}
//************************************************************************

void interpretador(pavilhao c){
    char linha[25], cmd;
    fgets(linha,20,stdin);
    cmd = toupper(linha[0]);
    while (cmd!='X'){
        /* Tratar comando */
        switch (cmd){
            case 'E': registaEntrada(c,linha);break;
            case 'F': entradaFila(c, linha);break;
            case 'L': OPENTHEGATES(c,linha); break;
            case 'T': pessoaTrampolins(c,linha); break;
            case 'S': saiTrampolin(c, linha);break;
            case 'V': registaCompra(c, linha);break;
            case 'Q': registaSaidaPavilhao(c, linha);break;
            case 'C': caixaPavilhao(c);break;
            default: printf("Comando invalido.\n");break;
        }
        fgets(linha,20,stdin);
        cmd = toupper(linha[0]);
    }
    printf("Caixa: %.2f euros.\n", caixaPavilhao(c));
    printf("Stock cafe: %d.\n",stockCafe(c));
    printf("Stock sumo: %d.\n",stockSumo(c));
    printf("Stock bolo: %d.\n",stockBolo(c));
}

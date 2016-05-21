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
        printf("Abertura Pavilhao.\n");
        interpretador(fct);
        destroiPavilhao(fct);
    }
    return 0;
}

void registaEntrada(pavilhao c, char * linha){
    char nome[50] , l;
    int numCidadao, numContribuinte;
    sscanf(linha,"%c %d %d %s",&l,&numCidadao,&numContribuinte, nome);
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
    sscanf(linha,"%d",&numCidadao);
    
    if((existePavilhao(c, numCidadao))!=1)
        printf("Pessoa nao esta no pavilhao.\n");
    else{
        entraFilaTrampolins(c, numCidadao);
        printf("Entrada autorizada.\n");
    }
    
}

//************************************************************************

void entraTrampolinsP(pavilhao c){
    
    
    
}

void pessoaTrampolins(pavilhao p , char * linha){
    int nTrampolin;
    char * nome;
    int perm;
    sscanf(linha,"%d",&nTrampolin);
    perm = pessoaTrampolin(p, nome, nTrampolin);
    if (perm == 0) {
        printf("Trampolim inexistente.");
    }else if (perm == 1){
        printf("Trampolim vazio.");
    }else{
        printf("Pessoa %s esta no trampolim.",nome);
    }
}
//************************************************************************
void saiTrampolin(pavilhao p, char * linha){
    int numCidadao;
    int hora;
    int minutos;
    sscanf(linha, "%d %d:%d",&numCidadao,&hora,&minutos);
    minutos += hora*60;
    if (minutos <= mEntrada(clienteEmPavilhao(p,numCidadao))) {
        printf("Saida trampolim nao autorizada.");
    }else if (existePavilhao(p, numCidadao)){
        saiTrampolins(p, minutos, numCidadao);
        printf("Saida trampolim autorizada.");
    } else {
        printf("Pessoa não esta no pavilhao.");
    }
}
//************************************************************************


//************************************************************************
void registaSaidaPavilhao(pavilhao p, char * linha){
    int numCidadao;
    cliente c;
    int perm;
    sscanf(linha,"%d",&numCidadao);
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

void interpretador(pavilhao p){
    char linha[25], cmd;
    fgets(linha,20,stdin);
    cmd = toupper(linha[0]);
    while (cmd!='X'){
        /* Tratar comando */
        switch (cmd){
            case 'E': registaEntrada(p,linha);break;
            case 'F': entradaFila(p, linha);break;
            case 'L': entraTrampolinsP(p); break;
            case 'T': ; break;
            case 'S': ;break;
            case 'V': ;break;
            case 'Q': ;break;
            case 'C': ;break;
            default: printf("Comando invalido.\n");break;
        }
        fgets(linha,20,stdin);
        cmd = toupper(linha[0]);
    }
    fechaPavilhao(p);
    printf("Caixa: %.2f euros.\n", caixaPavilhao(p));
    printf("Stock cafÈ: %d.\n",stockCafe(p));
    printf("Stock sumo: %d.\n",stockSumo(p));
    printf("Stock bolo: %d.\n",stockBolo(p));
    
}

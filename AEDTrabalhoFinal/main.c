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
    char * nome;
    int numCidadao, numContribuinte;
    sscanf(linha,"%d %d %s",&numCidadao,&numContribuinte,nome);
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


//************************************************************************
//************************************************************************
//************************************************************************
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
            case 'L': entraTrampolinsP(c); break;
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
    printf("Caixa: %.2f euros.\n", caixaPavilhao(c));
    printf("Stock cafÈ: %d.\n",stockCafe(c));
    printf("Stock sumo: %d.\n",stockSumo(c));
    printf("Stock bolo: %d.\n",stockBolo(c));
    
}

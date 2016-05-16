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
#include "pavilh‹o.h"

#define MAXLINHA 30



void interpretador(pavilhao r);

int main(void){
    char linha[MAXLINHA];
    int capacidade;
    float preco;
    
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
        printf("Abertura lavagem.\n");
        interpretador(fct);
        destroiPavilhao(fct);
    }
    return 0;
}

void registaEntrada(pavilhao c, char * linha){
    char e, lav,mat[9];
    int id;
    sscanf(linha,"%d %d %s",&numCidadao,&numContribuinte,&nome);

        lav = toupper(lav);
        if (lav=='N'||lav=='E') {
            entraPavilhao(numContribuinte, numCidadao, nome);
            printf("Entrada registada.\n");

        else
            printf("Dados invalidos.\n");
    }
}

void registaSaida(pavilhao c){
    if (pessoasPavilhao(c) == 0){
        printf("Sem veiculos.\n");
    }
    else{
        cliente aux = regLavagemPavilhao(c);
        printf("Pessoa com numero contribuinte %d lavou veiculo com matricula %s.\n",contribuinteCliente(aux),matriculaCliente(aux));
        destroiCliente(aux);
    }
}

void dinheiroCaixa(pavilhao c){
    printf("Caixa: %.2f euros.\n", caixaPavilhao(c));
}

void lavVendidos(pavilhao c, char *linha){
    char n, tipo;
    if (sscanf(linha,"%c %c",&n,&tipo)!= 2)
        printf("Dados invalidos.\n");
    else{
        tipo = toupper(tipo);
        if (tipo=='N')
            printf("Lavagem normal: %d\n", lavagemPavilhao(c,tipo));
        else if ( tipo=='E' )
            printf("Lavagem especial: %d\n", lavagemPavilhao(c,tipo));
        else
            printf("Dados invalidos.\n");
    }
}

void interpretador(pavilhao c){
    char linha[25], cmd;
    int numPessoas;
    
    fgets(linha,20,stdin);
    cmd = toupper(linha[0]);
    while (cmd!='X'){
        /* Tratar comando */
        switch (cmd){
            case 'E': registaEntrada(c,linha);break;
            case 'F': entradaFila(c);break;
            case 'L': dinheiroCaixa(c); break;
            case 'N': lavVendidos(c,linha); break;
            case 'F': entradaFila(c);break;
            case 'F': entradaFila(c);break;
            default: printf("Comando invalido.\n");break;
        }
        fgets(linha,20,stdin);
        cmd = toupper(linha[0]);
    }
    printf("Lavagem normal: %d\n", lavagemPavilhao(c,'N'));
    printf("Lavagem especial: %d\n",lavagemPavilhao(c,'E'));
    dinheiroCaixa(c);
    numPessoas = pessoasPavilhao(c);
    if (numPessoas != 0)
        printf("%d veiculos por lavar.\n",numPessoas);
}

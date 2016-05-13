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
#include "maquina.h"

#define MAXLINHA 30

void interpretador(maquina r);

int main(void){
    char linha[MAXLINHA];
    int capacidade;
    float preco;
    
    fgets(linha, MAXLINHA, stdin);
    sscanf(linha,"%d %f",&capacidade,&preco);
    if ((capacidade >0) && (preco >0)){
        maquina  fct= criaMaquina(capacidade, preco);
        printf("Abertura lavagem.\n");
        interpretador(fct);
        destroiMaquina(fct);
    }
    return 0;
}

void registaEntrada(maquina c, char * linha){
    char e, lav,mat[9];
    int id;
    if (sscanf(linha,"%c %d %c %s",&e,&id,&lav,mat)!= 4)
        printf("Dados invalidos.\n");
    else{
        lav = toupper(lav);
        if (lav=='N'||lav=='E') {
            entraMaquina(c, id, mat, lav);
            printf("Entrada registada.\n");
        }
        else
            printf("Dados invalidos.\n");
    }
}

void registaSaida(maquina c){
    if (pessoasMaquina(c) == 0){
        printf("Sem veiculos.\n");
    }
    else{
        cliente aux = regLavagemMaquina(c);
        printf("Pessoa com numero contribuinte %d lavou veiculo com matricula %s.\n",contribuinteCliente(aux),matriculaCliente(aux));
        destroiCliente(aux);
    }
}

void dinheiroCaixa(maquina c){
    printf("Caixa: %.2f euros.\n", caixaMaquina(c));
}

void lavVendidos(maquina c, char *linha){
    char n, tipo;
    if (sscanf(linha,"%c %c",&n,&tipo)!= 2)
        printf("Dados invalidos.\n");
    else{
        tipo = toupper(tipo);
        if (tipo=='N')
            printf("Lavagem normal: %d\n", lavagemMaquina(c,tipo));
        else if ( tipo=='E' )
            printf("Lavagem especial: %d\n", lavagemMaquina(c,tipo));
        else
            printf("Dados invalidos.\n");
    }
}

void interpretador(maquina c){
    char linha[25], cmd;
    int numPessoas;
    
    fgets(linha,20,stdin);
    cmd = toupper(linha[0]);
    while (cmd!='X'){
        /* Tratar comando */
        switch (cmd){
            case 'E': registaEntrada(c,linha);break;
            case 'M': registaSaida(c);break;
            case 'C': dinheiroCaixa(c); break;
            case 'N': lavVendidos(c,linha); break;
            default: printf("Comando invalido.\n");break;
        }
        fgets(linha,20,stdin);
        cmd = toupper(linha[0]);
    }
    printf("Lavagem normal: %d\n", lavagemMaquina(c,'N'));
    printf("Lavagem especial: %d\n",lavagemMaquina(c,'E'));
    dinheiroCaixa(c);
    numPessoas = pessoasMaquina(c);
    if (numPessoas != 0)
        printf("%d veiculos por lavar.\n",numPessoas);
}

/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Baralho
*  Arquivo:              Baralho.h
*
*  Autores: bcr - Bernardo Costa Ruga
*           vmp - Victor Meira Pinto
*           awv - Alexandre Wanick Vieira
*
*  $HA Histórico de evolução:
*     Versão    Autor    Data          Observações
*       1.0       bcr      15/04         Criação do arquivo Baralho.c
*       1.1       vmp      17/04         Implementacao de funcoes 
*
***************************************************************************/


#include "Baralho.h"
#include "LISTA.H"
#include <stdio.h>
#include <stdlib.h>
#define K 13
#define Q 12
#define J 11
#define A 1
#define PAUS 1
#define COPAS 2
#define ESPADAS 3
#define OUROS 4

/***********************************************************************
*
*  $TC Tipo de dados: BAR Descritor de uma carta
*
*  $ED Descrição do tipo
*     Estrutura que indica o naipe da carta, seu valor (podendo ir de A à Rei) e se a carta é uma manilha.
***********************************************************************/
typedef struct tgCarta{
    int naipe;
    int valor;
}BAR_tpCarta;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Descritor de um baralho
*
*  $ED Descrição do tipo
*     O deck de cartas (o baralho em si) é uma lista de cartas e também a um indicativo de quantas cartas o deck possui.
***********************************************************************/
typedef struct tgBaralho{
    LIS_tppLista deck;
    int qtd;
}BAR_tpBaralho;

///***** Dados encapsulados no módulo ******/
//static BAR_tpCarta * pCarta = NULL;

/***********************************************************************
*  Função: BAR Criar Carta
***********************************************************************/

BAR_tpCarta * BAR_CriarCarta ( int Valor, int Naipe ){
    
    BAR_tpCarta * pCarta;
    pCarta = ( BAR_tpCarta * ) malloc( sizeof( BAR_tpCarta ));
    if ( pCarta == NULL){
        return NULL;
    }
    
    pCarta->naipe = Naipe;
    pCarta->valor = Valor;
    
    return pCarta;
}   /* Fim função: BAR Criar Carta */

/***********************************************************************
 *  Função: BAR Destruir Carta
 ***********************************************************************/

void BAR_DestruirCarta ( BAR_tpCarta * pCarta ){
    
    pCarta->naipe = 0;
    pCarta->valor = 0;
    
    free(pCarta);
    
}   /* Fim função: BAR Destruir Carta */

/***********************************************************************
 *  Função: BAR Obter Info
 ***********************************************************************/

BAR_tpCondRet BAR_ObterInfo ( BAR_tpCarta * pCarta, int *pNaipe, int *pValor ){

    //if carta nao existe
        //return BAR_CondRetVazio

    *pNaipe = pCarta->naipe
    *pValor = pCarta->valor

    return BAR_CondRetOk;
}   /* Fim função: BAR Obter Info */

static int BAR_converteValor (int val){
    // 3 2 A K J Q 7 6 5 4
    switch(val){
        case 3:
            val = 16;
            break;

        case 2:
            val = 15;
            break;

        case A:
            val = 14;
            break;

        case J:
            val = 12;
            break;

        case Q:
            val = 11;
            break;

        default:
            break;               
    }
    return val;

}    

/***********************************************************************
 *  Função: BAR Identifica Maior
 ***********************************************************************/

BAR_tpCondRet BAR_IdentificaMaior ( BAR_tpCarta * pCarta1, BAR_tpCarta * pCarta2, BAR_tpCarta * pManilha, int * pMaior ){
    
    //if carta 1 ou 2 nao existe
        //return BAR_CondRetVazio

    int val1 = pCarta1->valor, val2 = pCarta2->valor;
    int nai1 = pCarta1->naipe, nai2 = pCarta2->naipe;
    int val_man = pManilha->valor;

    if(val1 == val_man){
        if(val2 == val_man){
            if(nai1 < nai2)
                *pMaior = 1;
            else
                *pMaior = 2;
            
            return BAR_CondRetOk;
        }
        else{
            *pMaior = 1;
            return BAR_CondRetOk;
        }
    }
    else if(val2 == val_man){
        *pMaior = 2;
        return BAR_CondRetOk;
    }
    else{
        val1 = BAR_converteValor(val1);
        val2 = BAR_converteValor(val2);

        if(val1 > val2)
            *pMaior = 1;
        else if(val1 < val2)
            *pMaior = 2;
        else
            *pMaior = 0;

    }
    
    return BAR_CondRetOk;
}   /* Fim função: BAR Identifica Maior */

/***********************************************************************
 *  Função: BAR Criar Baralho
 ***********************************************************************/

BAR_tpBaralho * BAR_CriarBaralho ( void ){
    
    int i, k;
    int Naipe = 0;
    BAR_tpCarta * pCarta;
    BAR_tpBaralho * pBaralho;
    pBaralho = ( BAR_tpBaralho * ) malloc( sizeof( BAR_tpBaralho ));
    if ( pBaralho == NULL ){
        return NULL;
    }
    
    pBaralho->deck = LIS_CriarLista( BAR_DestruirCarta (BAR_tpCarta *));
    if ( pBaralho->deck == NULL ){
        return NULL;
    }
    for( i=0; i<4; i++){
        switch (i) {
            case 0:
                Naipe = PAUS;
            case 1:
                Naipe = COPAS;
            case 2:
                Naipe = OUROS;
            case 3:
                Naipe = ESPADAS;
        }
        for( k=0; k<10; k++){
            switch (k){
                case 0:
                    pCarta = BAR_CriarCarta ( A, Naipe );
                case 7:
                    pCarta = BAR_CriarCarta ( J, Naipe );
                case 8:
                    pCarta = BAR_CriarCarta ( Q, Naipe );
                case 9:
                    pCarta = BAR_CriarCarta ( K,  Naipe );
                default:
                    pCarta = BAR_CriarCarta ( k+1, Naipe );
            }
            LIS_InserirElementoApos( pBaralho->deck, pCarta );
        }
    }
    
    pBaralho->qtd = 40;
    
    return pBaralho;
}   /* Fim função: BAR Criar Baralho */

/***********************************************************************
 *  Função: BAR Destruir Baralho
 ***********************************************************************/

void BAR_DestruirBaralho ( BAR_tpBaralho * pBaralho ){
    
    LIS_DestruirLista( pBaralho->deck ); 
    free(pBaralho);
    
}   /* Fim função: BAR Destruir Baralho */


static int BAR_RetornaNumAleatorio(int max){
    srand((unsigned) time(&t));
    return rand()%max
}

/***********************************************************************
 *  Função: BAR Embaralhar
 ***********************************************************************/

BAR_tpCondRet BAR_Embaralhar ( BAR_tpBaralho * pBaralho ){

    int num_total = 40;
    int prox_pos;
    int pos_atual = 0;
    BAR_tpCarta *pCarta;
    int condret;

    BAR_tpBaralho * pB_embaralhado;

    BAR_CriarBaralho(pB_embaralhado);

    pCarta = BAR_CriarCarta();


    // if baralho vazio
        // return BAR_CondRetVazio;

    for (i=0;i<40;i++){

        IrInicioLista(pBaralho->deck);

        //calcula prox pos a retirar do baralho ordenado
        prox_pos = BAR_RetornaNumAleatorio(40-i);

        //avanca ate a prox pos
        condret = LIS_AvancarElementoCorrente(pBaralho->deck, prox_pos);
        pCarta = LIS_ObterValor(pBaralho->deck);

        //deleta no baralho recebido
        condret = LIS_ExcluirElemento(pBaralho->deck);

        //insere antes na lista
        condret = LIS_InserirElementoApos(pB_embaralhado->deck, pCarta);

    }

    pBaralho = b_embaralhado;
    
    return BAR_CondRetOk;
}   /* Fim função: BAR Embaralhar */

/***********************************************************************
 *  Função: BAR Puxar Carta
 ***********************************************************************/

BAR_tpCondRet BAR_PuxarCarta ( BAR_tpBaralho * pBaralho, BAR_tpCarta *pCarta ){

    int condret;
    //if baralho nao existe
        // return BAR_CondRet LALALALA


    IrInicioLista(pBaralho->deck);
    pCarta = LIS_ObterValor(pBaralho->deck);
    condret = LIS_ExcluirElemento(pBaralho->deck);
    pBaralho->qtd--;

    return BAR_CondRetOk;
}   /* Fim função: BAR Puxar Carta */

/***********************************************************************
 *  Função: BAR Obter Número de Cartas
 ***********************************************************************/

BAR_tpCondRet BAR_ObterNumerodeCartas ( BAR_tpBaralho * pBaralho , int *pQtd){

    //if baralho nao existe
        // return BAR_CondRet LALALALA

    *pQtd = pBaralho->qtd;

    return BAR_CondRetOk;
}   /* Fim função: BAR Obter Número de Cartas */
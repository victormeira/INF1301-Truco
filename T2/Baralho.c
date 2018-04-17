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
#define OUROS 3
#define ESPADAS 4

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
    int manilha;
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
    pCarta->manilha = 0;
    
    return pCarta;
}   /* Fim função: BAR Criar Carta */

/***********************************************************************
 *  Função: BAR Destruir Carta
 ***********************************************************************/

void BAR_DestruirCarta ( BAR_tpCarta * pCarta ){
    
    pCarta->naipe = 0;
    pCarta->valor = 0;
    pCarta->manilha = 0;
    
    free(pCarta);
    
}   /* Fim função: BAR Destruir Carta */

/***********************************************************************
 *  Função: BAR Obter Info
 ***********************************************************************/

BAR_tpCondRet BAR_ObterInfo ( BAR_tpCarta * pCarta ){
    return BAR_CondRetOk;
}   /* Fim função: BAR Obter Info */

/***********************************************************************
 *  Função: BAR Identifica Maior
 ***********************************************************************/

BAR_tpCondRet BAR_IdentificaMaior ( BAR_tpCarta * pCarta1, BAR_tpCarta * pCarta2 ){
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
    
    pBaralho->deck = ( LIS_tppLista ) malloc( sizeof( BAR_tpCarta ));
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
 *  Função: BAR Destruir Carta
 ***********************************************************************/

void BAR_DestruirBaralho ( BAR_tpBaralho * pBaralho ){
    
//    int i;
    
//    for ( i=0; i<40; i++){
//        BAR_DestruirCarta( pBaralho->deck );
//    }
    
    LIS_DestruirLista( pBaralho->deck );
    
    pBaralho->qtd = 0;
    
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

    BAR_tpBaralho * b_embaralhado;

    BAR_CriarBaralho(b_embaralhado);

    // if baralho vazio
        // return BAR_CondRetVazio;

    for (i=0;i<40;i++){
        pos_atual = 0;
        //vai pro comeco da lista
        prox_pos = BAR_RetornaNumAleatorio(40-i);

        while(pos_atual != prox_pos){
            //anda mais um na lista
            //deleta no baralho recebido
            pos_atual++;
        }
        //insere antes na lista
    }

    pBaralho = b_embaralhado;
    
    return BAR_CondRetOk;
}   /* Fim função: BAR Embaralhar */

/***********************************************************************
 *  Função: BAR Puxar Carta
 ***********************************************************************/

BAR_tpCondRet BAR_PuxarCarta ( BAR_tpBaralho * pBaralho ){
    return BAR_CondRetOk;
}   /* Fim função: BAR Puxar Carta */

/***********************************************************************
 *  Função: BAR Obter Número de Cartas
 ***********************************************************************/

BAR_tpCondRet BAR_ObterNumerodeCartas ( BAR_tpBaralho * pBaralho ){
    return BAR_CondRetOk;
}   /* Fim função: BAR Obter Número de Cartas */
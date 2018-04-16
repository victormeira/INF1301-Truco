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
#include <stdio.h>
#define K 13
#define Q 12
#define J 11
#define A 1

/***********************************************************************
*
*  $TC Tipo de dados: BAR Descritor de uma carta
*
*  $ED Descrição do tipo
*     Estrutura que indica o naipe da carta, seu valor (podendo ir de A à Rei) e se a carta é uma manilha.
***********************************************************************/
typedef struct Carta{
    int naipe;
    int valor;
    int manilha;
}carta;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Descritor de um baralho
*
*  $ED Descrição do tipo
*     O deck de cartas (o baralho em si) é uma lista de cartas e também a um indicativo de quantas cartas o deck possui.
***********************************************************************/
typedef struct Baralho{
    carta* deck;
    int qtd;
}baralho;

/***********************************************************************
*  Função: BAR Criar Carta
***********************************************************************/

BAR_tpCondRet BAR_CriarCarta ( int Valor ){
    return BAR_CondRetOk;
}   /* Fim função: BAR Criar Carta */

/***********************************************************************
 *  Função: BAR Destruir Carta
 ***********************************************************************/

void BAR_DestruirCarta ( carta Carta ){
}   /* Fim função: BAR Destruir Carta */

/***********************************************************************
 *  Função: BAR Obter Info
 ***********************************************************************/

BAR_tpCondRet BAR_ObterInfo ( carta Carta ){
    return BAR_CondRetOk;
}   /* Fim função: BAR Obter Info */

/***********************************************************************
 *  Função: BAR Identifica Maior
 ***********************************************************************/

BAR_tpCondRet BAR_IdentificaMaior ( carta Carta1, carta Carta2 ){
    return BAR_CondRetOk;
}   /* Fim função: BAR Identifica Maior */

/***********************************************************************
 *  Função: BAR Criar Baralho
 ***********************************************************************/

BAR_tpCondRet BAR_CriarBaralho ( baralho Baralho ){
    return BAR_CondRetOk;
}   /* Fim função: BAR Criar Baralho */

/***********************************************************************
 *  Função: BAR Destruir Carta
 ***********************************************************************/

void BAR_DestruirBaralho ( baralho Baralho ){
}   /* Fim função: BAR Destruir Baralho */

/***********************************************************************
 *  Função: BAR Embaralhar
 ***********************************************************************/

BAR_tpCondRet BAR_Embaralhar ( baralho Baralho ){
    return BAR_CondRetOk;
}   /* Fim função: BAR Embaralhar */

/***********************************************************************
 *  Função: BAR Puxar Carta
 ***********************************************************************/

BAR_tpCondRet BAR_PuxarCarta ( baralho Baralho ){
    return BAR_CondRetOk;
}   /* Fim função: BAR Puxar Carta */

/***********************************************************************
 *  Função: BAR Obter Número de Cartas
 ***********************************************************************/

BAR_tpCondRet BAR_ObterNumerodeCartas ( baralho Baralho ){
    return BAR_CondRetOk;
}   /* Fim função: BAR Obter Número de Cartas */

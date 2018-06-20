/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Baralho
*  Arquivo:              Baralho.c
*
*  Autores: awv - Alexandre Wanick Vieira
*           bcr - Bernardo Costa Ruga
*           vmp - Victor Meira Pinto
*
*  $HA Histórico de evolução:
*     Versão    Autor    Data          Observações
*       1.0       bcr      15/04         Criação do arquivo Baralho.c
*       1.1       vmp      17/04         Implementacao de funções
*       1.2       awv      19/04         Revisão do código
*       1.2       bcr      19/04         Revisão do código
*       1.2       vmp      19/04         Revisão do código
*       1.3       bcr      25/04         Revisão do código
*       1.4       awv      30/04         Revisão do código
*       1.5       vmp      03/05         Revisão do código
*       1.6       bcr      03/05         Revisão do código
*
***************************************************************************/

#define MESA_OWN
#include "LISTA.H"
#include "BARALHO.H"
#include "MESA.H"
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
#undef MESA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: MES Descritor de uma mesa
*
*  $ED Descrição do tipo
*     A mesa é uma lista de cartas e também há um indicativo de quantas
*     cartas há.
*
***********************************************************************/

typedef struct tgMesa {

    LIS_tppLista cartasNaMesa ;
    int qtd ;

} MES_tpMesa ;

/***********************************************************************
 *  Função: MES Criar Mesa
 ***********************************************************************/

MES_tppMesa MES_CriarMesa ( void )
{

}

/***********************************************************************
 *  Função: MES Destruir Mesa
 ***********************************************************************/

void MES_DestruirMesa ( MES_tppMesa pMesa )
{

}

/***********************************************************************
 *  Função: MES Esvaziar Mesa
 ***********************************************************************/

MES_tpCondRet MES_EsvaziarMesa ( MES_tppMesa pMesa )
{

}

/***********************************************************************
 *  Função: MES Jogar Carta
 ***********************************************************************/

MES_tpCondRet MES_JogarCarta ( MES_tppMesa pMesa, MES_tppCarta pCarta )
{

}

/***********************************************************************
 *  Função: MES Obter Carta
 ***********************************************************************/

MES_tpCondRet MES_ObterCarta ( MES_tppCarta pCarta, int *pValor , int *pNaipe )
{

}

/***********************************************************************
 *  Função: MES Identificar Ganhador
 ***********************************************************************/

MES_tpCondRet MES_IdentificarGanhador ( MES_tppMesa pMesa )
{

}

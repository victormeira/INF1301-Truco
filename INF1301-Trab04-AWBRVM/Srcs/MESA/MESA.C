/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Mesa
*  Arquivo:              Mesa.c
*
*  Autores: awv - Alexandre Wanick Vieira
*           bcr - Bernardo Costa Ruga
*           vmp - Victor Meira Pinto
*
*  $HA Histórico de evolução:
*     Versão    Autor    Data          Observações
*       1.0       awv      20/06         Criação do arquivo Mesa.c
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
#define MAX_JOGADORES 6
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

    BAR_tppCarta vtCartasNaMesa[ MAX_JOGADORES ] ;
    BAR_tppCarta pCartaManilha ;
    int proxAJogar ;

} MES_tpMesa ;

/***** Protótipos das variáveis encapuladas no módulo *****/

static int nJogadores = MAX_JOGADORES ;

/***** Protótipos das funções encapuladas no módulo *****/

static MES_tpCondRet MES_DefinirManilha ( MES_tppMesa pMesa, BAR_tpCarta * cartaManilha ) ;

/***********************************************************************
 *  Função: MES Criar Mesa
 ***********************************************************************/

MES_tppMesa MES_CriarMesa ( int numJogadores )
{
    MES_tpMesa * pMesa ;
    pMesa = ( MES_tpMesa * ) malloc( sizeof( MES_tpMesa )) ;

    if ( pMesa == NULL )
    {
        return NULL ;
    } /* if */

    if ( numJogadores != 2 && numJogadores != 4 && numJogadores != 6 )
    {
        //TODO: Tratar se o Num de Jogadores nao for 2,4,6
        return NULL ;
    }

    nJogadores = numJogadores ;
    pMesa->proxAJogar = 0 ;

    // defining a Manilha so it isn't NULL
    pMesa->cartaManilha = BAR_CriarCarta( A, OUROS ) ;
    
    return pMesa ;
    /* Fim função: MES Criar Mesa */
}

/***********************************************************************
 *  Função: MES Definir Manilha
 ***********************************************************************/

MES_tpCondRet MES_DefinirManilha ( MES_tppMesa pMesa, BAR_tpCarta * cartaManilha )
{
    int *mValor, *mNaipe;

    if ( cartaManilha != NULL )
    {
        //TODO: Tratar CondRet do ObterInfo
        BAR_ObterInfo( cartaManilha , mValor , mNaipe ) ;

        if ( mValor != NULL && mNaipe != NULL )
        {
            pMesa->cartaManilha = BAR_CriarCarta( mValor , mNaipe ) ;
            BAR_DestruirCarta( cartaManilha ) ;
        }
        else
        {
            //TODO: Tratar se deu M no ObterInfo
            return MES_CondRetCartaNaoExiste ;
        }
    }
    else
    {
        return MES_CondRetCartaNaoExiste ;
    }

    return MES_CondRetOk ;
    /* Fim função: MES Definir Manilha */
}

/***********************************************************************
 *  Função: MES Destruir Mesa
 ***********************************************************************/

void MES_DestruirMesa ( MES_tppMesa pMesa )
{
    BAR_DestruirCarta( pMesa->pCartaManilha ) ;

    free( pMesa ) ;
    /* Fim função: MES Destruir Mesa */
}

/***********************************************************************
 *  Função: MES Esvaziar Mesa
 ***********************************************************************/

MES_tpCondRet MES_EsvaziarMesa ( MES_tppMesa pMesa )
{
    //TODO: Implement Esvaziar Mesa - Precisa mesmo??
    int i ;

    for ( i = 0 ; i < nJogadores ; i++ )
    {
        BAR_DestruirCarta( pMesa->vtCartasNaMesa[ i ] ) ;

        pMesa->vtCartasNaMesa[ i ] = NULL ;
    }
    /* Fim função: MES Esvaziar Mesa */
}

/***********************************************************************
 *  Função: MES Jogar Carta
 ***********************************************************************/

MES_tpCondRet MES_JogarCarta ( MES_tppMesa pMesa, MES_tppCarta pCarta, int jogadorId )
{
    int * mValor;
    int * mNaipe;

    if ( pCarta == NULL )
    {
        return MES_CondRetCartaNaoExiste ;
    }

    if ( pMesa == NULL )
    {
        return MES_CondRetMesaNaoExiste ;
    }

    if ( jogadorId - 1 != pMesa->proxAJogar )
    {
        //TODO: Trata o erro do prox a jogar nao é o jogador passado
        return MES_CondRetJogadorNaoExiste ;
    }

    //TODO: Tratar CondRet do ObterInfo
    BAR_ObterInfo( pCarta , mValor , mNaipe ) ;

    if ( mValor == NULL || mNaipe == NULL )
    {
        //TODO: caso ObterInfo deu M
        return MES_CondRetCartaNaoExiste ;
    }

    pMesa->vtCartasNaMesa[ pMesa->proxAJogar ] = BAR_CriarCarta( * mValor , * mNaipe ) ;

    pMesa->proxAJogar = ( pMesa->proxAJogar + 1 ) % nJogadores ;

    return MES_CondRetOk ;
    /* Fim função: MES Jogar Carta */
}

/***********************************************************************
 *  Função: MES Obter Carta
 ***********************************************************************/

MES_tpCondRet MES_ObterCarta ( int jogadorId , int *pValor ,
                                int *pNaipe ) ;
{
    if(jogadorId < 1 || jogadorId > nJogadores){
        return MES_CondRetJogadorNaoExiste;
    }

    BAR_ObterInfo(pMesa->vtCartasNaMesa[jogadorId-1], pValor, pNaipe);

    return MES_CondRetOk;
}

/***********************************************************************
 *  Função: MES Identificar Ganhador
 ***********************************************************************/

MES_tpCondRet MES_IdentificarGanhador ( MES_tppMesa pMesa )
{
    
}

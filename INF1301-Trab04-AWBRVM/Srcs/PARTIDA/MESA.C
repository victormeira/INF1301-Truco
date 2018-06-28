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
        return NULL ;
    } /* if */

    nJogadores = numJogadores ;
    pMesa->proxAJogar = 0 ;
    pMesa->pCartaManilha = NULL ;
    
    return pMesa ;
    /* Fim função: MES Criar Mesa */
}

/***********************************************************************
 *  Função: MES Definir Manilha
 ***********************************************************************/

MES_tpCondRet MES_DefinirManilha ( MES_tppMesa pMesa, BAR_tppCarta cartaManilha )
{
    int mValor ;
    int mNaipe ;

    if ( cartaManilha != NULL )
    {
        if ( BAR_ObterInfo( cartaManilha , &mValor , &mNaipe ) == BAR_CondRetCartaNaoExiste )
        {
            return MES_CondRetCartaNaoExiste ;
        } /* if */

        if ( mValor >= A && mValor <= 6 )
        {
            mValor++ ;
        }
        else if ( mValor == 7 )
        {
            mValor = Q ;
        }
        else if ( mValor == Q )
        {
            mValor = J ;
        }
        else if ( mValor == J )
        {
            mValor = K ;
        }
        else if ( mValor == K )
        {
            mValor = A ;
        }
        else
        {
            return MES_CondRetCartaNaoExiste ;
        } /* if */

        pMesa->pCartaManilha = BAR_CriarCarta( mValor , mNaipe ) ;
    }
    else
    {
        return MES_CondRetCartaNaoExiste ;
    } /* if */

    return MES_CondRetOk ;
    /* Fim função: MES Definir Manilha */
}

/***********************************************************************
 *  Função: MES Destruir Mesa
 ***********************************************************************/

void MES_DestruirMesa ( MES_tppMesa pMesa )
{
    free( pMesa ) ;
    /* Fim função: MES Destruir Mesa */
}

/***********************************************************************
 *  Função: MES Esvaziar Mesa
 ***********************************************************************/

MES_tpCondRet MES_EsvaziarMesa ( MES_tppMesa pMesa )
{
    int i ;

    static int primeiroDaRodada = 0 ;

    if ( pMesa == NULL )
    {
        return MES_CondRetMesaNaoExiste ;
    } /* if */

    BAR_DestruirCarta( pMesa->pCartaManilha ) ;

    for ( i = 0 ; i < nJogadores ; i++ )
    {
        BAR_DestruirCarta( pMesa->vtCartasNaMesa[ i ] ) ;
        pMesa->vtCartasNaMesa[ i ] = NULL ;
    }

    primeiroDaRodada = ( primeiroDaRodada + 1 ) % nJogadores ;
    pMesa->proxAJogar = primeiroDaRodada ;

    return MES_CondRetOk ;
    /* Fim função: MES Esvaziar Mesa */
}

/***********************************************************************
 *  Função: MES Jogar Carta
 ***********************************************************************/

MES_tpCondRet MES_JogarCarta ( MES_tppMesa pMesa, MES_tppCarta pCarta, int jogadorId )
{
    int mValor ;
    int mNaipe ;

    if ( pCarta == NULL )
    {
        return MES_CondRetCartaNaoExiste ;
    } /* if */

    if ( pMesa == NULL )
    {
        return MES_CondRetMesaNaoExiste ;
    } /* if */

    if ( jogadorId - 1 != pMesa->proxAJogar )
    {
        return MES_CondRetJogadorNaoExiste ;
    } /* if */

    if ( BAR_ObterInfo( pCarta , &mValor , &mNaipe ) == BAR_CondRetCartaNaoExiste )
    {
        return MES_CondRetCartaNaoExiste ;
    } /* if */

    pMesa->vtCartasNaMesa[ pMesa->proxAJogar ] = BAR_CriarCarta( mValor , mNaipe ) ;

    pMesa->proxAJogar = ( pMesa->proxAJogar + 1 ) % nJogadores ;

    return MES_CondRetOk ;
    /* Fim função: MES Jogar Carta */
}

/***********************************************************************
 *  Função: MES Obter Carta
 ***********************************************************************/

MES_tpCondRet MES_ObterCarta ( MES_tppMesa pMesa, int jogadorId , int * pValor , int * pNaipe )
{
    if ( jogadorId < 1 || jogadorId > nJogadores )
    {
        return MES_CondRetJogadorNaoExiste;
    } /* if */

    if ( BAR_ObterInfo( pMesa->vtCartasNaMesa[ jogadorId - 1 ] , pValor , pNaipe ) == BAR_CondRetCartaNaoExiste )
    {
        return MES_CondRetCartaNaoExiste ;
    } /* if */

    return MES_CondRetOk ;
    /* Fim função: MES Obter Carta */
}

/***********************************************************************
 *  Função: MES Identificar Ganhador
 ***********************************************************************/

MES_tpCondRet MES_IdentificarGanhador ( MES_tppMesa pMesa , int * timeGanhador )
{
    int maiorCartaTime1 ;
    int maiorCartaTime2 ;
    int maiorCarta ;
    int i ;

    if ( pMesa == NULL )
    {
        return MES_CondRetMesaNaoExiste ;
    } /* if */

    maiorCartaTime1 = 0 ;
    maiorCartaTime2 = 1 ; 

    //compara 0 com 2, depois melhor com 4 e o mesmo pro segundo time
    for ( i = 1 ;  i < nJogadores / 2 ; i++ )
    {
        if ( BAR_IdentificaMaior( pMesa->vtCartasNaMesa[ maiorCartaTime1 ] , pMesa->vtCartasNaMesa[ 2 * i ] , pMesa->pCartaManilha , &maiorCarta ) == BAR_CondRetCartaNaoExiste )
        {
            return MES_CondRetCartaNaoExiste ;
        } /* if */

        if ( maiorCarta == 2 )
        {
            maiorCartaTime1 = 2 * i ;
        } /* if */

        if ( BAR_IdentificaMaior( pMesa->vtCartasNaMesa[ maiorCartaTime2 ] , pMesa->vtCartasNaMesa[ 2 * i + 1 ] , pMesa->pCartaManilha , &maiorCarta ) == BAR_CondRetCartaNaoExiste )
        {
            return MES_CondRetCartaNaoExiste ;
        } /* if */

        if ( maiorCarta == 2 )
        {
            maiorCartaTime2 = 2 * i + 1 ;
        } /* if */
    }

    if ( BAR_IdentificaMaior ( pMesa->vtCartasNaMesa[ maiorCartaTime1 ] , pMesa->vtCartasNaMesa[ maiorCartaTime2 ] , pMesa->pCartaManilha , &maiorCarta ) == BAR_CondRetCartaNaoExiste )
    {
        return MES_CondRetCartaNaoExiste ;
    } /* if */

    * timeGanhador = maiorCarta ;

    return MES_CondRetOk ;
    /* Fim função: MES Identificar Ganhador */
}

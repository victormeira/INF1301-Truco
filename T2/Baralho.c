/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Baralho
*  Arquivo:              Baralho.h
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

typedef struct tgCarta {

    int naipe ;
    int valor ;

} BAR_tpCarta ;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Descritor de um baralho
*
*  $ED Descrição do tipo
*     O deck de cartas (o baralho em si) é uma lista de cartas e também a um indicativo de quantas cartas o deck possui.
***********************************************************************/

typedef struct tgBaralho {

    LIS_tppLista deck ;
    int qtd ;

} BAR_tpBaralho ;

///***** Dados encapsulados no módulo ******/
//static BAR_tpCarta * pCarta = NULL ;

/***********************************************************************
*  Função: BAR Criar Carta
***********************************************************************/

BAR_tpCarta * BAR_CriarCarta ( int Valor, int Naipe )
{
    
    BAR_tpCarta * pCarta ;
    pCarta = ( BAR_tpCarta * ) malloc( sizeof( BAR_tpCarta )) ;
    if ( pCarta == NULL )
    { /* AE: Carta não existe. */
        return NULL ;
    } /* if */
    
    pCarta->naipe = Naipe ;
    pCarta->valor = Valor ;
    
    return pCarta ;
}   /* Fim função: BAR Criar Carta */

/***********************************************************************
 *  Função: BAR Destruir Carta
 ***********************************************************************/

void BAR_DestruirCarta ( BAR_tpCarta * pCarta )
{

    if ( pCarta == NULL )
    { /* AE:Carta não existe. */
        return BAR_CondRetCartaNaoExiste ;
    }
    
    free( pCarta ) ;
    
}   /* Fim função: BAR Destruir Carta */

/***********************************************************************
 *  Função: BAR Obter Info
 ***********************************************************************/

BAR_tpCondRet BAR_ObterInfo ( BAR_tpCarta * pCarta, int * pNaipe, int * pValor )
{

    if ( pCarta == NULL )
    { /* AE:Carta não existe. */
        return BAR_CondRetCartaNaoExiste ;
    }

    * pNaipe = pCarta->naipe
    * pValor = pCarta->valor

    return BAR_CondRetOk ;
}   /* Fim função: BAR Obter Info */

static int BAR_converteValor ( int val )
{
    // 3 2 A K J Q 7 6 5 4
    switch ( val )
    {    /* AE: Compara o valor da carta com valores de ordem diferente do truco - 3, 2, A, J e Q. */
        case 3:
            val = 16 ;
            break ;
        case 2:
            val = 15 ;
            break ;
        case A:
            val = 14 ;
            break ;
        case J:
            val = 12 ;
            break ;
        case Q:
            val = 11 ;
            break ;
        default:
            val = 0 ;
            break ;               
    } /* switch */
    /* AS: O valor de ordem diferente se converte em um valor de facil comparação. */ 
    return val ;

}    

/***********************************************************************
 *  Função: BAR Identifica Maior
 ***********************************************************************/

BAR_tpCondRet BAR_IdentificaMaior ( BAR_tpCarta * pCarta1, BAR_tpCarta * pCarta2, BAR_tpCarta * pManilha, int * pMaiorCarta )
{
    
    if ( pCarta1 == NULL )
    { /* AE:Carta não existe. */
        return BAR_CondRetCartaNaoExiste ;
    }
    if ( pCarta2 == NULL )
    { /* AE:Carta não existe. */
        return BAR_CondRetCartaNaoExiste ;
    }
    if ( pManilha == NULL )
    { /* AE:Carta não existe. */
        return BAR_CondRetCartaNaoExiste ;
    }

    int ValorCarta1 = pCarta1->valor, ValorCarta2 = pCarta2->valor ;
    int NaipeCarta1 = pCarta1->naipe, NaipeCarta2 = pCarta2->naipe ;
    int ValorManilha = pManilha->valor ;

    if ( ValorCarta1 == ValorManilha )
    { /*AE: Compara se o valor da Carta 1 é igual ao valor da manilha. */
        if ( ValorCarta2 == ValorManilha )
        { /*AE: Compara se o valor da Carta 2 é igual ao valor da manilha. */
            if ( NaipeCarta1 < NaipeCarta2 )
            { /*AE: Compara se o valor do naipe da Carta 1 é menor que o da Carta 2. */
                * pMaiorCarta = 1 ;
            }
            else
            {
                * pMaiorCarta = 2 ;
            } /* if */
            /* AS: Comparação para descobrir maior carta completa. */ 
            
            return BAR_CondRetOk ;
        }
        else
        {
            * pMaiorCarta = 1 ;
            return BAR_CondRetOk ;
        } /* if */
        /* AS: Comparação para descobrir maior carta completa. */
    }
    else if ( ValorCarta2 == ValorManilha )
    {
        * pMaiorCarta = 2 ;
        return BAR_CondRetOk ;
    }
    else
    {
        ValorCarta1 = BAR_converteValor( ValorCarta1 ) ;
        ValorCarta2 = BAR_converteValor( ValorCarta2 ) ;

        if ( ValorCarta1 > ValorCarta2 )
        { /* AE: Compara se o valor da Carta 1 é maior que o valor da Carta 2. */
            * pMaiorCarta = 1 ;
        }
        else if ( ValorCarta1 < ValorCarta2 )
        {
            * pMaiorCarta = 2 ;
        }
        else
        {
            * pMaiorCarta = 0 ;
        } /* if */
        /* AS: Comparação para descobrir maior carta completa. */

    } /* if */
    /* AS: Comparação para descobrir maior carta completa. */
    
    return BAR_CondRetOk ;
}   /* Fim função: BAR Identifica Maior */

/***********************************************************************
 *  Função: BAR Criar Baralho
 ***********************************************************************/

BAR_tpBaralho * BAR_CriarBaralho ( void )
{
    
    int i, k ;
    int Naipe ;
    int NumeroTotaldeCartas = 40 ;
    int NumeroDeNaipes = 4 ;

    BAR_tpCarta * pCarta ;
    BAR_tpBaralho * pBaralho ;

    pBaralho = ( BAR_tpBaralho * ) malloc( sizeof( BAR_tpBaralho )) ;

    if ( pBaralho == NULL )
    { /* AE: Baralho não existe. */
        return BAR_CondRetBaralhoNaoExiste ;
    } /* if */
    
    pBaralho->deck = LIS_CriarLista( BAR_DestruirCarta (BAR_tpCarta *)) ;

    if ( pBaralho->deck == NULL )
    { /* AE: Lista de cartas vazia. */
        return BAR_CondRetBaralhoVazio ;
    } /* if */

    for( i = 0 ; i < NumeroDeNaipes ; i++ )
    {
        switch ( i ) 
        {
            case 0:
                Naipe = PAUS ;
                break ;
            case 1:
                Naipe = COPAS ;
                break ;
            case 2:
                Naipe = OUROS ;
                break ;
            case 3:
                Naipe = ESPADAS ;
                break ;
            default:
                Naipe = -1 ;
                break ;
        } /* for */

        for( k = 0 ; k < ( NumeroTotaldeCartas / NumeroDeNaipes ) ; k++ )
        {
            switch ( k )
            {
                case 0:
                    pCarta = BAR_CriarCarta ( A, Naipe ) ;
                    break ;
                case 7:
                    pCarta = BAR_CriarCarta ( J, Naipe ) ;
                    break ;
                case 8:
                    pCarta = BAR_CriarCarta ( Q, Naipe ) ;
                    break ;
                case 9:
                    pCarta = BAR_CriarCarta ( K,  Naipe ) ;
                    break ;
                default:
                    pCarta = BAR_CriarCarta ( k + 1, Naipe ) ;
                    break ;
            } /* switch */

            if ( pCarta == NULL )
            { /* AE:Carta não existe. */
                return BAR_CondRetCartaNaoExiste ;
            }

            LIS_InserirElementoApos( pBaralho->deck, pCarta ) ;
        } /* for */
    }
    
    pBaralho->qtd = NumeroTotaldeCartas ;
    
    return pBaralho ;

}   /* Fim função: BAR Criar Baralho */

/***********************************************************************
 *  Função: BAR Destruir Baralho
 ***********************************************************************/

void BAR_DestruirBaralho ( BAR_tpBaralho * pBaralho )
{

    LIS_DestruirLista( pBaralho->deck ) ; 
    free( pBaralho ) ;
    
}   /* Fim função: BAR Destruir Baralho */


static int BAR_RetornaNumAleatorio ( int max )
{

    srand(( unsigned ) time( &t )) ;
    return rand () %max ;

}   /* Fim função: BAR Retorna Número Aleatório */

/***********************************************************************
 *  Função: BAR Embaralhar
 ***********************************************************************/

BAR_tpCondRet BAR_Embaralhar ( BAR_tpBaralho * pBaralho )
{

    int i ;
    int NumeroTotaldeCartas = 40 ;
    int ProxPos ;
    int CondRetElementoCorrente, CondRetExcluirElemento, CondRetInserirApos ;

    BAR_tpCarta * pCarta ;
    BAR_tpBaralho * pB_embaralhado ;
    BAR_tpBaralho * pB_aux ;

    if ( pBaralho == NULL )
    { /* AE:Baralho não existe. */
        return BAR_CondRetBaralhoNaoExiste ;
    }

    BAR_CriarBaralho( pB_embaralhado ) ;

    if ( pB_embaralhado == NULL )
    { /* AE:Baralho não existe. */
        return BAR_CondRetBaralhoNaoExiste ;
    }

    LIS_EsvaziarLista( pB_embaralhado->deck ) ;

    pB_embaralhado->qtd = 0 ;

    pCarta = BAR_CriarCarta() ;

    if ( pCarta == NULL )
    { /* AE:Carta não existe. */
        return BAR_CondRetCartaNaoExiste ;
    }
    
    for ( i = 0 ; i < NumeroTotaldeCartas ; i++ , pB_embaralhado->qtd++ )
    {

        IrInicioLista( pBaralho->deck ) ;

        //calcula prox pos a retirar do baralho ordenado
        prox_pos = BAR_RetornaNumAleatorio( NumeroTotaldeCartas - i ) ;

        //avanca ate a prox pos
        CondRetElementoCorrente = LIS_AvancarElementoCorrente( pBaralho->deck, ProxPos ) ;
        if ( CondRetElementoCorrente != LIS_CondRetOK )
        { /* AE: Não foi possivel avançar para o proximo elemento do baralho original. */
           return BAR_CondRetBaralhoIncompleto ; //Duvida: O que fazer se uma funcao que retorna condret nao retorna condretOK? 
        }
        pCarta = LIS_ObterValor( pBaralho->deck ) ;

        //deleta no baralho recebido
        CondRetExcluirElemento = LIS_ExcluirElemento( pBaralho->deck ) ;
        if ( CondRetExcluirElemento != LIS_CondRetOK )
        { /* AE: Não foi possivel excluir o elemento corrente do baralho original. */
            return BAR_CondRetCartaNaoExiste ;
        }
        pBaralho->qtd-- ;

        //insere antes na lista
        CondRetInserirApos = LIS_InserirElementoApos( pB_embaralhado->deck, pCarta ) ;
        if ( CondRetInserirApos != LIS_CondRetOK )
        { /* AE: Não foi possivel inserir carta no baralho embaralhado. */
            return BAR_CondRetBaralhoNaoExiste ;
        }

    } /* for */

    pB_aux = pBaralho;
    pBaralho = pB_embaralhado ;

    BAR_DestruirBaralho( pB_aux ) ;
    
    return BAR_CondRetOk ;

}   /* Fim função: BAR Embaralhar */

/***********************************************************************
 *  Função: BAR Puxar Carta
 ***********************************************************************/

BAR_tpCondRet BAR_PuxarCarta ( BAR_tpBaralho * pBaralho, BAR_tpCarta * pCarta )
{

    int CondRetExcluirElemento ;

    if ( pBaralho == NULL )
    { /* AE:Baralho não existe. */
        return BAR_CondRetBaralhoNaoExiste ;
    }

    if ( pCarta == NULL )
    { /* AE:Carta não existe. */
        return BAR_CondRetCartaNaoExiste ;
    }

    IrInicioLista( pBaralho->deck ) ;
    pCarta = LIS_ObterValor( pBaralho->deck ) ;
    CondRetExcluirElemento = LIS_ExcluirElemento( pBaralho->deck ) ;
    if ( CondRetExcluirElemento != LIS_CondRetOK )
    { /* AE: Não foi possivel excluir o elemento corrente do baralho original. */
        return BAR_CondRetCartaNaoExiste ;
    }

    pBaralho->qtd-- ;

    return BAR_CondRetOk ;

}   /* Fim função: BAR Puxar Carta */

/***********************************************************************
 *  Função: BAR Obter Número de Cartas
 ***********************************************************************/

BAR_tpCondRet BAR_ObterNumerodeCartas ( BAR_tpBaralho * pBaralho , int * pQtd)
{

    if ( pBaralho == NULL )
    { /* AE:Baralho não existe. */
        return BAR_CondRetBaralhoNaoExiste ;
    }

    * pQtd = pBaralho->qtd ;

    return BAR_CondRetOk ;

}   /* Fim função: BAR Obter Número de Cartas */

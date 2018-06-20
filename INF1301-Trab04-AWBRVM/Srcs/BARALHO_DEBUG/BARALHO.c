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
*       1.7       bcr      20/06         Revisão do código, adição de contadores
*
***************************************************************************/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define BARALHO_OWN
#include "BARALHO.H"
#include "LISTA.H"
#define K 13
#define Q 12
#define J 11
#define A 1
#define PAUS 1
#define COPAS 2
#define ESPADAS 3
#define OUROS 4
#undef BARALHO_OWN

#ifdef _DEBUG
#include "CONTA.H"
#include "CESPDIN.H"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: BAR Descritor de uma carta
*
*  $ED Descrição do tipo
*     Estrutura que indica o naipe da carta, seu valor 
*     (podendo ir de A à Rei) e se a carta é uma manilha.
*
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
*     O deck de cartas (o baralho em si) é uma lista de cartas e 
*     também a um indicativo de quantas cartas o deck possui.
*
***********************************************************************/

typedef struct tgBaralho {

    LIS_tppLista deck ;
    int qtd ;

} BAR_tpBaralho ;

/***** Protótipos das funções encapuladas no módulo *****/

static int BAR_RetornaNumAleatorio ( int max );

static int BAR_converteValor ( int val );

/***********************************************************************
*  Função: BAR Criar Carta
***********************************************************************/

BAR_tpCarta * BAR_CriarCarta ( int Valor, int Naipe )
{

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_CriarCarta iniciando" ) ;
    #endif

    BAR_tpCarta * pCarta ;
    pCarta = ( BAR_tpCarta * ) malloc( sizeof( BAR_tpCarta )) ;
    if ( pCarta == NULL )
    {
        return NULL ;
    } /* if */

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_CriarCarta memoria alocada" ) ;
    #endif

    pCarta->valor = Valor ;
    pCarta->naipe = Naipe ;

    #ifdef _DEBUG
        CED_DefinirTipoEspaco( pCarta , GRA_TipoEspacoCabeca ) ; 
    #endif  

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_CriarCarta valor e naipes atribuidos" ) ;
    #endif

    return pCarta ;
}   /* Fim função: BAR Criar Carta */

/***********************************************************************
 *  Função: BAR Destruir Carta
 ***********************************************************************/

void BAR_DestruirCarta ( BAR_tpCarta * pCarta )
{
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_DestruirCarta iniciando" ) ;
    #endif

    free( pCarta ) ;

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_DestruirCarta pCarta destruido" ) ;
    #endif
}   /* Fim função: BAR Destruir Carta */

/***********************************************************************
 *  Função: BAR Obter Info
 ***********************************************************************/

BAR_tpCondRet BAR_ObterInfo ( BAR_tpCarta * pCarta, int * pValor, int * pNaipe )
{
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_ObterInfo iniciando" ) ;
    #endif

    if ( pCarta == NULL )
    {
        return BAR_CondRetCartaNaoExiste ;
    } /* if */

    * pNaipe = pCarta->naipe ;
    * pValor = pCarta->valor ;

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_ObterInfo valor e naipe atribuidos" ) ;
    #endif
        
    return BAR_CondRetOk ;
}   /* Fim função: BAR Obter Info */

/***********************************************************************
 *  Função: BAR Identifica Maior
 ***********************************************************************/

BAR_tpCondRet BAR_IdentificaMaior ( BAR_tpCarta * pCarta1, BAR_tpCarta * pCarta2, BAR_tpCarta * pManilha, int * pMaiorCarta )
{
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_IdentificaMaior iniciando" ) ;
    #endif
        
    int ValorCarta1 ;
    int ValorCarta2 ;
    int NaipeCarta1 ;
    int NaipeCarta2 ;
    int ValorManilha ;
    
    if ( pCarta1 == NULL )
    {
        return BAR_CondRetCartaNaoExiste ;
    } /* if */
    if ( pCarta2 == NULL )
    {
        return BAR_CondRetCartaNaoExiste ;
    } /* if */
    if ( pManilha == NULL )
    {
        return BAR_CondRetCartaNaoExiste ;
    } /* if */

    ValorCarta1 = pCarta1->valor ;
    ValorCarta2 = pCarta2->valor ;
    NaipeCarta1 = pCarta1->naipe ;
    NaipeCarta2 = pCarta2->naipe ;
    ValorManilha = pManilha->valor ;

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_IdentificaMaior variaveis de valor e naipes criados" ) ;
    #endif
        
    if ( ValorCarta1 == ValorManilha )
    { /* Compara se o valor da Carta 1 é igual ao valor da manilha. */
        if ( ValorCarta2 == ValorManilha )
        { /* Compara se o valor da Carta 2 é igual ao valor da manilha. */
            if ( NaipeCarta1 < NaipeCarta2 )
            { /* Compara se o valor do naipe da Carta 1 é menor que o da Carta 2. */
                * pMaiorCarta = 1 ;

                #ifdef _DEBUG
                    CNT_CONTAR( "BAR_IdentificaMaior carta 1 eh a manilha de maior naipe" ) ;
                #endif
                    
            }
            else
            {
                * pMaiorCarta = 2 ;

                #ifdef _DEBUG
                    CNT_CONTAR( "BAR_IdentificaMaior carta 2 eh a manilha de maior naipe" ) ;
                #endif
                    
            } /* if */
            return BAR_CondRetOk ;
        }
        else
        {
            * pMaiorCarta = 1 ;

                #ifdef _DEBUG
                    CNT_CONTAR( "BAR_IdentificaMaior carta 1 eh a manilha e carta 2 nao" ) ;
                #endif
                    
            return BAR_CondRetOk ;
        } /* if */
    }
    else if ( ValorCarta2 == ValorManilha )
    {
        * pMaiorCarta = 2 ;

        #ifdef _DEBUG
            CNT_CONTAR( "BAR_IdentificaMaior carta 2 eh a manilha e carta 1 nao" ) ;
        #endif
                    
        return BAR_CondRetOk ;
    }
    else
    {
        ValorCarta1 = BAR_converteValor( ValorCarta1 ) ;
        ValorCarta2 = BAR_converteValor( ValorCarta2 ) ;

        if ( ValorCarta1 > ValorCarta2 )
        { /* Compara se o valor da Carta 1 é maior que o valor da Carta 2. */
            * pMaiorCarta = 1 ;

            #ifdef _DEBUG
                CNT_CONTAR( "BAR_IdentificaMaior carta 1 eh a maior" ) ;
            #endif
                    
        }
        else if ( ValorCarta1 < ValorCarta2 )
        {
            * pMaiorCarta = 2 ;

            #ifdef _DEBUG
                CNT_CONTAR( "BAR_IdentificaMaior carta 2 eh a maior" ) ;
            #endif
                    
        }
        else
        {
            * pMaiorCarta = 0 ;

            #ifdef _DEBUG
                CNT_CONTAR( "BAR_IdentificaMaior deu empate" ) ;
            #endif

        } /* if */
    } /* if */
    
    return BAR_CondRetOk ;
}   /* Fim função: BAR Identifica Maior */

/***********************************************************************
 *  Função: BAR Criar Baralho
 ***********************************************************************/

BAR_tpBaralho * BAR_CriarBaralho ( void )
{
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_CriarBaralho iniciando" ) ;
    #endif
        
    int i, k ;
    int Naipe ;
    int NumeroTotaldeCartas = 40 ;
    int NumeroDeNaipes = 4 ;

    BAR_tpCarta * pCarta ;
    BAR_tpBaralho * pBaralho ;

    pBaralho = ( BAR_tpBaralho * ) malloc( sizeof( BAR_tpBaralho )) ;

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_CriarBaralho novo baralho alocado" ) ;
    #endif


    if ( pBaralho == NULL )
    {
        return NULL ;
    } /* if */
    
    pBaralho->deck = LIS_CriarLista( BAR_DestruirCarta ) ;

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_CriarBaralho novo deck do baralho criado" ) ;
    #endif

    if ( pBaralho->deck == NULL )
    {
        return NULL ;
    } /* if */

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_CriarBaralho vai criar as cartas do novo baralho" ) ;
    #endif

    // Itera pelos naipes
    for( i = 1 ; i <= NumeroDeNaipes ; i++ )
    {
        switch ( i ) 
        {
            case 1:
                Naipe = PAUS ;
                break ;
            case 2:
                Naipe = COPAS ;
                break ;
            case 3:
                Naipe = ESPADAS ;
                break ;
            case 4:
                Naipe = OUROS ;
                break ;
            default:
                Naipe = -1 ;
                break ;
        } /* switch */

        // Itera pelos valores das cartas
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
            {
                return NULL ;
            }

            LIS_InserirElementoApos( pBaralho->deck, pCarta ) ;
        } /* for */
    }
    
    pBaralho->qtd = NumeroTotaldeCartas ;
    
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_CriarBaralho novo baralho finalizado" ) ;
    #endif

    return pBaralho ;

}   /* Fim função: BAR Criar Baralho */


/***********************************************************************
 *  Função: BAR Destruir Baralho
 ***********************************************************************/

void BAR_DestruirBaralho ( BAR_tpBaralho * pBaralho )
{
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_DestruirBaralho iniciando" ) ;
    #endif

    if ( pBaralho->qtd != 0 )
    {
        LIS_DestruirLista( pBaralho->deck ) ;
    } /* if */

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_DestruirBaralho baralho destruido" ) ;
    #endif
    
    free( pBaralho ) ;
    
}   /* Fim função: BAR Destruir Baralho */

/***********************************************************************
 *  Função: BAR Embaralhar
 ***********************************************************************/

BAR_tpCondRet BAR_Embaralhar ( BAR_tpBaralho * pBaralho )
{
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_Embaralhar iniciando" ) ;
    #endif
        

    int i ;
    int NumeroTotaldeCartas = 40 ;
    int ProxPos ;
    int CondRetElementoCorrente, CondRetExcluirElemento, CondRetInserirApos ;

    static char timeFlag = 0 ;

    time_t t;

    BAR_tpCarta * pCarta ;
    BAR_tpCarta * pCartaAux ;
    BAR_tpBaralho * pBaralhoAux ;

    if ( pBaralho == NULL )
    {
        return BAR_CondRetBaralhoNaoExiste ;
    } /* if */

    pBaralhoAux = BAR_CriarBaralho( ) ;
    pCartaAux = BAR_CriarCarta( 0 , 0 ) ;

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_Embaralhar baralho auxiliar criado" ) ;
    #endif        

    if ( pBaralhoAux == NULL )
    {
        return BAR_CondRetBaralhoNaoExiste ;
    } /* if */
 
    // Garante que o seed para a randomização é ativado apenas uma vez
    if ( timeFlag == 0 ) {
        srand( ( unsigned ) time( &t ) ) ;
        timeFlag = 1 ;
    } /* if */

    LIS_EsvaziarLista( pBaralho->deck ) ;

    pBaralho->qtd = 0 ;

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_Embaralhar baralho comecando a embaralhar" ) ;
    #endif        
    
    for ( i = 0 ; i < NumeroTotaldeCartas ; i++ , pBaralho->qtd++ )
    {

        IrInicioLista( pBaralhoAux->deck ) ;

        //calcula prox pos a retirar do baralho ordenado
        ProxPos = BAR_RetornaNumAleatorio( NumeroTotaldeCartas - i ) ;

        //avanca ate a prox pos
        CondRetElementoCorrente = LIS_AvancarElementoCorrente( pBaralhoAux->deck, ProxPos ) ;

        if ( CondRetElementoCorrente != LIS_CondRetOK )
        {
           return BAR_CondRetBaralhoIncompleto ;
        } /* if */

        pCartaAux = ( BAR_tpCarta * ) LIS_ObterValor( pBaralhoAux->deck ) ;

        pCarta = BAR_CriarCarta( pCartaAux->valor, pCartaAux->naipe ) ;

        //deleta no baralho recebido
        CondRetExcluirElemento = LIS_ExcluirElemento( pBaralhoAux->deck ) ;

        if ( CondRetExcluirElemento != LIS_CondRetOK )
        {
            return BAR_CondRetCartaNaoExiste ;
        } /* if */

        pBaralhoAux->qtd-- ;

        //insere antes na lista
        CondRetInserirApos = LIS_InserirElementoApos( pBaralho->deck, pCarta ) ;

        if ( CondRetInserirApos != LIS_CondRetOK )
        {
            return BAR_CondRetBaralhoNaoExiste ;
        } /* if */
    } /* for */

    IrInicioLista ( pBaralho->deck ) ;
    BAR_DestruirBaralho( pBaralhoAux ) ;
    
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_Embaralhar baralho embaralhado" ) ;
    #endif        

    return BAR_CondRetOk ;

}   /* Fim função: BAR Embaralhar */

/***********************************************************************
 *  Função: BAR Puxar Carta
 ***********************************************************************/

BAR_tpCondRet BAR_PuxarCarta ( BAR_tpBaralho * pBaralho, BAR_tpCarta * pCarta )
{
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_PuxarCarta iniciando" ) ;
    #endif
        

    int CondRetExcluirElemento ;

    BAR_tpCarta *pCartaAux ;

    if ( pBaralho == NULL )
    {
        return BAR_CondRetBaralhoNaoExiste ;
    } /* if */

    if ( pCarta == NULL )
    {
        return BAR_CondRetCartaNaoExiste ;
    } /* if */

    if ( pBaralho->qtd == 0 )
    {
        return BAR_CondRetBaralhoVazio ;
    } /* if */

    IrInicioLista( pBaralho->deck ) ;

    pCartaAux = ( BAR_tpCarta * ) LIS_ObterValor( pBaralho->deck ) ;

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_PuxarCarta carta atribuida" ) ;
    #endif      

    pCarta->valor = pCartaAux->valor ;
    pCarta->naipe = pCartaAux->naipe ;

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_PuxarCarta valor e naipe atribuidos" ) ;
    #endif      

    CondRetExcluirElemento = LIS_ExcluirElemento( pBaralho->deck ) ;

    if ( CondRetExcluirElemento != LIS_CondRetOK )
    {
        return BAR_CondRetCartaNaoExiste ;
    } /* if */

    pBaralho->qtd-- ;

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_PuxarCarta carta retirada do baralho" ) ;
    #endif      

    return BAR_CondRetOk ;

}   /* Fim função: BAR Puxar Carta */

/***********************************************************************
 *  Função: BAR Obter Número de Cartas
 ***********************************************************************/

BAR_tpCondRet BAR_ObterNumerodeCartas ( BAR_tpBaralho * pBaralho , int * pQtd)
{
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_ObterNumerodeCartas iniciando" ) ;
    #endif    

    if ( pBaralho == NULL )
    {
        * pQtd = -1 ;

        return BAR_CondRetBaralhoNaoExiste ;
    } /* if */

    * pQtd = pBaralho->qtd ;

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_ObterNumerodeCartas numero de cartas obtido" ) ;
    #endif    

    return BAR_CondRetOk ;

}   /* Fim função: BAR Obter Número de Cartas */

/***********************************************************************
 *  Função: BAR Compara Baralhos
 ***********************************************************************/

BAR_tpCondRet BAR_ComparaBaralhos ( BAR_tpBaralho * pBaralho1 , BAR_tpBaralho * pBaralho2 )
{
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_ComparaBaralhos iniciando" ) ;
    #endif

    int i;

    int qtdDeck1 = pBaralho1->qtd ;
    int qtdDeck2 = pBaralho2->qtd ;

    LIS_tpCondRet CondRet1, CondRet2 ;
    LIS_tppLista primeiroDeck = pBaralho1->deck ;
    LIS_tppLista segundoDeck = pBaralho2->deck ;
    
    BAR_tpCarta *cartaDoBaralho1 ;
    BAR_tpCarta *cartaDoBaralho2 ;
    

    // Se tiver quantidades diferentes de cartas nos baralhos
    if ( qtdDeck1 != qtdDeck2 )
    {
        return BAR_CondRetQuantidadesDiferentes ;
    } /* if */
    
    // Se algum dos Baralhos estiver vazio
    if ( primeiroDeck == NULL || segundoDeck == NULL )
    {
        return BAR_CondRetBaralhoVazio ;
    } /* if */
    
    IrInicioLista( primeiroDeck ) ;
    IrInicioLista( segundoDeck ) ;

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_ComparaBaralhos comecando comparacao" ) ;
    #endif

    // Compara cada carta de ambos dos baralhos
    for (i = 0 ; i < qtdDeck1 ; i++ )
    {   

        cartaDoBaralho1 = ( BAR_tpCarta * ) LIS_ObterValor( primeiroDeck ) ;
        cartaDoBaralho2 = ( BAR_tpCarta * ) LIS_ObterValor( segundoDeck ) ;
        
        if ( ! ( ( cartaDoBaralho1->valor == cartaDoBaralho2->valor ) && ( cartaDoBaralho1->naipe ==  cartaDoBaralho2->naipe ) ) )
        {
            return BAR_CondRetBaralhosDiferentes;
        } /* if */
        
        CondRet1 = LIS_AvancarElementoCorrente( primeiroDeck , 1) ;
        CondRet2 = LIS_AvancarElementoCorrente( segundoDeck , 1) ;
        
        // Caso não consiga andar, Baralhos tem qtds diferentes
        if(CondRet1 != LIS_CondRetOK || CondRet2 != LIS_CondRetOK)
        {
            return BAR_CondRetQuantidadesDiferentes ;
        } /* if */
    } /* for */
    
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_ComparaBaralhos baralhos comparados" ) ;
    #endif

    return BAR_CondRetOk ;
    
}   /* Fim função: BAR Compara Baralhos */

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: BAR  -Retorna Numero Aleatorio
*
*  $ED Descrição da função
*     Retorna um numero do tipo int aleatorio de 0 ao  
*     parametro int max.
*
***********************************************************************/

int BAR_RetornaNumAleatorio ( int max )
{
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_RetornaNumAleatorio iniciando" ) ;
    #endif
        
    return rand () %max ;

}   /* Fim função: BAR Retorna Número Aleatório */


/***********************************************************************
*
*  $FC Função: BAR  -Converte valor
*
*  $ED Descrição da função
*     Retorna o numero equivalente ao valor da carta para facilitar
*     na comparacao.
*
***********************************************************************/

int BAR_converteValor ( int val )
{
    #ifdef _DEBUG
        CNT_CONTAR( "BAR_converteValor iniciando" ) ;
    #endif
        
    // 3 2 A K J Q 7 6 5 4
    // O valor de ordem diferente se converte em um valor de facil comparação. */
    switch ( val )
    {
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
            val = val ;
            break ;               
    } /* switch */

    #ifdef _DEBUG
        CNT_CONTAR( "BAR_converteValor valor comparado" ) ;
    #endif
        
    return val ;

}    /* Fim função: BAR Converter Valor */


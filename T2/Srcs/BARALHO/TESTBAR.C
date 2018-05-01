/***************************************************************************
 *  $MCI Módulo de implementação: TBAR Teste Baralho
 *
 *  Arquivo gerado:              TestBAR.c
 *  Letras identificadoras:      TBAR
 *
 *  Autores:  awv - Alexandre Wanick Vieira
 *            bcr - Bernardo Costa Ruga
 *            vmp - Victor Meira Pinto
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data             Observações
 *     1.0       vmp   19/abr/2018     Início desenvolvimento
 *     1.1       awv   30/abr/2018     Revisão do código
 *
 ***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Baralho.h"


static const char RESET_BARALHO_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_BARALHO_CMD         [ ] = "=criarbaralho"     ;
static const char DESTRUIR_BARALHO_CMD      [ ] = "=destruirbaralho"  ;
static const char CRIAR_CARTA_CMD           [ ] = "=criarcarta"    ;
static const char DESTRUIR_CARTA_CMD        [ ] = "=destruircarta"  ;
static const char OBTER_INFO_CARTA_CMD      [ ] = "=obterinfocarta"  ;
static const char ID_MAIOR_CMD              [ ] = "=idmaior"   ;
static const char EMBARALHAR_CMD            [ ] = "=embaralhar"    ;
static const char PUXAR_CARTA_CMD           [ ] = "=puxarcarta" ;
static const char OBTER_NUM_CMD             [ ] = "=obternum"    ;
static const char COMPARAR_BARALHOS_CMD     [ ] = "=compararbaralhos"    ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_BARALHO  3
#define DIM_VT_CARTA      40
#define DIM_VALOR         100

BAR_tppBaralho   vtBaralhos[ DIM_VT_BARALHO ] ;
BAR_tppCarta     vtCartas[ DIM_VT_CARTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

static void DestruirValor( void * pValor ) ;

static int ValidarInxBaralho( int inxBaralho , int Modo ) ;

static int ValidarInxCarta( int inxCarta , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
 *
 *  $FC Função: TBAR &Testar Baralho
 *
 *  $ED Descrição da função
 *     Podem ser criados até 3 baralhos, identificadas pelos índices 0 a 2
 *
 *     Comandos disponíveis:
 *
 *     =resetteste
 *           - anula o vetor de baralhos. Provoca vazamento de memória
 *     =criarbaralho                 inxBaralho
 *     =destruirbaralho              inxBaralho
 *     =criarcarta                   inxCarta  valorEsperado  naipeEsperado
 *     =destruircarta                inxCarta
 *     =obterinfocarta               inxCarta  valorEsperado naipeEsperado  CondretPonteiro
 *     =idmaior                      inxCarta1  inxCarta2  inxCartaManilha  maiorEsperado  CondretPonteiro
 *     =embaralhar                   inxBaralho  CondretEsperado
 *     =puxarcarta                   inxBaralho  valorEsperado  naipeEsperado  CondretPonteiro
 *     =obternum                     inxBaralho  numEsperado
 *     =compararbaralhos             inxBaralho1  inxBaralho2  CondretPonteiro
 *
 ***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
    
    int inxCarta  = -1 ;
    int inxCarta1 = -1 ;
    int inxCarta2 = -1 ;
    int inxCartaManilha = -1;
    int inxBaralho = -1 ;
    int inxBaralho1 = -1 ;
    int inxBaralho2 = -1 ;
    int numLidos   = -1 ;
    int CondRetEsp = -1 ;
    int valorEsperado = -1 ;
    int naipeEsperado = -1 ;
    int maiorEsperado = -1 ;
    
    int naipeRecebido ;
    int valorRecebido ;
    int maiorRecebido ;
    
    TST_tpCondRet CondRet ;
    
    char   StringDado[  DIM_VALOR ] ;
    BAR_tppCarta pDado = BAR_CriarCarta( 0 , 0 ) ;
    
    int i ;
    
    StringDado[ 0 ] = 0 ;
    
    /* Efetuar reset de teste de baralho */
    
    if ( strcmp( ComandoTeste , RESET_BARALHO_CMD ) == 0 )
    {
        for( i = 0 ; i < DIM_VT_BARALHO ; i++ )
        {
            vtBaralhos[ i ] = NULL ;
        } /* for */

        for( i = 0 ; i < DIM_VT_CARTA ; i++ )
        {
            vtCartas[ i ] = NULL ;
        } /* for */
        
        return TST_CondRetOK ;
        
    } /* fim ativa: Efetuar reset de teste de baralho */
    
    /* Testar CriarBaralho */
    
    else if ( strcmp( ComandoTeste , CRIAR_BARALHO_CMD ) == 0 )
    {
        
        numLidos = LER_LerParametros( "i" ,
                                     &inxBaralho ) ;
        
        if ( ( numLidos != 1 )
            || ( ! ValidarInxBaralho( inxBaralho , VAZIO )))
        {
            return TST_CondRetParm ;
        } /* if */
        
        vtBaralhos[ inxBaralho ] =
        BAR_CriarBaralho( ) ;
        
        return TST_CompararPonteiroNulo( 1 , vtBaralhos[ inxBaralho ] ,
                                        "Erro em ponteiro de novo Baralho."  ) ;
        
    } /* fim ativa: Testar CriarBaralho */
    
    /* Testar DestruirBaralho */
    
    else if ( strcmp( ComandoTeste , DESTRUIR_BARALHO_CMD ) == 0 )
    {
        
        numLidos = LER_LerParametros( "i" ,
                                     &inxBaralho ) ;
        
        if ( ( numLidos != 1 )
            || ( ! ValidarInxBaralho( inxBaralho , NAO_VAZIO )))
        {
            return TST_CondRetParm ;
        } /* if */
        
        BAR_DestruirBaralho ( vtBaralhos[ inxBaralho ] ) ;

        vtBaralhos[ inxBaralho ] = NULL ;
        
        return TST_CompararPonteiroNulo( 0 , vtBaralhos[ inxBaralho ] ,
                                        "Erro em destruir Baralho."  ) ;
        
    } /* fim ativa: Testar DestruirBaralho */
    
    /* Testar CriarCarta */
    
    else if ( strcmp( ComandoTeste , CRIAR_CARTA_CMD ) == 0 )
    {
        
        numLidos = LER_LerParametros( "iii" ,
                                     &inxCarta, &valorRecebido, &naipeRecebido ) ;
        
        if ( ( numLidos != 1 )
            || ( ! ValidarInxCarta( inxCarta , VAZIO )))
        {
            return TST_CondRetParm ;
        } /* if */
        
        vtCartas[ inxCarta ] =
        BAR_CriarCarta(valorRecebido, naipeRecebido) ;
        
        return TST_CompararPonteiroNulo( 1 , vtCartas[ inxCarta ] ,
                                        "Erro em ponteiro da nova Carta."  ) ;
        
    } /* fim ativa: Testar CriarCarta */
    
    
    /* Testar DestruirCarta */
    
    else if ( strcmp( ComandoTeste , DESTRUIR_CARTA_CMD ) == 0 )
    {
        
        numLidos = LER_LerParametros( "i" ,
                                     &inxCarta ) ;
        
        if ( ( numLidos != 1 )
            || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )))
        {
            return TST_CondRetParm ;
        } /* if */
        
        BAR_DestruirCarta ( vtCartas[ inxCarta ] );
        
        return TST_CompararPonteiroNulo( 0 , vtCartas[ inxCarta ] ,
                                        "Erro em destruir Carta."  ) ;
        
    } /* fim ativa: Testar DestruirCarta */
    
    /* Testar ObterInfoDaCarta */
    
    else if ( strcmp( ComandoTeste , OBTER_INFO_CARTA_CMD ) == 0 )
    {
        
        numLidos = LER_LerParametros( "iiii" ,
                                     &inxCarta, &valorEsperado, &naipeEsperado, &CondRetEsp ) ;
        
        if ( ( numLidos != 4 )
            || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )))
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRet = BAR_ObterInfo( (BAR_tppCarta)vtCartas[ inxCarta ], &naipeRecebido, &valorRecebido);
        
        if(CondRetEsp == 0)
        {
            return TST_CompararPonteiroNulo( 0 , vtCartas[ inxCarta ] ,
                                            "Carta nao deveria existir." ) ;
        } /* if */
        
        CondRet = TST_CompararInt(valorEsperado, valorRecebido ,
                                  "Valores recebidos nao sao iguais");
        
        if(CondRet == TST_CondRetOK)
        {
            return TST_CompararInt(naipeEsperado, naipeRecebido,
                                   "Naipes recebidos nao sao iguais");
        } /* if */
        
        return CondRet;
        
        
    } /* fim ativa: Testar ObterInfoDaCarta */
    
    /* Testar IdentificaMaior */
    
    else if ( strcmp( ComandoTeste , ID_MAIOR_CMD ) == 0 )
    {
        
        numLidos = LER_LerParametros( "iiiii" ,
                                     &inxCarta1, &inxCarta2, &inxCartaManilha, &maiorEsperado, &CondRetEsp  ) ;
        
        if ( ( numLidos != 5 )
            || ( ! ValidarInxCarta( inxCarta1 , NAO_VAZIO ))
            || ( ! ValidarInxCarta( inxCarta2 , NAO_VAZIO ))
            || ( ! ValidarInxCarta( inxCartaManilha , NAO_VAZIO )))
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRet = BAR_IdentificaMaior ( vtCartas[ inxCarta1 ], vtCartas[ inxCarta2 ], vtCartas[ inxCartaManilha ], &maiorRecebido );
        
        if ( CondRetEsp == 0 )
        {
            CondRet =  TST_CompararPonteiroNulo( 0 , vtCartas[ inxCarta1 ] ,
                                                "Carta 1 nao deveria existir." ) ;
            if ( CondRet == TST_CondRetOK )
            {
                CondRet =  TST_CompararPonteiroNulo( 0 , vtCartas[ inxCarta2 ] ,
                                                    "Carta 2 nao deveria existir." ) ;
                if ( CondRet == TST_CondRetOK )
                {
                    return TST_CompararPonteiroNulo( 0 , vtCartas[ inxCartaManilha ] ,
                                                    "Carta Manilha nao deveria existir." ) ;
                }
            }
            
            return CondRet;
        } /* if */
        
        return TST_CompararInt(maiorEsperado, maiorRecebido,
                               "Valores recebidos nao sao iguais");
        
    } /* fim ativa: Testar IdentificaMaior */
    
    /* Testar Embaralhar */
    
    else if ( strcmp( ComandoTeste , EMBARALHAR_CMD ) == 0 )
    {
        
        numLidos = LER_LerParametros( "ii" ,
                                     &inxBaralho, &CondRetEsp  ) ;
        
        if ( ( numLidos != 2 )
            || ( ! ValidarInxBaralho( inxBaralho , NAO_VAZIO ) ) )
        {
            if ( vtBaralhos [ inxBaralho ] != NULL )
            {
                return TST_CondRetParm ;
            }
        } /* if */
        
        CondRet = BAR_Embaralhar ( vtBaralhos[ inxBaralho ] );
        
        if ( CondRetEsp == 0 )
        {
            return TST_CompararPonteiroNulo( 1 , vtBaralhos [ inxBaralho ] ,
                                            "Baralho nao e vazio." ) ;
        }
        else if ( CondRetEsp == BAR_CondRetBaralhoVazio )
        {
            return TST_CompararPonteiroNulo( 0 , vtBaralhos [ inxBaralho ] ,
                                            "Baralho nao deveria ser vazio." ) ;
        }
        else if ( CondRetEsp == BAR_CondRetBaralhoNaoExiste )
        {
            return TST_CompararPonteiroNulo( 0 , vtBaralhos [ inxBaralho ] ,
                                            "Baralho não deveria existir." ) ;
        }
        
        return TST_CondRetNaoConhec ;
        
    } /* fim ativa: Testar Embaralhar */
    
    /* Testar PuxarCarta */
    
    else if ( strcmp( ComandoTeste , PUXAR_CARTA_CMD ) == 0 )
    {
        
        numLidos = LER_LerParametros( "iiii" ,
                                     &inxBaralho, &valorEsperado, &naipeEsperado, &CondRetEsp ) ;
        
        if ( ( numLidos != 4 )
            || ( ! ValidarInxBaralho( inxBaralho , NAO_VAZIO ) ) )
        {
            if ( vtBaralhos [ inxBaralho ] != NULL )
            {
                return TST_CondRetParm ;
            }
        } /* if */

//        printf("end pCarta teste antes: %d\n", pDado);
        
        CondRet = BAR_PuxarCarta( vtBaralhos [ inxBaralho ], pDado );

        if ( CondRet == BAR_CondRetBaralhoVazio )
        {
            if ( CondRetEsp == BAR_CondRetBaralhoVazio )
            {
                return TST_CondRetOK ;
            }
            else
            {
                return TST_CompararInt( CondRetEsp, CondRet ,
                                  "Valores recebidos nao sao iguais") ;
            }
        }
        else if ( CondRet == BAR_CondRetBaralhoNaoExiste )
        {
            if ( CondRetEsp == BAR_CondRetBaralhoNaoExiste )
            {
                return TST_CondRetOK ;
            }
            else
            {
                return TST_CompararInt( CondRetEsp, CondRet ,
                                  "Valores recebidos nao sao iguais") ;
            }
        } /* if */

        CondRet = BAR_ObterInfo( pDado, &valorRecebido, &naipeRecebido);

        if ( CondRetEsp == 0 )
        {
            CondRet = TST_CompararPonteiroNulo( 1 , vtBaralhos [ inxBaralho ] ,
                                            "Baralho nao deveria existir." ) ;

            if ( CondRet == TST_CondRetOK )
            {
                CondRet = TST_CompararInt( valorEsperado, valorRecebido ,
                                  "Valores recebidos nao sao iguais") ;

                if ( CondRet == TST_CondRetOK )
                {
                    CondRet = TST_CompararInt( naipeEsperado, naipeRecebido,
                                           "Naipes recebidos nao sao iguais") ;
                }
            }
        } /* if */
  
        return CondRet;
        
    } /* fim ativa: Testar PuxarCarta */
    
    /* Testar ObterNumCarta */
    else if ( strcmp( ComandoTeste , OBTER_NUM_CMD ) == 0 )
    {
        
        numLidos = LER_LerParametros( "ii" ,
                                     &inxBaralho, &valorEsperado ) ;
        
        if ( ( numLidos != 2 )
            || ( ! ValidarInxBaralho( inxBaralho , NAO_VAZIO ) ) )
        {
            if ( vtBaralhos [ inxBaralho ] != NULL )
            {
                return TST_CondRetParm ;
            }
        } /* if */
        
        CondRet = BAR_ObterNumerodeCartas( vtBaralhos [ inxBaralho ], &valorRecebido );
        
        return TST_CompararInt(valorEsperado, valorRecebido,
                               "Valores recebidos nao sao iguais") ;
        
    } /* fim ativa: Testar ObterNumCarta */

    /* Testar CompararBaralhos */
    else if ( strcmp( ComandoTeste , COMPARAR_BARALHOS_CMD ) == 0 )
    {
        numLidos = LER_LerParametros( "iii" ,
                                     &inxBaralho1, &inxBaralho2, &CondRetEsp ) ;

        if ( ( numLidos != 3 )
            || ( ! ValidarInxBaralho( inxBaralho1 , NAO_VAZIO ) )
            || ( ! ValidarInxBaralho( inxBaralho2 , NAO_VAZIO ) ) )
        {
 //           if ( vtBaralhos [ inxBaralho1 ] != NULL )
 //           {
                return TST_CondRetParm ;
 //           }
        } /* if */

        CondRet = BAR_ComparaBaralhos( vtBaralhos [ inxBaralho1 ] , vtBaralhos [ inxBaralho2 ] ) ;

        if ( CondRet == 0 )
        {
            if ( CondRetEsp == CondRet )
            {
                return TST_CondRetOK ;
            }
            else
            {
                return TST_CompararInt(CondRetEsp, CondRet,
                               "Valores recebidos nao sao iguais") ;
            }
        }
        else if ( CondRet == BAR_CondRetQuantidadesDiferentes )
        {
            if ( CondRetEsp == CondRet )
            {
                return TST_CondRetOK ;
            }
            else
            {
                return TST_CompararInt(CondRetEsp, CondRet,
                               "Valores recebidos nao sao iguais") ;
            }
        }
        else if ( CondRet == BAR_CondRetBaralhosDiferentes )
        {
            if ( CondRetEsp == CondRet )
            {
                return TST_CondRetOK ;
            }
            else
            {
                return TST_CompararInt(CondRetEsp, CondRet,
                               "Valores recebidos nao sao iguais") ;
            }
        } /* if */

    } /* fim ativa: Testar CompararBaralhos */
    
    return TST_CondRetNaoConhec ;
}

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
 *
 *  $FC Função: TBAR -Destruir valor
 *
 ***********************************************************************/

void DestruirValor( void * pValor )
{
    
    free( pValor ) ;
    
} /* Fim função: TBAR -Destruir valor */
/***********************************************************************
 *
 *  $FC Função: TBAR -Validar indice de baralho
 *
 ***********************************************************************/

int ValidarInxBaralho( int inxBaralho , int Modo )
{
    
    if ( ( inxBaralho <  0 )
        || ( inxBaralho >= DIM_VT_BARALHO ))
    {
        return FALSE ;
    } /* if */
    
    if ( Modo == VAZIO )
    {
        if ( vtBaralhos[ inxBaralho ] != NULL )
        {
            return FALSE ;
        } /* if */
    } else
    {
        if ( vtBaralhos[ inxBaralho ] == NULL )
        {
            return FALSE ;
        } /* if */
    } /* if */
    
    return TRUE ;
    
} /* Fim função: TBAR -Validar indice de Baralho */

/***********************************************************************
 *
 *  $FC Função: TBAR -Validar indice de carta
 *
 ***********************************************************************/

int ValidarInxCarta( int inxCarta , int Modo )
{
    
    if ( ( inxCarta <  0 )
        || ( inxCarta >= DIM_VT_CARTA ))
    {
        return FALSE ;
    } /* if */
    
    if ( Modo == VAZIO )
    {
        if ( vtCartas[ inxCarta ] != 0 )
        {
            return FALSE ;
        } /* if */
    } else
    {
        if ( vtCartas[ inxCarta ] == 0 )
        {
            return FALSE ;
        } /* if */
    } /* if */
    
    return TRUE ;
    
} /* Fim função: TBAR -Validar indice de carta */

/********** Fim do módulo de implementação: TBAR Teste do modulo baralho **********/

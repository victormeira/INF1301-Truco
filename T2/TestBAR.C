/***************************************************************************
*  $MCI Módulo de implementação: TBAR Teste Baralho
*
*  Arquivo gerado:              TestBAR.c
*  Letras identificadoras:      TBAR
*
*  Autores: vmp - Victor Meira Pinto
*			bcr - Bernardo Costa Ruga
*			awv - Alexandre Wanick Vieira 
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     		Observações
*     1.0       vmp   19/abr/2004 	início desenvolvimento
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
static const char CRIAR_CARTA_CMD			[ ] = "=criarcarta"	;
static const char DESTRUIR_CARTA_CMD     	[ ] = "=destruircarta"  ;
static const char OBTER_INFO_CARTA_CMD      [ ] = "=obterinfocarta"  ;
static const char ID_MAIOR_CMD     			[ ] = "=idmaior"   ;
static const char EMBARALHAR_CMD	       	[ ] = "=embaralhar"    ;
static const char PUXAR_CARTA_CMD         	[ ] = "=puxarcarta" ;
static const char OBTER_NUM_CMD            	[ ] = "=obternum"    ;



#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_BARALHO  3
#define DIM_VT_CARTA  	40
#define DIM_VALOR     	100

BAR_tppBaralho   vtBaralhos[ DIM_VT_BARALHO ] ;
BAR_tppBaralho   vtCartas[ DIM_VT_CARTA ] ;

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
*	  =criarcarta					inxCarta valor naipe	
*     =destruircarta                inxCarta
*     =obterinfocarta              	inxCarta  valorEsperado naipeEsperado  CondretPonteiro
*     =idmaior 			            inxCarta1 inxCarta2  inxCartaManilha maiorEsperado  CondretPonteiro
*     =embaralhar                   inxBaralho CondretEsperado
*     =puxarcarta                   inxBaralho valorEsperado naipeEsperado CondretPonteiro
*     =obternum                  	inxBaralho numEsperado
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxCarta  = -1 ,
      	  inxCarta1 = -1 ,
      	  inxCarta2 = -1 ,
      	  inxCartaManilha = -1, 	
      	  inxBaralho = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1 ,
          CondretPonteiro = -1 ,
          valorEsperado = -1 ,
          naipeEsperado = -1 ,
          maiorEsperado = -1 ,
          numEsperado = -1 ;

      TST_tpCondRet CondRet ;

      char   StringDado[  DIM_VALOR ] ;
      BAR_tppCarta pDado ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_BARALHO_CMD ) == 0 )
         {
            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtBaralhos[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

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

            BAR_DestruirBaralho ( vtBaralhos[ inxBaralho ] );

            return TST_CompararPonteiroNulo( 0 , vtBaralhos[ inxBaralho ] ,
               "Erro em destruir Baralho."  ) ;

         } /* fim ativa: Testar DestruirBaralho */

      /* Testar CriarCarta */

         else if ( strcmp( ComandoTeste , CRIAR_CARTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxBaralho, &valor, &naipe ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxBaralho( inxBaralho , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtCartas[ inxCarta ] =
                 BAR_CriarCarta(valor, naipe) ;

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
                       &inxCarta, &valorEsperado, &naipeEsperado, &CondretPonteiro  ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxCarta( inxCarta , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            /* CHAMADA DA FUNCAO */

            /* TESTE DE CADA CASO */

         } /* fim ativa: Testar ObterInfoDaCarta */

   	/* Testar IdentificaMaior */

         else if ( strcmp( ComandoTeste , ID_MAIOR_CMD  ) == 0 )
         {

            numLidos = LER_LerParametros( "iiiii" ,
                       &inxCarta1, &inxCarta2, &inxCartaManilha, &maiorEsperado, &CondretPonteiro  ) ;

            if ( ( numLidos != 5 )
              || ( ! ValidarInxCarta( inxCarta1 , NAO_VAZIO ))
              || ( ! ValidarInxCarta( inxCarta2 , NAO_VAZIO ))
              || ( ! ValidarInxCarta( inxCartaManilha , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            /* CHAMADA DA FUNCAO */

            /* TESTE DE CADA CASO */

         } /* fim ativa: Testar IdentificaMaior */

   	/* Testar Embaralhar */

         else if ( strcmp( ComandoTeste , EMBARALHAR_CMD  ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxBaralho, &CondretEsperado  ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxBaralho( inxBaralho , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */


            /* CHAMADA DA FUNCAO */
            /* TESTE DE CADA CASO */

         } /* fim ativa: Testar Embaralhar */

   	/* Testar PuxarCarta */

         else if ( strcmp( ComandoTeste , PUXAR_CARTA_CMD   ) == 0 )
         {

            numLidos = LER_LerParametros( "iiii" ,
                      &inxBaralho, &valorEsperado, &naipeEsperado, &CondretPonteiro  ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxBaralho( inxBaralho , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            /* CHAMADA DA FUNCAO */   
            /* TESTE DE CADA CASO */

         } /* fim ativa: Testar PuxarCarta */

   	/* Testar ObterNumCarta */
         else if ( strcmp( ComandoTeste , OBTER_NUM_CMD   ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                      &inxBaralho, &numEsperado  ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxBaralho( inxBaralho , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            /* CHAMADA DA FUNCAO */   
            /* TESTE DE CADA CASO */

         } /* fim ativa: Testar ObterNumCarta */


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
         if ( vtBaralhos[ inxBaralho ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtBaralhos[ inxBaralho ] == 0 )
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
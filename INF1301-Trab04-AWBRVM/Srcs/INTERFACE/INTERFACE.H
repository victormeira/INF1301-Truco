#if ! defined( INTERFACE_ )
#define INTERFACE_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo Baralho
*  Arquivo:              Baralho.h
*
*  Autores: awv - Alexandre Wanick Vieira
*           bcr - Bernardo Costa Ruga
*           vmp - Victor Meira Pinto  
*
*  $HA Hist�rico de evolu��o:
*     Vers�o    Autor    Data          Observa��es
*      1.0       bcr      15/04         Cria��o do arquivo Baralho.h
*      1.1       awv      19/04         Revis�o do c�digo e atualiza��o das condi��es de retorno
*      1.2       awv      30/04         Revis�o do c�digo
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e explorar
*     um baralho de cartas.
*
***************************************************************************/

#if defined( INTERFACE_OWN )
   #define INTERFACE_EXT
#else
   #define INTERFACE_EXT extern
#endif

void INT_CarregarImagens( void ) ;
//void INT_DesenharCarta( int valor, int naipe, float xEsquerda, float yBaixo, float largura, float altura ) ;
void INT_ConfigurarInterface( int * pArgc , char ** argv ) ;
void INT_Display( void ) ;
void INT_DesenharCartasNaMao( void ) ;

#undef INTERFACE_EXT

/********** Fim do m�dulo de defini��o: M�dulo Baralho **********/

#else
#endif

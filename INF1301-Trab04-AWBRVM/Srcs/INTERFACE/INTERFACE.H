#if ! defined( INTERFACE_ )
#define INTERFACE_
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
*      1.0       bcr      15/04         Criação do arquivo Baralho.h
*      1.1       awv      19/04         Revisão do código e atualização das condições de retorno
*      1.2       awv      30/04         Revisão do código
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e explorar
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

/********** Fim do módulo de definição: Módulo Baralho **********/

#else
#endif

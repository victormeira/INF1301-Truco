#if ! defined( PARTIDA_ )
#define PARTIDA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Partida
*  Arquivo:              Partida.h
*
*  Autores: awv - Alexandre Wanick Vieira
*           bcr - Bernardo Costa Ruga
*           vmp - Victor Meira Pinto  
*
*  $HA Histórico de evolução:
*     Versão    Autor    Data          Observações
*      1.0       awv      20/06         Criação do arquivo Partida.h
*      1.1       vmp      22/06         Revisão do código
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e explorar
*     um baralho de cartas.
*
***************************************************************************/

#if defined( PARTIDA_OWN )
   #define PARTIDA_EXT
#else
   #define PARTIDA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: PAR Condições de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da partida
*
***********************************************************************/

    typedef enum {

        PAR_CondRetOk ,
            /* Condição de Retorno OK, usada quando a função executa
               corretamente */
        PAR_CondRetFaltouMemoria ,
            /* Condição de Retorno faltou memória, usada quando a
               memoria do sistema não apresenta mais espaço */
        PAR_CondRetNumJogadoresInvalido
        	/* Condição de Retorno número de jogadores inválido, usada
              quando o número de jogadores é inválido */

    } PAR_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PAR  &Criar Partida
*
*  $ED Descrição da função
*     Cria a partida.
*
*  $EP Parâmetros
*     numJogadores - número de jogadores na partida
*
*  $FV Valor retornado
*     PAR_CondRetOk
*     PAR_CondRetFaltouMemoria
*     PAR_CondRetNumJogadoresInvalido
*
***********************************************************************/

    PAR_tpCondRet PAR_CriarPartida ( int numJogadores ) ;


/***********************************************************************
*
*  $FC Função: PAR  &Iniciar Partida
*
*  $ED Descrição da função
*     Inicia a partida.
*
***********************************************************************/

    void PAR_IniciarPartida ( void ) ;


/***********************************************************************
*
*  $FC Função: PAR  &Destruir Partida
*
*  $ED Descrição da função
*     Destrói a partida.
*
***********************************************************************/

    void PAR_DestruirPartida ( void ) ;

	int PAR_IniciarMao( void ) ;

	int PAR_FinalizarRodada( void ) ;

	int PAR_AtualizarRodada( void ) ;

	int PAR_IniciarRodada( void ) ;

	void *  PAR_ObterMaoJogador( int jogadorId ) ;


#undef PARTIDA_EXT

/********** Fim do módulo de definição: Módulo Partida **********/

#else
#endif

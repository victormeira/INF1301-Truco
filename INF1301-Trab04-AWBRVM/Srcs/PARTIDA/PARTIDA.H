#if ! defined( PARTIDA_ )
#define PARTIDA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Mesa
*  Arquivo:              Mesa.h
*
*  Autores: awv - Alexandre Wanick Vieira
*           bcr - Bernardo Costa Ruga
*           vmp - Victor Meira Pinto  
*
*  $HA Histórico de evolução:
*     Versão    Autor    Data          Observações
*      1.0       awv      15/04         Criação do arquivo Mesa.h
*      1.1       awv      19/04         Revisão do código e atualização das condições de retorno
*      1.2       awv      30/04         Revisão do código
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

/* Tipo referência para uma partida */

typedef struct tgPartida * PAR_tppPartida ;


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
        PAR_CondRetFaltouMemoria
            /* Condição de Retorno faltou memória, usada quando a
               memoria do sistema não apresenta mais espaço */

    } PAR_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PAR  &Criar Partida
*
*  $ED Descrição da função
*     Cria a partida.
*
*  $FV Valor retornado
*     PAR_CondRetOk
*     PAR_CondRetFaltouMemoria
*
***********************************************************************/

    PAR_tppPartida PAR_CriarPartida ( void ) ;


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


#undef PARTIDA_EXT

/********** Fim do módulo de definição: Módulo Mesa **********/

#else
#endif

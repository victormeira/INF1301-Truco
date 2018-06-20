#if ! defined( MESA_ )
#define MESA_
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

#if defined( MESA_OWN )
   #define MESA_EXT
#else
   #define MESA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma carta */

typedef struct tgCarta * MES_tppCarta ;

/* Tipo referência para a mesa */

typedef struct tgMesa * MES_tppMesa ;


/***********************************************************************
*
*  $TC Tipo de dados: MES Condições de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da mesa
*
***********************************************************************/

    typedef enum {

        MES_CondRetOk ,
            /* Condição de Retorno OK, usada quando a função executa
               corretamente */
        MES_CondRetFaltouMemoria ,
            /* Condição de Retorno faltou memória, usada quando a
               memoria do sistema não apresenta mais espaço */
        MES_CondRetCartaNaoExiste ,
            /* Condição de Retorno carta não existe, usada quando a
               carta recebida como parâmetro é NULL */
        MES_CondRetMesaNaoExiste ,
            /* Condição de Retorno mesa não existe, usada quando a
               mesa recebida como parâmetro é NULL */
        MES_CondRetMesaVazia ,
            /* Condição de Retorno mesa está vazia, usada quando a
               lista de cartas na mesa recebida como parâmetro é NULL */
        MES_CondRetJogadorNaoExiste
            /* Condição de Retorno jogador não existe, usada quando o
               jogadorId recebido como parâmetro não corresponde a
               nenhum dos jogadores existentes */

    } MES_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MES  &Criar Mesa
*
*  $ED Descrição da função
*     Cria uma nova mesa.
*
*  $FV Valor retornado
*     Se executou corretamente, retorna o ponteiro para a mesa.
*     Este ponteiro será utilizado pelas funções que manipulem esta mesa.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
*  $EP Parâmetros
*     numJogadores - número de jogadores na mesa
*
***********************************************************************/

    MES_tppMesa MES_CriarMesa ( int numJogadores ) ;


/***********************************************************************
*
*  $FC Função: MES  &Define Manilha
*
*  $ED Descrição da função
*     Define a manilha da rodada.
*
*  $EP Parâmetros
*     pMesa - ponteiro para a mesa
*     cartaManilha - ponteiro pra manilha a ser definida
*
***********************************************************************/

    MES_tpCondRet MES_DefineManilha ( MES_tppMesa pMesa, BAR_tpCarta * cartaManilha ) ;

/***********************************************************************
*
*  $FC Função: MES  &Destruir Mesa
*
*  $ED Descrição da função
*     Destrói a mesa.
*
*  $EP Parâmetros
*     pMesa - ponteiro para a mesa a ser destruída.
*
***********************************************************************/

    void MES_DestruirMesa ( MES_tppMesa pMesa ) ;


/***********************************************************************
*
*  $FC Função: MES  &Esvaziar Mesa
*
*  $ED Descrição da função
*     Vai retirar da mesa todas as cartas que estiverem contidas nela.
*
*  $EP Parâmetros
*     pMesa - ponteiro para a mesa que será esvaziada
*
*  $FV Valor retornado
*     MES_CondRetOk
*     MES_CondRetMesaNaoExiste
*
***********************************************************************/

    MES_tpCondRet MES_EsvaziarMesa ( MES_tppMesa pMesa ) ;


/***********************************************************************
*
*  $FC Função: MES  &Jogar Carta
*
*  $ED Descrição da função
*     Vai jogar uma carta na mesa.
*
*  $EP Parâmetros
*     pMesa - ponteiro para a mesa que terá uma carta jogada
*     pCarta - ponteiro que recebe a carta jogada na mesa
*     jogadorId - inteiro que representa o jogador da carta a ser jogada
*
*  $FV Valor retornado
*     MES_CondRetOk
*     MES_CondRetMesaNaoExiste
*     MES_CondRetCartaNaoExiste
*     MES_CondRetJogadorNaoExiste
*
***********************************************************************/

    MES_tpCondRet MES_JogarCarta ( MES_tppMesa pMesa ,
                                   MES_tppCarta pCarta ,
                                   int jogadorId ) ;


/***********************************************************************
*
*  $FC Função: MES  &Obter Carta
*
*  $ED Descrição da função
*     Obtém as informações da última carta jogada na mesa.
*
*  $EP Parâmetros
*     jogador - inteiro que representa o jogador da carta a ser obtida
*     pValor - ponteiro que retorna o valor da carta
*     pNaipe - ponteiro que retorna o naipe da carta
*
*  $FV Valor retornado
*     MES_CondRetOk
*     MES_CondRetCartaNaoExiste
*     MES_CondRetMesaNaoExiste
*     MES_CondRetMesaVazia
*     MES_CondRetJogadorNaoExiste
*
***********************************************************************/

    MES_tpCondRet MES_ObterCarta ( int jogadorId , int *pValor ,
                                   int *pNaipe ) ;


/***********************************************************************
*
*  $FC Função: MES  &Identificar Ganhador
*
*  $ED Descrição da função
*     Identifica qual é o jogador ganhador da rodada.
*
*  $EP Parâmetros
*     pMesa - ponteiro para a mesa
*     pGanhador - ponteiro que retorna o número do ID do jogador ganhador
*
*  $FV Valor retornado
*     MES_CondRetOk
*     MES_CondRetMesaNaoExiste
*     MES_CondRetMesaVazia
*     MES_CondRetJogadorNaoExiste
*
***********************************************************************/

    MES_tpCondRet MES_IdentificarGanhador ( MES_tppMesa pMesa ,
                                            int * pGanhador ) ;


#undef MESA_EXT

/********** Fim do módulo de definição: Módulo Mesa **********/

#else
#endif

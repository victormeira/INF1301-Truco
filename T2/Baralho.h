/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Baralho
*  Arquivo:              Baralho.h
*
*  Autores: bcr - Bernardo Costa Ruga
*           vmp - Victor Meira Pinto
*           awv - Alexandre Wanick Vieira
*
*  $HA Histórico de evolução:
*     Versão    Autor    Data          Observações
*      1.0       bcr      15/04         Criação do arquivo Baralho.h
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e explorar
*     um baralho de cartas.
*
***************************************************************************/

#ifndef Baralho_h
#define Baralho_h

/***********************************************************************
*
*  $TC Tipo de dados: BAR Condições de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno
*
***********************************************************************/

typedef enum{
    BAR_CondRetOk,
    /* Condicao de Retorno OK, usada quando a função executa corretamente */
    BAR_CondRetFaltouMemoria,
    /* Condicao de Retorno faltou memória, usada quando a memoria do sistema não apresenta mais espaço */
} BAR_tpCondRet;


typedef struct Carta carta;
typedef struct Baralho baralho;


/***********************************************************************
*
*  $FC Função: BAR Criar Carta
*
*  $ED Descrição da função
*     Cria uma nova carta.
*
*  $EP Parâmetros
*     $P Valor - é o parametro que indica o valor da carta a ser criada.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*     BAR_CondRetFaltouMemoria
*
***********************************************************************/

BAR_tpCondRet BAR_CriarCarta ( int Valor );

/***********************************************************************
*
*  $FC Função: BAR Destruir Carta
*
*  $ED Descrição da função
*     Destroi uma carta.
*
*  $EP Parâmetros
*     $P Carta - é o parametro que indica a carta que será destruida.
*
***********************************************************************/

void BAR_DestruirCarta ( carta Carta );

/***********************************************************************
*
*  $FC Função: BAR Obter Info
*
*  $ED Descrição da função
*     Obtem todas as informações pertinentes àquela carta.
*
*  $EP Parâmetros
*     $P Carta - é o parametro que a carta que obteremos as informações.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*
***********************************************************************/

BAR_tpCondRet BAR_ObterInfo ( carta Carta );

/***********************************************************************
*
*  $FC Função: BAR Identifica Maior
*
*  $ED Descrição da função
*     Identifica qual das duas cartas é a maior.
*
*  $EP Parâmetros
*     $P Carta1 - é o parametro que indica uma das duas cartas a serem comparadas.
*     $P Carta2 - é o parametro que indica uma das duas cartas a serem comparadas.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*
***********************************************************************/

BAR_tpCondRet BAR_IdentificaMaior ( carta Carta1, carta Carta2 );

/***********************************************************************
*
*  $FC Função: BAR Criar Baralho
*
*  $ED Descrição da função
*     Cria um novo baralho.
*
*  $EP Parâmetros
*     $P Baralho - é o parametro que indica o baralho a ser criado.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*     BAR_CondRetFaltouMemoria
*
***********************************************************************/

BAR_tpCondRet BAR_CriarBaralho ( baralho Baralho );

/***********************************************************************
*
*  $FC Função: BAR Destruir Baralho
*
*  $ED Descrição da função
*     Destroi o baralho.
*
*  $EP Parâmetros
*     $P Baralho - é o parametro que indica o baralho a ser destruido.
*
***********************************************************************/

void BAR_DestruirBaralho ( baralho Baralho );

/***********************************************************************
*
*  $FC Função: BAR Embaralhar
*
*  $ED Descrição da função
*     Vai embaralhar as cartas do baralho de maneira aleatória.
*
*  $EP Parâmetros
*     $P Baralho - é o parametro que indica o baralho a ser embaralhado.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*
***********************************************************************/

BAR_tpCondRet BAR_Embaralhar ( baralho Baralho );

/***********************************************************************
*
*  $FC Função: BAR Puxar Carta
*
*  $ED Descrição da função
*     Vai sacar uma carta do topo baralho.
*
*  $EP Parâmetros
*     $P Baralho - é o parametro que indica o baralho que terá uma carta sacada.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*
***********************************************************************/

BAR_tpCondRet BAR_PuxarCarta ( baralho Baralho );

/***********************************************************************
*
*  $FC Função: BAR Obter Número de Cartas
*
*  $ED Descrição da função
*     Vai identificar quantas cartas ainda restam no baralho.
*
*  $EP Parâmetros
*     $P Baralho - é o parametro que indica o baralho que será contado.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*
***********************************************************************/

BAR_tpCondRet BAR_ObterNumerodeCartas ( baralho Baralho );

#endif /* Baralho_h */
/********** Fim do módulo de definição: Módulo Baralho **********/

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


typedef struct tgCarta * BAR_tppCarta;
typedef struct tgBaralho * BAR_tppBaralho;


/***********************************************************************
*
*  $FC Função: BAR Criar Carta
*
*  $ED Descrição da função
*     Cria uma nova carta.
*
*  $EP Parâmetros
*     $P Valor - é o parâmetro que indica o valor da carta a ser criada.
*     $P Valor - é o parâmetro que indica o valor da carta a ser criada.
*
*  $FV Valor retornado
*     BAR_tppCarta pCarta
*
***********************************************************************/

BAR_tppCarta BAR_CriarCarta ( int Valor, int Naipe );

/***********************************************************************
*
*  $FC Função: BAR Destruir Carta
*
*  $ED Descrição da função
*     Destroi uma carta.
*
*  $EP Parâmetros
*     $P Carta - é o parâmetro que indica a carta que será destruida.
*
***********************************************************************/

void BAR_DestruirCarta ( BAR_tppCarta pCarta );

/***********************************************************************
*
*  $FC Função: BAR Obter Info
*
*  $ED Descrição da função
*     Obtem todas as informações pertinentes àquela carta.
*
*  $EP Parâmetros
*     $P Carta - é o parâmetro que a carta que obteremos as informações.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*
***********************************************************************/

BAR_tpCondRet BAR_ObterInfo ( BAR_tppCarta pCarta );

/***********************************************************************
*
*  $FC Função: BAR Identifica Maior
*
*  $ED Descrição da função
*     Identifica qual das duas cartas é a maior.
*
*  $EP Parâmetros
*     $P Carta1 - é o parâmetro que indica uma das duas cartas a serem comparadas.
*     $P Carta2 - é o parâmetro que indica uma das duas cartas a serem comparadas.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*
***********************************************************************/

BAR_tpCondRet BAR_IdentificaMaior ( BAR_tppCarta pCarta1, BAR_tppCarta pCarta2 );

/***********************************************************************
*
*  $FC Função: BAR Criar Baralho
*
*  $ED Descrição da função
*     Cria um novo baralho.
*
*  $EP Parâmetros
*     $P Baralho - é o parâmetro que indica o baralho a ser criado.
*
*  $FV Valor retornado
*     BAR_tppBaralho pBaralho
*
***********************************************************************/

BAR_tppBaralho BAR_CriarBaralho ( void );

/***********************************************************************
*
*  $FC Função: BAR Destruir Baralho
*
*  $ED Descrição da função
*     Destroi o baralho.
*
*  $EP Parâmetros
*     $P Baralho - é o parâmetro que indica o baralho a ser destruido.
*
***********************************************************************/

void BAR_DestruirBaralho ( BAR_tppBaralho pBaralho );

/***********************************************************************
*
*  $FC Função: BAR Embaralhar
*
*  $ED Descrição da função
*     Vai embaralhar as cartas do baralho de maneira aleatória.
*
*  $EP Parâmetros
*     $P Baralho - é o parâmetro que indica o baralho a ser embaralhado.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*
***********************************************************************/

BAR_tpCondRet BAR_Embaralhar ( BAR_tppBaralho pBaralho );

/***********************************************************************
*
*  $FC Função: BAR Puxar Carta
*
*  $ED Descrição da função
*     Vai sacar uma carta do topo baralho.
*
*  $EP Parâmetros
*     $P Baralho - é o parâmetro que indica o baralho que terá uma carta sacada.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*
***********************************************************************/

BAR_tpCondRet BAR_PuxarCarta ( BAR_tppBaralho pBaralho );

/***********************************************************************
*
*  $FC Função: BAR Obter Número de Cartas
*
*  $ED Descrição da função
*     Vai identificar quantas cartas ainda restam no baralho.
*
*  $EP Parâmetros
*     $P Baralho - é o parâmetro que indica o baralho que será contado.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*
***********************************************************************/

BAR_tpCondRet BAR_ObterNumerodeCartas ( BAR_tppBaralho pBaralho );

#endif /* Baralho_h */
/********** Fim do módulo de definição: Módulo Baralho **********/

#if ! defined( BARALHO_ )
#define BARALHO_
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
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e explorar
*     um baralho de cartas.
*
***************************************************************************/

#if defined( BARALHO_OWN )
   #define BARALHO_EXT
#else
   #define BARALHO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma carta */

typedef struct tgCarta * BAR_tppCarta ;

/* Tipo referência para o baralho */

typedef struct tgBaralho * BAR_tppBaralho ;


/***********************************************************************
*
*  $TC Tipo de dados: BAR Condições de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do baralho
*
***********************************************************************/

    typedef enum {

        BAR_CondRetOk ,
            /* Condição de Retorno OK, usada quando a função executa
               corretamente */
        BAR_CondRetFaltouMemoria ,
            /* Condição de Retorno faltou memória, usada quando a
               memoria do sistema não apresenta mais espaço */
        BAR_CondRetCartaNaoExiste ,
            /* Condição de Retorno carta nao existe, usada quando a
               carta recebida como parametro é NULL */
        BAR_CondRetBaralhoNaoExiste ,
            /* Condição de Retorno baralho nao existe, usada quando o
               baralho recebido como parametro é NULL */
        BAR_CondRetBaralhoVazio ,
            /* Condição de Retorno baralho esta vazio, usada quando o
               deck(lista) do baralho recebido como parametro é NULL */
        BAR_CondRetBaralhoIncompleto ,
            /* Condição de Retorno baralho contém menos do que 40
               cartas */
        BAR_CondRetQuantidadesDiferentes ,
            /* Condição de Retorno os baralhos não possuem a mesma quantidade
             de cartas */
        BAR_CondRetBaralhosDiferentes
            /* Condição de Retorno os baralhos comparados não são iguais */

    } BAR_tpCondRet ;


/***********************************************************************
*
*  $FC Função: BAR  &Criar Carta
*
*  $ED Descrição da função
*     Cria uma nova carta.
*
*  $EP Parâmetros
*     $P Valor - é o parâmetro que indica o valor da carta a ser criada.
*     $P Naipe - é o parâmetro que indica o naipe da carta a ser criada.
*
*  $FV Valor retornado
*     BAR_tppCarta pCarta
*
***********************************************************************/

    BAR_tppCarta BAR_CriarCarta ( int Valor, int Naipe ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Destruir Carta
*
*  $ED Descrição da função
*     Destrói uma carta.
*
*  $EP Parâmetros
*     $P Carta - é o parâmetro que indica a carta que será destruida.
*
***********************************************************************/

    void BAR_DestruirCarta ( BAR_tppCarta pCarta ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Obter Info
*
*  $ED Descrição da função
*     Obtém todas as informações pertinentes àquela carta.
*
*  $EP Parâmetros
*     $P Carta - é o parâmetro que a carta que obteremos as informações.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*
***********************************************************************/

    BAR_tpCondRet BAR_ObterInfo (BAR_tppCarta pCarta, int *pNaipe,
                                 int *pValor ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Identifica Maior
*
*  $ED Descrição da função
*     Identifica qual é a maior carta dentre duas cartas.
*
*  $EP Parâmetros
*     $P Carta1 - é o parâmetro que indica uma das duas cartas a serem comparadas.
*     $P Carta2 - é o parâmetro que indica uma das duas cartas a serem comparadas.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*
***********************************************************************/

    BAR_tpCondRet BAR_IdentificaMaior (BAR_tppCarta pCarta1,
                                       BAR_tppCarta pCarta2,
                                       BAR_tppCarta pManilha,
                                       int * pMaior ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Criar Baralho
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

    BAR_tppBaralho BAR_CriarBaralho ( void ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Destruir Baralho
*
*  $ED Descrição da função
*     Destroi o baralho.
*
*  $EP Parâmetros
*     $P Baralho - é o parâmetro que indica o baralho a ser destruido.
*
***********************************************************************/

    void BAR_DestruirBaralho ( BAR_tppBaralho pBaralho ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Embaralhar
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

    BAR_tpCondRet BAR_Embaralhar ( BAR_tppBaralho pBaralho ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Puxar Carta
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

    BAR_tpCondRet BAR_PuxarCarta (BAR_tppBaralho pBaralho,
                                  BAR_tppCarta pCarta ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Obter Número de Cartas
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

    BAR_tpCondRet BAR_ObterNumerodeCartas ( BAR_tppBaralho pBaralho,
                                            int *pQtd ) ;

#undef BARALHO_EXT

/********** Fim do módulo de definição: Módulo Baralho **********/

#else
#endif

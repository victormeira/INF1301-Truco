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
*      1.2       awv      30/04         Revisão do código
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
*     Valor - valor da carta a ser criada
*     Naipe - naipe da carta a ser criada
*
*  $FV Valor retornado
*     Se executou corretamente, retorna o ponteiro para a carta.
*     Este ponteiro será utilizado pelas funções que manipulem esta carta.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

    BAR_tppCarta BAR_CriarCarta ( int Valor , int Naipe ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Destruir Carta
*
*  $ED Descrição da função
*     Destrói uma carta.
*
*  $EP Parâmetros
*     pCarta - ponteiro para a carta que será destruída
*
***********************************************************************/

    void BAR_DestruirCarta ( BAR_tppCarta pCarta ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Obter Info
*
*  $ED Descrição da função
*     Obtém todas as informações pertinentes àquela carta
*
*  $EP Parâmetros
*     pCarta - ponteiro para a carta que obteremos as informações
*     pValor - ponteiro que retorna o valor da carta
*     pNaipe - ponteiro que retorna o naipe da carta
*
*  $FV Valor retornado
*     BAR_CondRetOk
*     BAR_CondRetCartaNaoExiste
*
***********************************************************************/

    BAR_tpCondRet BAR_ObterInfo (BAR_tppCarta pCarta, int *pValor ,
                                 int *pNaipe ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Identifica Maior
*
*  $ED Descrição da função
*     Identifica qual é a maior carta dentre duas cartas.
*
*  $EP Parâmetros
*     pCarta1 - ponteiro para uma das duas cartas a serem comparadas
*     pCarta2 - ponteiro para uma das duas cartas a serem comparadas
*     pManilha - ponteiro para a carta manilha
*     pMaior - ponteiro que retorna o número da maior carta
*
*  $FV Valor retornado
*     BAR_CondRetOk
*     BAR_CondRetCartaNaoExiste
*
***********************************************************************/

    BAR_tpCondRet BAR_IdentificaMaior (BAR_tppCarta pCarta1 ,
                                       BAR_tppCarta pCarta2 ,
                                       BAR_tppCarta pManilha ,
                                       int * pMaior ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Criar Baralho
*
*  $ED Descrição da função
*     Cria um novo baralho.
*
*  $FV Valor retornado
*     Se executou corretamente, retorna o ponteiro para o baralho.
*     Este ponteiro será utilizado pelas funções que manipulem este baralho.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
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
*     pBaralho - ponteiro para o baralho a ser destruído.
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
*     pBaralho - ponteiro para o baralho a ser embaralhado.
*
*  $FV Valor retornado
*     BAR_CondRetOk
*     BAR_CondRetBaralhoNaoExiste
*     BAR_CondRetBaralhoIncompleto
*     BAR_CondRetCartaNaoExiste
*
***********************************************************************/

    BAR_tpCondRet BAR_Embaralhar ( BAR_tppBaralho pBaralho ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Puxar Carta
*
*  $ED Descrição da função
*     Vai sacar uma carta do topo do baralho.
*
*  $EP Parâmetros
*     pBaralho - ponteiro para o baralho que terá uma carta sacada
*     pCarta - ponteiro que recebe a carta sacada do baralho
*
*  $FV Valor retornado
*     BAR_CondRetOk
*     BAR_CondRetBaralhoNaoExiste
*     BAR_CondRetBaralhoVazio
*     BAR_CondRetCartaNaoExiste
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
*     pBaralho - ponteiro para o baralho que será contado
*     pQtd - ponteiro que retorna a quantidade de cartas do baralho
*
*  $FV Valor retornado
*     BAR_CondRetOk
*     BAR_CondRetBaralhoNaoExiste
*
***********************************************************************/

    BAR_tpCondRet BAR_ObterNumerodeCartas ( BAR_tppBaralho pBaralho,
                                            int *pQtd ) ;


/***********************************************************************
*
*  $FC Função: BAR  &Comparar Baralhos
*
*  $ED Descrição da função
*     Compara dois baralhos, dizendo se são iguais, diferentes ou se
*               são de tamanhos diferentes.
*
*  $EP Parâmetros
*     pBaralho1 - ponteiro para um dos baralhos a serem comparados
*     pBaralho2 - ponteiro para um dos baralhos a serem comparados
*
*  $FV Valor retornado
*     BAR_CondRetOk
*     BAR_CondRetQuantidadesDiferentes
*     BAR_CondRetBaralhoVazio
*     BAR_CondRetBaralhosDiferentes
*
***********************************************************************/

    BAR_tpCondRet BAR_ComparaBaralhos ( BAR_tppBaralho pBaralho1 ,
                                        BAR_tppBaralho pBaralho2 ) ;


#undef BARALHO_EXT

/********** Fim do módulo de definição: Módulo Baralho **********/

#else
#endif

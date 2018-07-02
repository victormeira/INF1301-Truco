/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Partida
*  Arquivo:              Partida.c
*
*  Autores: awv - Alexandre Wanick Vieira
*           bcr - Bernardo Costa Ruga
*           vmp - Victor Meira Pinto
*
*  $HA Histórico de evolução:
*     Versão    Autor    Data          Observações
*       1.0       awv      22/06         Criação do arquivo Partida.c e implementacao de funções
*       1.1       vmp      27/06         Implementacao de funções
*       1.2       bcr      28/06         Implementacao de funções
*       1.3       awv      29/06         Revisão do código
*
***************************************************************************/

#define PARTIDA_OWN
#include "LISTA.H"
#include "BARALHO.H"
#include "MESA.H"
#include "PARTIDA.H"
#include "INTERFACE.H"
#include "glut.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define K 13
#define Q 12
#define J 11
#define A 1
#define PAUS 1
#define COPAS 2
#define ESPADAS 3
#define OUROS 4
#define MAX_JOGADORES 6
#define TRUE 1
#define FALSE 0
#undef PARTIDA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: PAR Descritor de um jogador
*
*  $ED Descrição do tipo
*     O jogador tem um grupo e um nome que o identifica.
*
***********************************************************************/

typedef struct tgJogador {

    int grupo ;
    char nome[50] ;

} PAR_tpJogador ;

/***********************************************************************
*
*  $TC Tipo de dados: PAR Descritor de uma partida
*
*  $ED Descrição do tipo
*     A partida é uma lista das cartas dos jogadores, um vetor de informações 
*     sobre os jogadores, um ponteiro para a mesa, um ponteiro para o baralho
*     e também a contagem da pontuação de cada grupo.
*
***********************************************************************/

typedef struct tgPartida {

	LIS_tppLista cartasDosJogadores ;
	PAR_tpJogador * infoDosJogadores ;
	MES_tppMesa pMesa ;
	BAR_tppBaralho pBaralho ;
	int pontuacaoDoGrupo[2] ;

} PAR_tpPartida ;

extern char rodadaFlag ;

/***** Protótipos das variáveis encapuladas no módulo *****/

int grupoGanhador = 0 ;

int nJogadores = MAX_JOGADORES ;

static PAR_tpPartida jogoDeTruco ;

static int pontuacaoDaRodada[2] ;

static BAR_tppCarta pCartaManilhaAtual ;

int jogadorCorrente ;

static int primeiroJogadorDaMao = 0 ;

int valorApostaCorrente = 1 ;

MES_tppMesa pMesa ;

static int grupoGanhadorDaRodada[3] ;

/***** Protótipos das funções encapuladas no módulo *****/

static char PAR_ConverterValor ( int valorInt ) ;

static char * PAR_ConverterNaipe ( int naipeInt ) ;

static char * PAR_ObterNomeJogador( int jogadorId ) ;

void *  PAR_ObterMaoJogador( int jogadorId ) ;

static void PAR_AtualizarJogadorCorrente( void ) ;

static void PAR_ExibirAposta( int valorApostaCorrente ) ;

static void PAR_ExibirManilha( void ) ;

static void PAR_ExibirMesa( void ) ;

static void PAR_ExibirCartas( int jogadorId , int rodadaId ) ;

static int PAR_AtualizarPontuacao( int grupoId , int pontuacao ) ;

static int PAR_IniciarAposta( int grupoId , int jogadorId ) ;

int PAR_IniciarRodada( void ) ;

int PAR_IniciarMao( void ) ;

/***********************************************************************
*  Função: PAR Criar Partida
***********************************************************************/

PAR_tpCondRet PAR_CriarPartida ( int numJogadores )
{
	int i ;
    char nome[50] ;

	if ( numJogadores != 2 && numJogadores != 4 && numJogadores != 6 )
    {
        return PAR_CondRetNumJogadoresInvalido ;
    } /* if */

	nJogadores = numJogadores ;

	jogoDeTruco.infoDosJogadores = ( PAR_tpJogador *)malloc( numJogadores * sizeof( PAR_tpJogador )) ;

	if ( jogoDeTruco.infoDosJogadores == NULL )
	{
		return PAR_CondRetFaltouMemoria ;
	} /* if */

    jogoDeTruco.cartasDosJogadores = LIS_CriarLista( LIS_DestruirLista ) ;

    if ( jogoDeTruco.cartasDosJogadores == NULL )
    {
        return PAR_CondRetFaltouMemoria ;
    } /* if */

    for ( i = 0 ; i < numJogadores ; i++ )
    {
        jogoDeTruco.infoDosJogadores[i].grupo = (i % 2) + 1 ;

        printf( "Digite o nome do jogador %d do grupo %d\n" , i / 2 + 1 , (i % 2) + 1 ) ;
        scanf( "%s" , nome ) ;
        strcpy( jogoDeTruco.infoDosJogadores[i].nome , nome ) ;

		LIS_InserirElementoApos( jogoDeTruco.cartasDosJogadores , LIS_CriarLista( BAR_DestruirCarta ) ) ;
		IrFinalLista( jogoDeTruco.cartasDosJogadores ) ;
    } /* for */

    IrInicioLista( jogoDeTruco.cartasDosJogadores ) ;

	jogoDeTruco.pMesa = MES_CriarMesa( numJogadores ) ;
	jogoDeTruco.pBaralho = BAR_CriarBaralho( ) ;

	pMesa = jogoDeTruco.pMesa ;

	jogoDeTruco.pontuacaoDoGrupo[0] = 0 ;
	jogoDeTruco.pontuacaoDoGrupo[1] = 0 ;

	jogadorCorrente = 0 ;

	return PAR_CondRetOk ;
    /* Fim função: PAR Criar Partida */
}

/***********************************************************************
 *  Função: PAR Iniciar Partida
 ***********************************************************************/

void PAR_IniciarPartida ( void )
{
	char resposta ;

	jogoDeTruco.pontuacaoDoGrupo[0] = 0 ;
	jogoDeTruco.pontuacaoDoGrupo[1] = 0 ;

	glutMainLoop( ) ;

//	while ( grupoGanhador == 0 )
//	{
//		grupoGanhador = PAR_IniciarMao( ) ;
//	} /* while */
	/*
	printf( "Parabens, o grupo %d eh o vencedor!\n" , grupoGanhador ) ;
	printf( "Desejas jogar novamente?\n" ) ;
	printf( "'s' para sim e 'n' para nao: " ) ;
	scanf( " %c" , &resposta ) ;

	while ( resposta != 'n' && resposta != 's' )
	{
		printf( "Resposta invalida. Digite 's' para sim e 'n' para nao: " ) ;
		scanf( " %c" , &resposta ) ;
	} /* while */
	/*
	if ( resposta == 'n' )
	{
		return ;
	} /* if */

	PAR_IniciarPartida( ) ;
}

/***********************************************************************
 *  Função: PAR Destruir Partida
 ***********************************************************************/

void PAR_DestruirPartida ( void )
{
	IrInicioLista( jogoDeTruco.cartasDosJogadores ) ;

	while ( LIS_ExcluirElemento( jogoDeTruco.cartasDosJogadores ) != LIS_CondRetListaVazia ) ;
	 /* while */

    LIS_DestruirLista( jogoDeTruco.cartasDosJogadores ) ;

	free( jogoDeTruco.infoDosJogadores ) ;

	MES_DestruirMesa( jogoDeTruco.pMesa ) ;
	BAR_DestruirBaralho( jogoDeTruco.pBaralho ) ;
    
}   /* Fim função: PAR Destruir Carta */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: PAR  -Converter valor
*
*  $ED Descrição da função
*     Retorna o valor da carta em um char dado um valor em int.
*
***********************************************************************/

char PAR_ConverterValor ( int valorInt )
{
	char valorChar ;

    switch ( valorInt )
    {
        case A:
            valorChar = 'A' ;
            break ;
        case J:
            valorChar = 'J' ;
            break ;
        case Q:
            valorChar = 'Q' ;
            break ;
		case K:
            valorChar = 'K' ;
            break ;
        default:
            valorChar = valorInt + '0' ;
            break ;
    } /* switch */

    return valorChar ;

}    /* Fim função: PAR Converter Valor */

/***********************************************************************
*
*  $FC Função: PAR  -Converter naipe
*
*  $ED Descrição da função
*     Retorna o naipe da carta em uma string dado um naipe em int.
*
***********************************************************************/

char * PAR_ConverterNaipe ( int naipeInt )
{
	char * naipeString ;

    switch ( naipeInt )
    {
        case PAUS:
            naipeString = "PAUS" ;
            break ;
        case COPAS:
            naipeString = "COPAS" ;
            break ;
        case ESPADAS:
            naipeString = "ESPADAS" ;
            break ;
		case OUROS:
            naipeString = "OUROS" ;
            break ;
        default:
            return NULL ;
    } /* switch */

    return naipeString ;

}    /* Fim função: PAR Converter Naipe */

/***********************************************************************
*
*  $FC Função: PAR  -Obter Nome Jogador
*
*  $ED Descrição da função
*     Retorna o nome do jogador em uma string dado seu ID.
*
***********************************************************************/

char * PAR_ObterNomeJogador( int jogadorId )
{
	return jogoDeTruco.infoDosJogadores[jogadorId].nome ;
	/* Fim função: PAR Obter Nome Jogador */
}

/***********************************************************************
*
*  $FC Função: PAR  -Obter Mao Jogador
*
*  $ED Descrição da função
*     Retorna a lista de cartas na mao de um jogador dado seu ID.
*
***********************************************************************/

void * PAR_ObterMaoJogador( int jogadorId )
{
	LIS_tppLista pMaoJogador ;

	IrInicioLista( jogoDeTruco.cartasDosJogadores ) ;
	LIS_AvancarElementoCorrente( jogoDeTruco.cartasDosJogadores , jogadorId ) ;

	pMaoJogador = LIS_ObterValor( jogoDeTruco.cartasDosJogadores ) ;
	IrInicioLista( pMaoJogador ) ;
	IrInicioLista( jogoDeTruco.cartasDosJogadores ) ;

	return pMaoJogador ;
	/* Fim função: PAR Obter Mao Jogador */
}

/***********************************************************************
*
*  $FC Função: PAR  -Atualizar Jogador Corrente
*
*  $ED Descrição da função
*     Atualiza qual é o jogador corrente.
*
***********************************************************************/

void PAR_AtualizarJogadorCorrente( void )
{
	if ( jogadorCorrente < nJogadores - 1 )
	{
		jogadorCorrente++ ;
	}
	else
	{
		jogadorCorrente = 0 ;
	}/* if */

}/* Fim função: PAR Atualizar Jogador Corrente */

/***********************************************************************
*
*  $FC Função: PAR  -Exibir Aposta
*
*  $ED Descrição da função
*     Exibe o valor da aposta atual.
*
***********************************************************************/

void PAR_ExibirAposta( int valorApostaCorrente )
{
	printf( "\nA aposta atual vale %d\n" , valorApostaCorrente ) ;
	/* Fim função: PAR Exibir Aposta */
}

/***********************************************************************
*
*  $FC Função: PAR  -Exibir Manilha
*
*  $ED Descrição da função
*     Exibe qual é o valor e o naipe da manilha.
*
***********************************************************************/

void PAR_ExibirManilha( void )
{
	int valor ;
	int naipe ;

	BAR_ObterInfo( pCartaManilhaAtual , &valor , &naipe ) ;
	printf( "A manilha da mao atual eh %c de %s.\n\n" , PAR_ConverterValor( valor ) , PAR_ConverterNaipe( naipe ) ) ;
	/* Fim função: PAR Exibir Manilha */
}

/***********************************************************************
*
*  $FC Função: PAR  -Exibir Mesa
*
*  $ED Descrição da função
*     Exibe quais cartas que já foram jogadas na mesa.
*
***********************************************************************/

void PAR_ExibirMesa( void )
{
	int i ;
	int valor ;
	int naipe ;

	for ( i = 0 ; i < nJogadores ; i++ )
	{
		if ( MES_ObterCarta( jogoDeTruco.pMesa , i , &valor , &naipe ) == MES_CondRetOk )
		{
			printf( "Carta de %s na mesa: --- " , PAR_ObterNomeJogador( i ) ) ;
			printf( "%c de %s\n" , PAR_ConverterValor( valor ) , PAR_ConverterNaipe( naipe ) ) ;
		} /* if */
	} /* for */

	/* Fim função: PAR Exibir Mesa */
}

/***********************************************************************
*
*  $FC Função: PAR  -Exibir Cartas
*
*  $ED Descrição da função
*     Exibe as cartas na mao de um jogador dado seu ID e o ID da rodada.
*
***********************************************************************/

void PAR_ExibirCartas( int jogadorId , int rodadaId )
{
	int i ;
	int valorDaCarta ;
	int naipeDaCarta ;

	LIS_tppLista pCartasDoJogador ;
	BAR_tppCarta pCarta ;

	pCartasDoJogador = PAR_ObterMaoJogador( jogadorId ) ;

	printf( "Cartas de %s:\n" , PAR_ObterNomeJogador( jogadorId ) ) ;

	i = 0 ;

	do
	{
		pCarta = LIS_ObterValor( pCartasDoJogador ) ;

		BAR_ObterInfo( pCarta , &valorDaCarta , &naipeDaCarta ) ;

		printf( "Carta numero %d: --- " , i + 1 ) ;
		printf( "%c de %s\n" , PAR_ConverterValor( valorDaCarta ) , PAR_ConverterNaipe( naipeDaCarta ) ) ;

		i++ ;
	}
	while ( LIS_AvancarElementoCorrente( pCartasDoJogador , 1 ) == LIS_CondRetOK ) ;
	/* while */
	
	printf( "\n" ) ;

	IrInicioLista( pCartasDoJogador ) ;
	/* Fim função: PAR Exibir Cartas */
}

/***********************************************************************
*
*  $FC Função: PAR  -Atualizar Pontuacao
*
*  $ED Descrição da função
*     Retorna o ID do grupo vencedor da partida, caso haja um, e atualiza
*     sua pontuação total dado seu grupo ID e sua pontuação ganhada pela mão.
*     Caso não haja vencedor da partida, retorna zero.
*
***********************************************************************/

int PAR_AtualizarPontuacao( int grupoId , int pontuacao )
{
	printf( "O grupo %d ganhou %d pontos nesta mao!\n" , grupoId , pontuacao ) ;
	jogoDeTruco.pontuacaoDoGrupo[ grupoId - 1 ] += pontuacao ;

	printf( "Pontuacao do grupo 1: %d pontos\n" , jogoDeTruco.pontuacaoDoGrupo[0] ) ;
	printf( "Pontuacao do grupo 2: %d pontos\n" , jogoDeTruco.pontuacaoDoGrupo[1] ) ;

	if ( jogoDeTruco.pontuacaoDoGrupo[ grupoId - 1 ] >= 12 )
	{
		return grupoId ;
	} /* if */

	return 0 ;
	/* Fim função: PAR Atualizar Pontuacao */
}

/***********************************************************************
*
*  $FC Função: PAR  -Iniciar Aposta
*
*  $ED Descrição da função
*     Inicia uma aposta e retorna zero se o jogador corrente decide não
*     aumentar a aposta ou um número que especifica quem ganhou a aposta
*     e por quantos pontos, dados ID do grupo, ID do jogador corrente,
*     ID da rodada e um ponteiro para a aposta corrente.
*
***********************************************************************/

int PAR_IniciarAposta( int grupoId , int jogadorId )
{
	int i ;
	char resposta ;

	printf( "Jogador %s, desejas aumentar uma aposta? A aposta atual vale %d\n" , PAR_ObterNomeJogador( jogadorId ) , valorApostaCorrente ) ;
	printf( "'s' para sim e 'n' para nao: " ) ;
	scanf( " %c" , &resposta ) ;

	while ( resposta != 'n' && resposta != 's' )
	{
		printf( "Resposta invalida. Digite 's' para sim e 'n' para nao: " ) ;
		scanf( " %c" , &resposta ) ;
	} /* while */

	if ( resposta == 'n' )
	{
		return 0 ;
	} /* if */

	//Walk through players of the same team
	aposta:
	for ( i = 0 ; i < nJogadores ; i++ , PAR_AtualizarJogadorCorrente( ) )
	{
		if ( jogadorCorrente == jogadorId )
		{
			continue ;
		} /* if */

		if ( jogoDeTruco.infoDosJogadores[ jogadorCorrente ].grupo == grupoId )
		{
			printf( "Jogador %s, um jogador do seu grupo aumentou a aposta. Desejas aceitar a aposta? A aposta atual vale %d\n" , PAR_ObterNomeJogador( jogadorCorrente ) , valorApostaCorrente ) ;
			printf( "'s' para sim, 'n' para nao:" ) ;
			scanf( " %c" , &resposta ) ;

			while ( resposta != 'n' && resposta != 's')
			{
				printf("Resposta invalida. Digite 's' para sim, e 'n' para nao: ") ;
				scanf( " %c" , &resposta ) ;
			} /* while */

			if ( resposta == 'n' )
			{
				return 0 ;
			} /* if */
		} /* if */
	}

    // Walk through players of the other team
	for ( i = 0 ; i < nJogadores ; i++ , PAR_AtualizarJogadorCorrente( ) )
	{
		if ( jogadorCorrente == jogadorId )
		{
			continue ;
		} /* if */

		if ( jogoDeTruco.infoDosJogadores[ jogadorCorrente ].grupo != grupoId )
		{
			printf( "Jogador %s, desejas aceitar a aposta? A aposta atual vale %d\n" , PAR_ObterNomeJogador( jogadorCorrente ) , valorApostaCorrente ) ;
			printf( "'s' para sim, 'n' para nao e 'a' para aumentar a aposta: " ) ;
			scanf( " %c" , &resposta ) ;

			while ( resposta != 'n' && resposta != 's' && resposta != 'a' )
			{
				printf("Resposta invalida. Digite 's' para sim, 'n' para nao e 'a' para aumentar a aposta: ") ;
				scanf( " %c" , &resposta ) ;
			} /* while */

			if ( resposta == 's' )
			{
				continue ;
			} /* if */

			//The group that called the bet wins
			if ( resposta == 'n' )
			{
				return grupoId ;
			} /* if */

			//If here, the person wanted to up the ante
			if ( ( valorApostaCorrente ) == 12 )
			{
				printf( "Nao eh possivel aumentar mais a aposta.\n" ) ;
				printf( "Jogador %s, desejas aceitar a aposta? A aposta atual vale %d\n" , PAR_ObterNomeJogador( jogadorCorrente ) , valorApostaCorrente ) ;
				printf( "'s' para sim e 'n' para nao: " ) ;
				scanf( "%c" , &resposta ) ;

				while ( resposta != 'n' && resposta != 's' )
				{
					printf("Resposta invalida. Digite 's' para sim e 'n' para nao: ") ;
					scanf( " %c" , &resposta ) ;
				} /* while */

				if ( resposta == 's' )
				{
					continue ;
				} /* if */

				//The group that called the bet wins
				if ( resposta == 'n' )
				{
					return grupoId ;
				} /* if */
			}
			else
			{
				if ( ( valorApostaCorrente ) == 1 )
				{
					( valorApostaCorrente ) += 2 ;
				}
				else
				{
					( valorApostaCorrente ) += 3 ;
				} /* if */

				jogadorId = jogadorCorrente ;
				grupoId = jogoDeTruco.infoDosJogadores[ jogadorCorrente ].grupo ;
				goto aposta ;
			} /* if */
		}
	}

	//If here, every one accepted the bet but didn't up the ante

	return 0 ;
	/* Fim função: PAR Iniciar Aposta */
}

/***********************************************************************
*
*  $FC Função: PAR  -Iniciar Rodada
*
*  $ED Descrição da função
*     Inicia uma rodada e retorna o time ganhador da rodada dado o ID da
*     rodada e o valor da aposta corrente.
*
***********************************************************************/

int PAR_IniciarRodada( void )
{
	int i ;

	IrInicioLista( jogoDeTruco.cartasDosJogadores ) ;

	for ( i = 0 ; i < 3 ; i++ )
	{
		grupoGanhadorDaRodada[ i ] = 0 ;
	}

	return 0 ;
}

int PAR_FinalizarRodada( void )
{
	int timeGanhador ;

	if ( MES_IdentificarGanhador( jogoDeTruco.pMesa , &timeGanhador ) != MES_CondRetOk )
	{
		return -1 ;
	} /* if */

	MES_EsvaziarMesa( jogoDeTruco.pMesa , jogadorCorrente ) ;

	if ( timeGanhador != 0 )
	{
		printf( "O grupo %d ganhou esta rodada!\n\n" , timeGanhador ) ;
	}
	else
	{
		printf( "Houve um empate nesta rodada!\n\n" ) ;
	} /* if */

	rodadaFlag = FALSE ;

	return timeGanhador ;
	/* Fim função: PAR Iniciar Rodada */
}

int PAR_AtualizarRodada( void )
{
	int resultadoDaAposta ;
	int timeGanhador ;
	int cartaId ;

	BAR_tppCarta pCarta ;
	LIS_tppLista pMaoJogador ;

	static int rodadaId = 1 ;
	static int jogadas = 0 ;

	PAR_ExibirMesa( ) ;
	PAR_ExibirCartas( jogadorCorrente , rodadaId ) ;
	resultadoDaAposta = PAR_IniciarAposta( jogoDeTruco.infoDosJogadores[jogadorCorrente].grupo , jogadorCorrente ) ;

	printf("RODADA ID: %d\n", rodadaId);

	if ( resultadoDaAposta != 0 )
	{
		MES_EsvaziarMesa( jogoDeTruco.pMesa , jogadorCorrente ) ;

		printf( "O grupo %d ganhou esta rodada!\n\n" , timeGanhador ) ;
		timeGanhador = resultadoDaAposta + 2 ;
		rodadaId = 0 ;

		return timeGanhador ;
	} /* if */

	printf( "Jogador %s, escolha a carta que desejas jogar: " , PAR_ObterNomeJogador( jogadorCorrente ) ) ;
	scanf( "%d" , &cartaId ) ;

	while ( cartaId <= 0 || cartaId >= ( 4 - rodadaId + 1 ) )
	{
		printf( "Carta invalida. Escolha uma carta valida: " ) ;
		scanf( "%d" , &cartaId ) ;
	} /* while */

	printf( "\n" ) ;

	pMaoJogador = PAR_ObterMaoJogador( jogadorCorrente ) ;

	LIS_AvancarElementoCorrente( pMaoJogador , cartaId - 1 ) ;

	pCarta = LIS_ObterValor( pMaoJogador ) ;

	if ( MES_JogarCarta( jogoDeTruco.pMesa , pCarta , jogadorCorrente ) != MES_CondRetOk )
	{
		return -1 ;
	} /* if */

	LIS_ExcluirElemento( pMaoJogador ) ;
	IrInicioLista( pMaoJogador ) ;

	PAR_AtualizarJogadorCorrente( ) ;

	if ( rodadaId <= 3 )
	{
		grupoGanhadorDaRodada[ rodadaId - 1 ] += PAR_FinalizarRodada( ) ;

		jogadas++ ;
		rodadaId += jogadas / nJogadores ;

		if ( jogadas == nJogadores )
		{
			jogadas = 0 ;

			if ( rodadaId == 3 )
			{
				rodadaId = 0 ;
				return PAR_FinalizarMao( ) ;
			}
		}
	}

	return 0 ;
}

/***********************************************************************
*
*  $FC Função: PAR  -Iniciar Mao
*
*  $ED Descrição da função
*     Inicia uma mão e retorna o valor retornado pela função
*     PAR_AtualizarPontuacao dado o ID da rodada e o valor da aposta
*     corrente.
*
***********************************************************************/

int PAR_IniciarMao( void )
{
	int i ;
	int j ;
//	int grupoGanhadorDaMao ;
	int numRodadasGrupo1 ;
	int numRodadasGrupo2 ;

	BAR_tppCarta * pCartasDosJogadores ;
	LIS_tppLista pCartasDoJogador ;

	pCartaManilhaAtual = BAR_CriarCarta( A , PAUS ) ;
	valorApostaCorrente = 1 ;

	pCartasDosJogadores = ( BAR_tppCarta *)malloc( nJogadores * 3 * sizeof( BAR_tppCarta ) ) ;

	if ( pCartasDosJogadores == NULL )
	{
		return -1 ;
	} /* if */

	printf( "\nUma nova mao foi iniciada.\n" ) ;

	BAR_Embaralhar( jogoDeTruco.pBaralho ) ;
	BAR_PuxarCarta( jogoDeTruco.pBaralho , pCartaManilhaAtual ) ;

	MES_DefinirManilha( jogoDeTruco.pMesa , pCartaManilhaAtual ) ;

	PAR_ExibirManilha( ) ;

	for ( i = 0 ; i < nJogadores * 3 ; i++ )
	{
		pCartasDosJogadores[i] = BAR_CriarCarta( A , PAUS ) ;
	} /* for */

	for ( i = 0 ; i < nJogadores ; i++ )
	{
		pCartasDoJogador = LIS_ObterValor( jogoDeTruco.cartasDosJogadores ) ;
		
		for ( j = 0 ; j < 3 ; j++ )
		{
			BAR_PuxarCarta( jogoDeTruco.pBaralho , pCartasDosJogadores[ ( i * 3 ) + j ] ) ;
			LIS_InserirElementoApos( pCartasDoJogador , pCartasDosJogadores[ ( i * 3 ) + j ] ) ;
		} /* for */

		IrInicioLista( pCartasDoJogador ) ;
		LIS_AvancarElementoCorrente( jogoDeTruco.cartasDosJogadores , 1 ) ;
	} /* for */

	free( pCartasDosJogadores ) ;

	IrInicioLista( jogoDeTruco.cartasDosJogadores ) ;

//	grupoGanhadorDaMao = 0 ;

	return 0 ;
}
	
int PAR_FinalizarMao( void )
{
	int i ;
	int j ;
//	int grupoGanhadorDaRodada[3] ;
	int grupoGanhadorDaMao ;
	int numRodadasGrupo1 ;
	int numRodadasGrupo2 ;

	grupoGanhadorDaMao = 0 ;

	for ( i = 0 ; i < 3 ; i ++ )
	{
//		grupoGanhadorDaRodada[i] = PAR_IniciarRodada( i + 1 , &valorApostaCorrente ) ;
		
		if ( grupoGanhadorDaRodada[i] > 2 )
		{
			grupoGanhadorDaMao = grupoGanhadorDaRodada[i] - 2 ;
			break ;
		} /* if */
	} /* for */

	if ( grupoGanhadorDaMao == 0 )
	{
		if ( grupoGanhadorDaRodada[0] == 0 && grupoGanhadorDaRodada[1] == 0 && grupoGanhadorDaRodada[2] == 0 )
		{
			return 0 ;
		}
		else if ( grupoGanhadorDaRodada[0] == 0 && grupoGanhadorDaRodada[1] == 0 )
		{
			grupoGanhadorDaMao = grupoGanhadorDaRodada[2] ;
		}
		else if ( grupoGanhadorDaRodada[0] == 0 )
		{
			grupoGanhadorDaMao = grupoGanhadorDaRodada[1] ;
		}
		else if ( grupoGanhadorDaRodada[1] == 0 || grupoGanhadorDaRodada[2] == 0 )
		{
			grupoGanhadorDaMao = grupoGanhadorDaRodada[0] ;
		}
		else
		{
			numRodadasGrupo1 = 0 ;
			numRodadasGrupo2 = 0 ;

			for ( i = 0 ; i < 3 ; i++ )
			{
				if ( grupoGanhadorDaRodada[i] == 1 )
				{
					numRodadasGrupo1++ ;
				}
				else
				{
					numRodadasGrupo2++ ;
				} /* if */
			} /* for */

			grupoGanhadorDaMao = ( numRodadasGrupo1 > numRodadasGrupo2 ) ? 1 : 2 ;
		} /* if */
	} /* if */

	if ( primeiroJogadorDaMao < nJogadores - 1 )
	{
		primeiroJogadorDaMao++ ;
	}
	else
	{
		primeiroJogadorDaMao = 0 ;
	} /* if */

	MES_EsvaziarMesa( jogoDeTruco.pMesa , primeiroJogadorDaMao ) ;

	jogadorCorrente = primeiroJogadorDaMao ;

	

	return PAR_AtualizarPontuacao( grupoGanhadorDaMao , valorApostaCorrente ) ;
	/* Fim função: PAR Iniciar Mao */
}

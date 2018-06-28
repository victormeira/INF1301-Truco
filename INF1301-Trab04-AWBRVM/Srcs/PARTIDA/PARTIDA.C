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
*       1.0       bcr      15/04         Criação do arquivo Partida.c
*       1.1       vmp      17/04         Implementacao de funções
*       1.2       awv      19/04         Revisão do código
*       1.2       bcr      19/04         Revisão do código
*       1.2       vmp      19/04         Revisão do código
*       1.3       bcr      25/04         Revisão do código
*       1.4       awv      30/04         Revisão do código
*       1.5       vmp      03/05         Revisão do código
*       1.6       bcr      03/05         Revisão do código
*
***************************************************************************/

#define PARTIDA_OWN
#include "LISTA.H"
#include "BARALHO.H"
#include "MESA.H"
#include "PARTIDA.H"
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
#undef PARTIDA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: PAR Descritor de uma partida
*
*  $ED Descrição do tipo
*     O deck de cartas (o baralho em si) é uma lista de cartas e 
*     também a um indicativo de quantas cartas o deck possui.
*
***********************************************************************/

typedef struct tgJogador {

    int grupo ;
    char nome[50] ;

} PAR_tpJogador ;

typedef struct tgPartida {

	LIS_tppLista cartasDosJogadores ;
	PAR_tpJogador * infoDosJogadores ;
	MES_tppMesa pMesa ;
	BAR_tppBaralho pBaralho ;
	int pontuacaoDoGrupo[2] ;

} PAR_tpPartida ;

PAR_tpPartida jogoDeTruco ;

static int nJogadores = MAX_JOGADORES ;
static int pontuacaoDaRodada[2] ;

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
        strcpy( nome , jogoDeTruco.infoDosJogadores[i].nome ) ;

		LIS_InserirElementoApos( jogoDeTruco.cartasDosJogadores , LIS_CriarLista( BAR_DestruirCarta ) ) ;
		IrFinalLista( jogoDeTruco.cartasDosJogadores ) ;
    }

    IrInicioLista( jogoDeTruco.cartasDosJogadores ) ;

	jogoDeTruco.pMesa = MES_CriarMesa( numJogadores ) ;
	jogoDeTruco.pBaralho = BAR_CriarBaralho( ) ;

	jogoDeTruco.pontuacaoDoGrupo[0] = 0 ;
	jogoDeTruco.pontuacaoDoGrupo[1] = 0 ;

	return PAR_CondRetOk ;
    /* Fim função: PAR Criar Partida */
}

/***********************************************************************
 *  Função: PAR Iniciar Partida
 ***********************************************************************/

void PAR_IniciarPartida ( void )
{
	int grupoGanhador ;
	char resposta ;

	jogoDeTruco.pontuacaoDoGrupo[0] = 0 ;
	jogoDeTruco.pontuacaoDoGrupo[1] = 0 ;

	grupoGanhador = PAR_IniciarMao( ) ;

	while ( grupoGanhador == 0 )
	{
		grupoGanhador = PAR_IniciarMao( ) ;
	}

	printf( "Parabens, o grupo %d eh o vencedor!\n" , grupoGanhador ) ;
	printf( "Desejas jogar novamente?" ) ;
	printf( "'s' para sim e 'n' para nao: " ) ;
	scanf( "%c" , &resposta ) ;

	if ( resposta == 'n' )
	{
		return ;
	}

	PAR_IniciarPartida( ) ;
}

/***********************************************************************
 *  Função: PAR Destruir Partida
 ***********************************************************************/

void PAR_DestruirPartida ( void )
{
	IrInicioLista( jogoDeTruco.cartasDosJogadores ) ;

	while ( LIS_ExcluirElemento( jogoDeTruco.cartasDosJogadores ) != LIS_CondRetListaVazia );

    LIS_DestruirLista( jogoDeTruco.cartasDosJogadores ) ;

	free( jogoDeTruco.infoDosJogadores ) ;

	MES_DestruirMesa( jogoDeTruco.pMesa ) ;
	BAR_DestruirBaralho( jogoDeTruco.pBaralho ) ;
    
}   /* Fim função: PAR Destruir Carta */

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: PAR  -Retorna Numero Aleatorio
*
*  $ED Descrição da função
*     Retorna um numero do tipo int aleatorio de 0 ao  
*     parametro int max.
*
***********************************************************************/

int PAR_RetornaNumAleatorio ( int max )
{
    return rand () %max ;

}   /* Fim função: PAR Retorna Número Aleatório */


/***********************************************************************
*
*  $FC Função: PAR  -Converte valor
*
*  $ED Descrição da função
*     Retorna o numero equivalente ao valor da carta para facilitar
*     na comparacao.
*
***********************************************************************/

int PAR_converteValor ( int val )
{
    // 3 2 A K J Q 7 6 5 4
    // O valor de ordem diferente se converte em um valor de facil comparação. */
    switch ( val )
    {
        case 3:
            val = 16 ;
            break ;
        case 2:
            val = 15 ;
            break ;
        case A:
            val = 14 ;
            break ;
        case J:
            val = 12 ;
            break ;
        case Q:
            val = 11 ;
            break ;
        default:
            val = val ;
            break ;               
    } /* switch */

    return val ;

}    /* Fim função: PAR Converter Valor */

// jogadorId vai de 0 a 5
// qualquer coisa muda

static char * PAR_ObterNomeJogador( int jogadorId )
{
	return jogoDeTruco.infoDosJogadores[jogadorId].nome ;
}

static LIS_tppLista PAR_ObterMaoJogador( int jogadorId )
{
	LIS_tppLista pMaoJogador ;

	IrInicioLista( jogoDeTruco.cartasDosJogadores ) ;
	LIS_AvancarElementoCorrente( jogoDeTruco.cartasDosJogadores , jogadorId ) ;

	pMaoJogador = LIS_ObterValor( jogoDeTruco.cartasDosJogadores ) ;
	IrInicioLista( pMaoJogador ) ;

	return pMaoJogador ;
}

static int PAR_AtualizarPontuacao( int grupoId , int pontuacao )
{
	jogoDeTruco.pontuacaoDoGrupo[ grupoId - 1 ] += pontuacao ;

	if ( jogoDeTruco.pontuacaoDoGrupo[ grupoId - 1 ] >= 12 )
	{
		return grupoId ;
	}

	return 0 ;
}

static int PAR_IniciarMao( void )
{
	int i ;
	int j ;
	int valorApostaCorrente ;
	int grupoGanhador[3] ;
	int grupoGanhadorDaMao ;
	int numRodadasGrupo1 ;
	int numRodadasGrupo2 ;

	BAR_tppCarta pCarta ;
	LIS_tppLista pCartasDoJogador ;

	valorApostaCorrente = 1 ;

	BAR_Embaralhar( jogoDeTruco.pBaralho ) ;
	BAR_PuxarCarta( jogoDeTruco.pBaralho , pCarta ) ;

	MES_DefinirManilha( jogoDeTruco.pMesa , pCarta ) ;

	for ( i = 0 ; i < nJogadores ; i++ )
	{
		pCartasDoJogador = LIS_ObterValor( jogoDeTruco.cartasDosJogadores ) ;
		
		for ( j = 0 ; j < 3 ; j++ )
		{
			BAR_PuxarCarta( jogoDeTruco.pBaralho , pCarta ) ;
			LIS_InserirElementoApos( pCartasDoJogador , pCarta ) ;
		}

		LIS_AvancarElementoCorrente( jogoDeTruco.cartasDosJogadores , 1 ) ;
	}

	IrInicioLista( jogoDeTruco.cartasDosJogadores ) ;

	for ( i = 0 ; i < 3 ; i ++ )
	{
		grupoGanhador[i] = PAR_IniciarRodada( i + 1 , &valorApostaCorrente ) ;
		
		if ( grupoGanhador[i] > 2 )
		{
			grupoGanhadorDaMao = grupoGanhador[i] - 2 ;
			break ;
		}
	}

	if ( grupoGanhador[0] == 0 && grupoGanhador[1] == 0 && grupoGanhador[2] == 0 )
	{
		// NINGUEM GANHA NADA
		return 0 ;
	}
	else if ( grupoGanhador[0] == 0 && grupoGanhador[1] == 0 )
	{
		grupoGanhadorDaMao = grupoGanhador[2] ;
	}
	else if ( grupoGanhador[0] == 0 )
	{
		grupoGanhadorDaMao = grupoGanhador[1] ;
	}
	else if ( grupoGanhador[1] == 0 || grupoGanhador[2] == 0 )
	{
		grupoGanhadorDaMao = grupoGanhador[0] ;
	}
	else
	{
		numRodadasGrupo1 = 0 ;
		numRodadasGrupo2 = 0 ;

		for ( i = 0 ; i < 3 ; i++ )
		{
			if ( grupoGanhador[i] == 1 )
			{
				numRodadasGrupo1++ ;
			}
			else
			{
				numRodadasGrupo2++ ;
			}
		}

		grupoGanhadorDaMao = (numRodadasGrupo1 > numRodadasGrupo2) ? 1 : 2 ;
	}

	return PAR_AtualizarPontuacao( grupoGanhadorDaMao , valorApostaCorrente ) ;
}

static int PAR_IniciarAposta( int grupoId , int * valorApostaCorrente )
{
	int i ;
	int proxJogador ;
	char resposta ;

	// POSSIVEIS FUNCOES DE EXIBICAO DE CARTA AQUI
	printf( "Desejas aumentar uma aposta? A aposta atual vale %d\n" , * valorApostaCorrente ) ;
	printf( "'s' para sim e 'n' para nao: " ) ;
	scanf( "%c" , &resposta ) ;

	if ( resposta == 'n' )
	{
		return 0 ;
	}

	for ( i = 0 ; i < nJogadores ; i++ )
	{
		proxJogador = ( 2 * i ) + grupoId ;
		// EXIBIR CARTAS DO JOGADOR TAL
		printf( "Desejas aceitar a aposta? A aposta atual vale %d\n" , * valorApostaCorrente ) ;
		printf( "'s' para sim, 'n' para nao e 'a' para aumentar a aposta: " ) ;
		scanf( "%c" , &resposta ) ;
		// TEM QUE TER O CASO EM QUE AUMENTA A APOSTA
		
		if ( resposta == 'n' )
		{
			return grupoId + 1 ;
		}
		else if ( resposta == 'a' )
		{
			if ( ( * valorApostaCorrente ) == 12 )
			{
				printf( "Nao eh possivel aumentar mais a aposta.\n" ) ;
				printf( "Desejas aceitar a aposta? A aposta atual vale %d\n" , * valorApostaCorrente ) ;
				printf( "'s' para sim e 'n' para nao: " ) ;
				scanf( "%c" , &resposta ) ;

				if ( resposta == 'n' )
				{
					return grupoId + 1 ;
				}
			}
			else
			{
				if ( ( * valorApostaCorrente ) == 1 )
				{
					( * valorApostaCorrente ) += 2 ;
				}
				else
				{
					( * valorApostaCorrente ) += 3 ;
				}

				return PAR_IniciarAposta( !grupoId , valorApostaCorrente ) ;
			}
		}
	}

	return -1 ;
}

static int PAR_IniciarRodada( int rodadaId , int * valorApostaCorrente )
{
	int i ;
	int cartaId ;
	int resultadoDaAposta ;
	int timeGanhador ;

	LIS_tppLista pMaoJogador ;
	BAR_tppCarta pCarta ;

	IrInicioLista( jogoDeTruco.cartasDosJogadores ) ;
	// POSSIVEL FUNCAO DE DECIDIR ORDEM

	for ( i = 0 ; i < nJogadores ; i++ )
	{
		// POSSIVEIS FUNCOES DE EXIBICAO DE CARTA AQUI
		resultadoDaAposta = PAR_IniciarAposta( jogoDeTruco.infoDosJogadores[i].grupo , valorApostaCorrente ) ;

		if ( resultadoDaAposta != 0 )
		{
			// ACABA A MAO
			timeGanhador = resultadoDaAposta + 2 ;
			return timeGanhador ;
		}

		printf( "Escolha a carta que desejas jogar\n" ) ;
		scanf( "%d" , &cartaId ) ;

		while ( cartaId <= 0 || cartaId >= ( 4 - rodadaId + 1 ) )
		{
			printf( "Carta invalida. Escolha uma carta valida.\n" ) ;
			scanf( "%d" , &cartaId ) ;
		}

		pMaoJogador = PAR_ObterMaoJogador( i ) ;

		LIS_AvancarElementoCorrente( pMaoJogador , cartaId - 1 ) ;

		pCarta = LIS_ObterValor( pMaoJogador ) ;

		MES_JogarCarta( jogoDeTruco.pMesa, pCarta , i ) ;

		LIS_ExcluirElemento( pMaoJogador ) ;
	}

	MES_IdentificarGanhador( jogoDeTruco.pMesa , &timeGanhador ) ;

	return timeGanhador ;
}

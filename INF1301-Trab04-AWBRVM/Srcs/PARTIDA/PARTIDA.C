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
static BAR_tppCarta pCartaManilhaAtual ;

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

	grupoGanhador = 0 ;

	while ( grupoGanhador == 0 )
	{
		grupoGanhador = PAR_IniciarMao( ) ;
	}

	printf( "Parabens, o grupo %d eh o vencedor!\n" , grupoGanhador ) ;
	printf( "Desejas jogar novamente?" ) ;
	printf( "'s' para sim e 'n' para nao: " ) ;
	scanf( " %c" , &resposta ) ;

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
*  $FC Função: PAR  -Converte valor
*
*  $ED Descrição da função
*     Retorna o numero equivalente ao valor da carta para facilitar
*     na comparacao.
*
***********************************************************************/

char PAR_converteValor ( int valorInt )
{
    // 3 2 A K J Q 7 6 5 4
    // O valor de ordem diferente se converte em um valor de facil comparação. */
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

char * PAR_converteNaipe ( int naipeInt )
{
    // 3 2 A K J Q 7 6 5 4
    // O valor de ordem diferente se converte em um valor de facil comparação. */
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

static void PAR_ExibirAposta( int valorApostaCorrente )
{
	printf( "\nA aposta atual vale %d\n" , valorApostaCorrente ) ;
}

static void PAR_ExibirManilha( void )
{
	int valor ;
	int naipe ;

	BAR_ObterInfo( pCartaManilhaAtual , &valor , &naipe ) ;
	printf( "\nA manilha da mao atual eh %c de %s.\n" , PAR_converteValor( valor ) , PAR_converteNaipe( naipe ) ) ;
}

static void PAR_ExibirMesa( void )
{
	int i ;
	int valor ;
	int naipe ;

	for ( i = 0 ; i < nJogadores ; i++ )
	{
		if ( MES_ObterCarta( jogoDeTruco.pMesa , i , &valor , &naipe ) == MES_CondRetOk )
		{
			printf( "Carta de %s na mesa: --- " , PAR_ObterNomeJogador( i ) ) ;
			printf( "%c de %s\n" , PAR_converteValor( valor ) , PAR_converteNaipe( naipe ) ) ;
		}
	}
}

static void PAR_ExibirCartas( int jogadorId , int rodadaId )
{
	int i ;
	int valorDaCarta ;
	int naipeDaCarta ;

	LIS_tppLista pCartasDoJogador ;
	BAR_tppCarta pCarta ;

//	IrInicioLista( jogoDeTruco.cartasDosJogadores ) ;
//	LIS_AvancarElementoCorrente( jogoDeTruco.cartasDosJogadores , jogadorId ) ;

//	pCartasDoJogador = LIS_ObterValor( jogoDeTruco.cartasDosJogadores ) ;
//	IrInicioLista( pCartasDoJogador ) ;

	pCartasDoJogador = PAR_ObterMaoJogador( jogadorId ) ;

	printf( "Cartas de %s\n" , PAR_ObterNomeJogador( jogadorId ) ) ;

	for ( i = 0 ; i < 4 - rodadaId ; i++ )
	{
		pCarta = LIS_ObterValor( pCartasDoJogador ) ;

		BAR_ObterInfo( pCarta , &valorDaCarta , &naipeDaCarta ) ;

		printf( "Carta numero %d: --- " , i + 1 ) ;
		printf( "%c de %s\n" , PAR_converteValor( valorDaCarta ) , PAR_converteNaipe( naipeDaCarta ) ) ;

		LIS_AvancarElementoCorrente( pCartasDoJogador , 1 ) ;
	}

	IrInicioLista( pCartasDoJogador ) ;
}

static int PAR_AtualizarPontuacao( int grupoId , int pontuacao )
{
	printf( "O grupo %d ganhou %d pontos nesta mao!\n" , grupoId , pontuacao ) ;

	jogoDeTruco.pontuacaoDoGrupo[ grupoId - 1 ] += pontuacao ;

	printf( "Pontuacao do grupo 1: %d pontos\n" , jogoDeTruco.pontuacaoDoGrupo[0] ) ;
	printf( "Pontuacao do grupo 2: %d pontos\n" , jogoDeTruco.pontuacaoDoGrupo[1] ) ;

	if ( jogoDeTruco.pontuacaoDoGrupo[ grupoId - 1 ] >= 12 )
	{
		return grupoId ;
	}

	return 0 ;
}

static int PAR_IniciarAposta( int grupoId , int jogadorId , int rodadaId , int * valorApostaCorrente )
{
	int i ;
	int proxJogador ;
	char resposta ;

	printf( "Desejas aumentar uma aposta? A aposta atual vale %d\n" , * valorApostaCorrente ) ;
	printf( "'s' para sim e 'n' para nao: " ) ;
	resposta = '0';
	while ( resposta != 's' || resposta != 'n' )
	{
		scanf( " %c" , &resposta ) ;
	}

	if ( resposta == 'n' )
	{
		return 0 ;
	}

	for ( i = 0 ; i < nJogadores ; i++ )
	{
		proxJogador = ( 2 * i ) + grupoId ;
		printf( "Desejas aceitar a aposta? A aposta atual vale %d\n" , * valorApostaCorrente ) ;
		printf( "'s' para sim, 'n' para nao e 'a' para aumentar a aposta: " ) ;
		scanf( " %c" , &resposta ) ;
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

				return PAR_IniciarAposta( !grupoId , i , rodadaId , valorApostaCorrente ) ;
			}
		}
	}

	return -1 ;
}

static int PAR_IniciarRodada( int rodadaId , int * valorApostaCorrente )
{
	int i ;
	static int j ;
	int cartaId ;
	int resultadoDaAposta ;
	int timeGanhador ;
	int valor;
	int naipe;

	LIS_tppLista pMaoJogador ;
	BAR_tppCarta pCarta ;
	BAR_tppCarta pCartas[18] ;

	j = 0;

	IrInicioLista( jogoDeTruco.cartasDosJogadores ) ;
	// POSSIVEL FUNCAO DE DECIDIR ORDEM

	for ( i = 0 ; i < nJogadores ; i++ )
	{
		PAR_ExibirMesa( ) ;
		PAR_ExibirCartas( i , rodadaId ) ;
		resultadoDaAposta = PAR_IniciarAposta( jogoDeTruco.infoDosJogadores[i].grupo , i , rodadaId , valorApostaCorrente ) ;

		if ( resultadoDaAposta != 0 )
		{
			// ACABA A MAO
			timeGanhador = resultadoDaAposta + 2 ;
			return timeGanhador ;
		}

		printf( "Escolha a carta que desejas jogar: " ) ;
		scanf( "%d" , &cartaId ) ;

		while ( cartaId <= 0 || cartaId >= ( 4 - rodadaId + 1 ) )
		{
			printf( "Carta invalida. Escolha uma carta valida.\n" ) ;
			scanf( "%d" , &cartaId ) ;
		}

		pMaoJogador = PAR_ObterMaoJogador( i ) ;

		LIS_AvancarElementoCorrente( pMaoJogador , cartaId - 1 ) ;

		if (i == 0){
		pCartas[j] = LIS_ObterValor( pMaoJogador ) ;

		MES_JogarCarta( jogoDeTruco.pMesa, pCartas[j] , i ) ;
		}else{
		pCartas[j+3] = LIS_ObterValor( pMaoJogador ) ;

		MES_JogarCarta( jogoDeTruco.pMesa, pCartas[j+3] , i ) ;
		}
		MES_ObterCarta( jogoDeTruco.pMesa , i , &valor , &naipe ) ;
//		printf("VALOR: %d --- NAIPE: %d\n", valor, naipe);

		LIS_ExcluirElemento( pMaoJogador ) ;
	}

	j++;

	MES_IdentificarGanhador( jogoDeTruco.pMesa , &timeGanhador ) ;

	printf( "O grupo %d ganhou esta rodada!\n" , timeGanhador ) ;

	return timeGanhador ;
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

	int naipeTeste ;
	int valorTeste ;

	BAR_tppCarta pCarta ;
	LIS_tppLista pCartasDoJogador ;
	BAR_tppCarta pCartas[6] ;

	pCarta = BAR_CriarCarta( A , PAUS ) ;
	valorApostaCorrente = 1 ;

	printf( "Uma nova mao foi iniciada.\n" ) ;

	BAR_Embaralhar( jogoDeTruco.pBaralho ) ;
	BAR_PuxarCarta( jogoDeTruco.pBaralho , pCarta ) ;

	MES_DefinirManilha( jogoDeTruco.pMesa , pCarta ) ;

	pCartaManilhaAtual = pCarta ;
	PAR_ExibirManilha( ) ;

	for(j=0; j<6;j++)
		pCartas[j] = BAR_CriarCarta( A , PAUS ) ;

	for ( i = 0 ; i < nJogadores ; i++ )
	{
		pCartasDoJogador = LIS_ObterValor( jogoDeTruco.cartasDosJogadores ) ;
		
		for ( j = 0 ; j < 3 ; j++ )
		{
			if (i == 0){
			BAR_PuxarCarta( jogoDeTruco.pBaralho , pCartas[j] ) ;
			BAR_ObterInfo( pCartas[j] , &valorTeste , &naipeTeste ) ;
//			printf("AQUI O VALOR %c E AQUI O NAIPE %s\n", PAR_converteValor(valorTeste), PAR_converteNaipe(naipeTeste));
			LIS_InserirElementoApos( pCartasDoJogador , pCartas[j] ) ;
			}else{
				BAR_PuxarCarta( jogoDeTruco.pBaralho , pCartas[j+3] ) ;
				BAR_ObterInfo( pCartas[j+3] , &valorTeste , &naipeTeste ) ;
//				printf("AQUI O VALOR %c E AQUI O NAIPE %s\n", PAR_converteValor(valorTeste), PAR_converteNaipe(naipeTeste));
				LIS_InserirElementoApos( pCartasDoJogador , pCartas[j+3] ) ;
			}
		}
		
		IrInicioLista( pCartasDoJogador ) ;
//		puts("OH ANTES");
		for (j=0; j<3; j++){
			pCarta = LIS_ObterValor( pCartasDoJogador ) ;
			BAR_ObterInfo( pCarta , &valorTeste , &naipeTeste ) ;
//			printf("AQUI O VALOR %c E AQUI O NAIPE %s\n", PAR_converteValor(valorTeste), PAR_converteNaipe(naipeTeste));
			//puts("OH CARALHO");
			LIS_AvancarElementoCorrente( pCartasDoJogador , 1 ) ;
		}
//		puts("OH DEPOIS");
		IrInicioLista( pCartasDoJogador ) ;
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

	// LIBERAR AS LISTAS DE CARTAS DOS JOGADORES

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

		grupoGanhadorDaMao = ( numRodadasGrupo1 > numRodadasGrupo2 ) ? 1 : 2 ;
	}

	MES_EsvaziarMesa( jogoDeTruco.pMesa ) ;

	return PAR_AtualizarPontuacao( grupoGanhadorDaMao , valorApostaCorrente ) ;
}

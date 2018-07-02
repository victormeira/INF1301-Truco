/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Main
*  Arquivo:              Main.c
*
*  Autores: awv - Alexandre Wanick Vieira
*           bcr - Bernardo Costa Ruga
*           vmp - Victor Meira Pinto
*
*  $HA Histórico de evolução:
*     Versão    Autor    Data          Observações
*       1.0       awv      29/06         Criação do arquivo Main.c
*
***************************************************************************/

#define MAIN_OWN
#include "PARTIDA.H"
#include "INTERFACE.H"
#include "glut.h"
#include <stdio.h>
#include <stdlib.h>
#define K 13
#define Q 12
#define J 11
#define A 1
#define PAUS 1
#define COPAS 2
#define ESPADAS 3
#define OUROS 4
#undef MAIN_OWN

int main( int argc , char ** argv )
{
	int numJogadores ;

	printf( "Numero de jogadores: " ) ;
	scanf( "%d" , &numJogadores ) ;

	INT_ConfigurarInterface( &argc , argv ) ;

	PAR_CriarPartida( numJogadores ) ;
	PAR_IniciarPartida( ) ;
	PAR_DestruirPartida( ) ;

	return 0;
}

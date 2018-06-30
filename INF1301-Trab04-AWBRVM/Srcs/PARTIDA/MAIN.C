/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Partida
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
#include <stdio.h>
#include "PARTIDA.H"
#undef MAIN_OWN

int main(void)
{
	int numJogadores ;

	printf( "Numero de jogadores: " ) ;
	scanf( "%d" , &numJogadores ) ;

	PAR_CriarPartida( numJogadores ) ;
	PAR_IniciarPartida( ) ;
	PAR_DestruirPartida( ) ;

	return 0;
}

#include <stdio.h>
#include "PARTIDA.H"

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

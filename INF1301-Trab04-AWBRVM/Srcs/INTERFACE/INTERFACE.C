#include "LISTA.H"
#include "BARALHO.H"
#include "MESA.H"
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

#define TRUE 1
#define FALSE 0

extern int nJogadores ;

extern int jogadorCorrente ;

extern int valorApostaCorrente ;

extern MES_tppMesa pMesa ;

char interfaceFlag = 0 ;

char displayFlag = 0 ;

char maoFlag = FALSE ;

char rodadaFlag = FALSE ;

char grupoVencedorPartidaFlag = FALSE ;

char displayCartasFlag = FALSE ;

static GLuint texturaCartas[40] ;

static int grupoGanhadorDaMao ;

static const float larguraCarta = 0.25 ;
static const float alturaCarta = 0.5 ;

static void INT_CarregarTexturaBMP(const char *pathArquivo, GLuint* indiceTexturaRet)
{
	FILE * imagem;
	GLuint textura;
	unsigned char* vetorImagem;
	unsigned char* ponteiro;
	unsigned char header[54];
	
	int i;
	int larguraImagem = 0;
	int alturaImagem = 0;

	imagem = fopen( pathArquivo, "rb" );

	fread(header, 54, 1, imagem);

	ponteiro = (unsigned char*) &larguraImagem;
	for (i = 0; i < 4; i++)
	{
		*ponteiro = header[18+i];
		ponteiro++;
	}

	ponteiro = (unsigned char*) &alturaImagem;
	for (i = 0; i < 4; i++)
	{
		*ponteiro = header[22+i];
		ponteiro++;
	}

	vetorImagem = (unsigned char*) malloc(larguraImagem*alturaImagem*3);

	fread(vetorImagem, larguraImagem*alturaImagem*3, 1, imagem);

	fclose(imagem);

	for(i = 0; i < larguraImagem*alturaImagem; i++)
	{
		int indice = i*3;
		unsigned char B,R;

		B = vetorImagem[indice];
		R = vetorImagem[indice+2];

		vetorImagem[indice] = R;
		vetorImagem[indice+2] = B;
	}

	glGenTextures(1, &textura);
	glBindTexture(GL_TEXTURE_2D, textura);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, larguraImagem, alturaImagem, GL_RGB, GL_UNSIGNED_BYTE, vetorImagem);

	free(vetorImagem);

	*indiceTexturaRet = textura;

}	/* Fim Função ITFC_CarregarTexturaBMP */

static void INT_CarregarImagens( void )
{
	int i ;
	char bmp[16] = "CARTAS/01.bmp" ;

	for ( i = 0 ; i < 40 ; i++)
	{
		bmp[7] = ( i + 1 ) / 10 + '0'; 
		bmp[8] = ( i + 1 ) % 10 + '0' ;
		INT_CarregarTexturaBMP( bmp , &texturaCartas[i] ) ;
	}

}	/* Fim Função ITFC_CarregarImagens */

void INT_DesenharCarta( int valor, int naipe, float xEsquerda, float yBaixo )
{
	switch ( valor )
    {
		case J:
            valor = 8 ;
            break ;
        case Q:
            valor = 9 ;
            break ;
		case K:
            valor = 10 ;
            break ;
        case A:
            valor = 1 ;
            break ;
        default:
            break ;
    } /* switch */

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texturaCartas[( valor - 1 ) + ( ( naipe - 1 ) * 10 ) ]);

	glColor3f(1,1,1);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);	glVertex2f(xEsquerda, yBaixo);
		glTexCoord2f(1, 0);	glVertex2f(xEsquerda + larguraCarta, yBaixo);
		glTexCoord2f(1, 1);	glVertex2f(xEsquerda + larguraCarta, yBaixo + alturaCarta);
		glTexCoord2f(0, 1);	glVertex2f(xEsquerda, yBaixo + alturaCarta);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

static void INT_MouseClick(int botao, int state, int x, int y)
{
	
}

void INT_DesenharCartasNaMao( void )
{
	int i ;
	int valorDaCarta ;
	int naipeDaCarta ;

	const float espaco = 0.5 ;

	BAR_tppCarta pCarta ;
	LIS_tppLista pCartasDoJogador ;

	pCartasDoJogador = PAR_ObterMaoJogador( jogadorCorrente ) ;

	i = 0 ;

	do
	{
		pCarta = LIS_ObterValor( pCartasDoJogador ) ;

		BAR_ObterInfo( pCarta , &valorDaCarta , &naipeDaCarta ) ;

		INT_DesenharCarta( valorDaCarta , naipeDaCarta , -0.75 + ( i * espaco ) , -0.75 ) ;

		i++ ;
	}
	while ( LIS_AvancarElementoCorrente( pCartasDoJogador , 1 ) == LIS_CondRetOK ) ;

	IrInicioLista( pCartasDoJogador ) ;

	displayCartasFlag = FALSE ;
}

void INT_DesenharCartasNaMesa( MES_tppMesa pMesa )
{
	int i ;
	int valorDaCarta ;
	int naipeDaCarta ;

	const float espaco = 0.5 ;

	for ( i = 0 ; i < nJogadores ; i++ )
	{
		if ( MES_ObterCarta( pMesa , i , &valorDaCarta , &naipeDaCarta ) == MES_CondRetOk )
		{
//			if (i == 0)
			INT_DesenharCarta( valorDaCarta , naipeDaCarta , -0.75 + ( i * espaco ) , 0.375 ) ;
//			else
//				INT_DesenharCarta( valorDaCarta , naipeDaCarta , -0.75, 0.375 - (i*espaco) - 0.0625) ;
		} /* if */
	} /* for */

	displayCartasFlag = FALSE ;
}

static void INT_Display( void )
{
	static int jogadas = 0 ;

	glClearColor( 0.13 , 0.545 , 0.13 , 0 ) ;
	glClear( GL_COLOR_BUFFER_BIT ) ;

	if ( displayCartasFlag == TRUE )
	{
		goto endDisplay ;
	}

	if ( maoFlag == TRUE )
	{
		if ( rodadaFlag == FALSE )
		{
			rodadaFlag = TRUE ;
			PAR_IniciarRodada( ) ;
		}

		displayCartasFlag = TRUE ;

		if ( PAR_AtualizarRodada( ) != 0 )
		{
			// Alguém ganhou a rodada por ter aposta recusada
//			rodadaId = 0 ;
			rodadaFlag = FALSE ;
			PAR_FinalizarRodada( ) ;
			goto endDisplay ;
		}

		if ( rodadaFlag = FALSE )
		{
			goto endDisplay ;
		}

//		if ( jogadas < nJogadores )
//		{
//			jogadas++ ;
//		}
//		else
//		{
//			jogadas = 0 ;

//			rodadaId++ ;

//			printf("JOGADAS: %d\n", jogadas);

//			if ( rodadaId == 3 )
//			{
//				rodadaId = 0 ;
//				rodadaFlag = FALSE ;
//				PAR_FinalizarRodada( ) ;
//			}
//		}
	}

	if ( maoFlag == FALSE )
	{
		if ( grupoVencedorPartidaFlag == FALSE )
		{
			maoFlag = TRUE ;
			PAR_IniciarMao( ) ;

			displayCartasFlag = TRUE ;
//			INT_DesenharCartasNaMao( ) ;
//			if ( displayCartasFlag == TRUE )
//			{
//				displayCartasFlag = FALSE ;
//				goto endDisplay ;
//			}
		}
	}

	endDisplay:
	if ( displayCartasFlag == TRUE )
	{
		INT_DesenharCartasNaMesa( pMesa ) ;
		INT_DesenharCartasNaMao( ) ;
		
		glutPostRedisplay( ) ;
	}

//	printf("JOGADAS: %d\n", jogadas);

	glutPostRedisplay( ) ;
	glutSwapBuffers( ) ;
}

void INT_ConfigurarInterface( int * pArgc , char ** argv )
{
	glutInit( pArgc, argv ) ;
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA ) ;
	glutInitWindowSize( 800 , 600 ) ;
	glutCreateWindow( "Truco" ) ;
	glLoadIdentity( ) ;
	gluOrtho2D( -1, 1, -1, 1 ) ;

	INT_CarregarImagens( ) ;

	glutDisplayFunc( INT_Display ) ;
	glutMouseFunc( INT_MouseClick ) ;

}	/* Fim Função ITFC_ConfigurarInterface */

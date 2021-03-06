#if ! defined( LerParm_ )
#define LerParm_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LER  Ler par�metros de comandos
*
*  Arquivo gerado:              LerParm.h
*  Letras identificadoras:      LER
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\ARCABOUC.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Prov� fun��es para a leitura e an�lise l�xica dos comandos de teste.
*     Pressup�e-se que cada comando de teste esteja integralmente em
*     uma linha.
*     Cada comando de teste inicia com o caractere '=' seguido de um string
*     que identifica o comando.
*     Cada comando pode requerer zero ou mais par�metros que se encontram na
*     mesma linha que o comando.
*     Par�metros podem ser literis ou simb�licos.
*     Os par�metros simb�licos precisam ser declarados antes de serem
*     utilizados.
*     Os par�metros t�m tipo e a leitura deve respeitar esses tipos.
*
*     Se for do interesse do programador, m�dulos de teste espec�fico
*     podem ler e processar por conta pr�pria linhas do script. Isto
*     pode ser necess�rio quando um m�dulo necessita de um grande
*     n�mero de par�metros ou de dados especiais.
*
*  $EIU Interface com o usu�rio pessoa
*     Este m�dulo interpreta os comandos de teste globalmente dispon�veis:
*
*     =declararparm   <nome>  <idTipo>  <literal>
*        declara o par�metro <nome> do <tipo> definido com o valor <literal>
*        <tipo> pode ser um de:
*           i - inteiro (long)
*           f - flutuante (double)
*           c - caractere
*           s - string
*        O valor de literal tem que estar em conformidade com o tipo
*
*     =exibirdeclaracao <nome>
*        exibe a declara��o do par�metro <nome> em formato "dump de mem�ria"
*
*     Literais devem obedecer �s regras l�xicas utilizadas pela linguagem C.
*
*     Estes comandos sempre estar�o dispon�veis. Os demais comandos de
*     teste est�o impementados no m�dulo TESTLER espec�fico para este m�dulo.
*
***************************************************************************/
 
#if defined( LerParm_OWN )
   #define LerParm_EXT
#else
   #define LerParm_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

#define  LER_DIM_NOME     32
#define  LER_DIM_STRING  500
#define  LER_DIM_BUFFER      250


/***********************************************************************
*
*  $TC Tipo de dados: LER Condi��es de retorno
*
*
***********************************************************************/

   typedef enum {

         LER_CondRetOK ,
               /* Ler retorno OK */

         LER_CondRetNaoAbriu
               /* Ler n�o abriu arquivo */

   } LER_tpCondRet ;

/***** Dados exportados pelo m�dulo *****/

   /* Estrutura de dados: *LER  Dados globais p�blicos */

   LerParm_EXT int LER_TamBuffer ;
         /* Tamanho do string contido no buffer de leitura
               *
               *$ED Descri��o
               *   Cont�m o n�mero total de caracteres do buffer, excluindo o zero.
               *   Jamais altere este valor. */

   LerParm_EXT int  LER_InxBuffer ;
         /* Cursor do buffer de leitura
               *
               *$ED Descri��o
               *   O cursor de leitura indexa o primeiro caractere n�o lido contido
               *   no buffer.
               *   O cursor � zerado sempre que uma nova linha for lida.
               *   O cursor � avan�ado ao ler um par�metro, sendo colocado no
               *   primeiro caractere imediatamente ap�s ao par�metro lido.
               *   Evite acessar caracteres quando LER_InxBuffer > LER_TamBuffer */

   LerParm_EXT char LER_Buffer[ LER_DIM_BUFFER + 1 ] ;
         /* Buffer de leitura
               *
               *$ED Descri��o
               *   Cont�m a linha corrente do script a ser processada.
               *   Jamais altere o valor do buffer. */


/***********************************************************************
*
*  $FC Fun��o: LER  &Inicializar m�dulo LerParm
*
*  $ED Descri��o da fun��o
*     Inicializa o m�dulo.
*     Deve ser chamada antes de iniciar a an�lise de comandos.
*     Deve ser chamada uma �nica vez no in�cio ou ap�s terminar o m�dulo.
*
***********************************************************************/

   int LER_InicializarLeitura( void ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Terminar m�dulo LerParm
*
*  $ED Descri��o da fun��o
*     Fecha o arquivo de leitura e sinaliza m�dulo de leitura n�o
*     inicializado.
*     Ap�s esta fun��o somente poder� ser chamada a fun��p
*     LER_InicializarLeitura
*
***********************************************************************/

   void LER_TerminarLeitura( void ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Obter nome do arquivo script
*
*  $FV Valor retornado
*     Retorna o ponteiro para o nome do arquivo script sendo processado.
*     Deve-se tomar cuidado para n�o alterar este nome.
*     Ser� NULL se n�a tem arquivo aberto ou o m�dulo n�o est� inicializado.
*
***********************************************************************/

   char * LER_ObterNomeArqScript( void ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Obter n�mero de linhas lidas at� o momento
*
***********************************************************************/

   int LER_ObterNumLinhas( void ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Abrir arquivo script de teste
*
*  $ED Descri��o da fun��o
*     Abre o arquivo que cont�m o script de teste.
*     A extens�o default do arquivo de comandos script de teste �
*     ".script" e ser� acrescida ao nome do arquivo caso este n�o
*     contenha nome de extens�o.
*
*  $EP Par�metros
*     $P NomeArqParm - nome do arquivo contendo o script de teste
*
*  $FV Valor retornado
*     LER_CondRetOK        - caso tenha sido poss�vel abrir o arquivo.
*     LER_CondRetNaoAbriu  - caso tenha ocorrido algum erro.
*                            N�o h� discrimina��o do erro encontrado.
*
***********************************************************************/

   LER_tpCondRet LER_AbrirArquivoScript( char * NomeArqParm ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Ler linha script eliminando brancos ao final
*
*  $ED Descri��o da fun��o
*     L� uma linha do arquivo script e elimina os caracteres branco,
*     fim de linha, tabula��o etc. do final da linha lida.
*
*  $FV Valor retornado
*     Retorna o tamanho da linha lida.
*     Ser�:
*        -1 caso tenha ocorrido fim de arquivo.
*        -2 caso tenha ocorrido algum problema de leitura.
*
***********************************************************************/

   int LER_LerLinhaScript( void ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Interpretar comandos de teste
*
*  $ED Descri��o da fun��o
*     Interpreta os comandos de teste disponibilizados pelo m�dulo
*     de leitura.
*
*     Ver a descri��o do m�dulo para mais detalhes
*
*  $EP Par�metros
*     $P - Comando de teste a ser interpretado
*
*  $FV Valor retornado
*     TST_CondRetOK          - caso tenha interpretado corretamente
*     TST_CondRetNaoExecutou - caso o comando de teste a interpretar
*               n�o perten�a ao conjunto de LER
*     TST_CondRetErro        - caso o comando de teste � do conjunto de LER
*                              e est� sintaticamente errado.
*                              Neste caso � gerada uma mensagem de erro no
*                              log.
*
***********************************************************************/

   TST_tpCondRet LER_InterpretarComandos( char * ComandoTeste ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Declarar par�metro simb�lico
*
*  $EP Par�metros
*     Interpreta uma linha de comando de teste contendo uma declara��o de
*     nome simb�lico.
*     Todas as declara��es t�m o formato:
*       =declararparm  <nome> <tipo> <literal>
*          em que o <literal> deve estar consistente com o <tipo>
*     S�o geradas mensagens de erro no log de teste caso a declara��o
*     n�o possa ser realizada.
*
*  $FV Valor retornado
*     TRUE  - se a declara��o ocorreu
*     FALSE - caso contr�rio
*
***********************************************************************/

   int LER_DeclararParametro( void ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Exibir declara��o de s�mbolo
*
*  $ED Descri��o da fun��o
*     Exibe o S�mbolo e o valor associado ao s�mbolo, sendo que este
*     � exibido em hexadecimal.
*
***********************************************************************/

   void LER_ExibirParametro( char * Simbolo ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Ler linha de par�metros
*
*  $ED Descri��o da fun��o
*     L� um n�mero vari�vel de par�metros
*
*  $EP Par�metros
*     $P Tipos   � um string contendo a identifica��o dos tipos dos par�metros
*                a serem lidos.
*     $P ...     Os demais par�metros s�o refer�ncias (ponteiros) para os
*                espa�os onde dever�o ser armazenados os valores lidos.
*
*     Tal como em scanf deve-se tomar o cuidado de assegurar que a lista
*     de refer�ncia e o string de tipos tenha o mesmo tamanho
*     e que os indicadores de tipo sejam consistentes com a refer�ncia
*     posicionalmente correspondentes.
*
*     Ao ler um campo, primeiro procura-se ler um nome de par�metro j�
*     declarado. Caso isto seja poss�vel e o tipo esteja correto
*     � "lido" o valor contido no par�metro.
*     Caso n�o seja poss�vel, tenta ler um literal em acordo com o tipo
*     dado.
*
*     Gera mensagens de erro para par�metros desconhecidos, sintaxe errada
*     e tipo inconsistente com o solicitado no correspondente caractere no
*     string Tipos.
*
*  $FV Valor retornado
*     Retorna o n�mero de campos lidos at� concluir ou at� encontrar
*     um erro.
*
***********************************************************************/

   int LER_LerParametros( char * Tipos , ... ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Ler par�metro caractere
*
*  $EP Par�metros
*     $P Parm � um ponteiro para um caractere que receber� o valor lido
*
*  $FV Valor retornado
*     TRUE  - se leu
*     FALSE - se ocorreu algum erro
*
*  $FGP Tipos e Vari�veis globais externas do pr�prio m�dulo
*     inxBuffer - � avan�ado para o primeiro caractere branco imediatamente
*                 a seguir do caractere lido
*
*  $EIU Interface com usu�rio pessoa
*     Um caractere deve vir entre aspas simples. Valem os caracteres de controle
*     \n \r \t \a \v \f \\ \' \" \? e \0
*     S�o geradas mensagens de erro no log
*
***********************************************************************/

   int LER_LerParmChar( char * Parm ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Ler par�metro inteiro
*
*  $EP Par�metros
*     $P Parm � um ponteiro para um int que receber� o valor lido
*
*  $FV Valor retornado
*     TRUE  - se leu
*     FALSE - se ocorreu algum erro
*
*  $FGP Tipos e Vari�veis globais externas do pr�prio m�dulo
*     inxBuffer - � avan�ado para o primeiro caractere branco imediatamente
*                 a seguir do int lido
*
*  $EIU Interface com usu�rio pessoa
*     S�o geradas mensagens de erro no log
*
***********************************************************************/

   int LER_LerParmInt( int * Parm ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Ler par�metro flutuante
*
*  $EP Par�metros
*     $P Parm � um ponteiro para um double que receber� o valor lido
*
*  $FV Valor retornado
*     TRUE  - se leu
*     FALSE - se ocorreu algum erro
*
*  $FGP Tipos e Vari�veis globais externas do pr�prio m�dulo
*     inxBuffer - � avan�ado para o primeiro caractere branco imediatamente
*                 a seguir do double lido
*
*  $EIU Interface com usu�rio pessoa
*     S�o v�lidas todas as formas de literal double aceitas pelo scanf.
*     S�o geradas mensagens de erro no log
*
***********************************************************************/

   int LER_LerParmDouble( double * Parm ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Ler par�metro nome
*
*  $EP Par�metros
*     $P Parm       � um ponteiro para um caractere que receber� o nome lido
*     $P tamString  � o tamanho do nome que foi lido
*     $P dimString  � o tamanho m�ximo que o nome poder� ter, j�
*                   descontado o zero final
*
*  $FV Valor retornado
*     TRUE  - se leu
*     FALSE - se ocorreu algum erro
*
*  $FGP Tipos e Vari�veis globais externas do pr�prio m�dulo
*     inxBuffer - � avan�ado para o primeiro caractere branco imediatamente
*                 a seguir do nome lido
*
*  $EIU Interface com usu�rio pessoa
*     S�o v�lidas as mesmas regras de nomes C.
*     S�o geradas mensagens de erro no log
*
***********************************************************************/

   int LER_LerParmNome( char * Parm , int * tamNome , int dimNome ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Ler par�metro string
*
*  $EP Par�metros
*     $P Parm       � um ponteiro para um caractere que receber� o string lido
*     $P tamString  � o tamanho do string que foi lido
*     $P dimString  � o tamanho m�ximo que o string poder� ter, j�
*                   descontado o zero final
*
*  $FV Valor retornado
*     TRUE  - se leu
*     FALSE - se ocorreu algum erro
*
*  $FGP Tipos e Vari�veis globais externas do pr�prio m�dulo
*     inxBuffer - � avan�ado para o primeiro caractere branco imediatamente
*                 a seguir do string lido
*
*  $EIU Interface com usu�rio pessoa
*     Um string deve vir entre aspas duplas.
*     Um string pode conter caracteres de controle
*     \n \r \t \a \v \f \\ \' \" \? e \0
*
*     S�o geradas mensagens de erro no log
*
***********************************************************************/

   int LER_LerParmString( char * Parm , int * tamString , int dimString ) ;


/***********************************************************************
*
*  $FC Fun��o: LER  &Pular comando de teste
*
*  $ED Descri��o da fun��o
*     Avan�a o cursor do buffer de leitura por cima de um comando de teste.
*     Todos os comandos de teste principiam com o prefixo '='
*
***********************************************************************/

   void LER_PularComando( void ) ;

#undef LerParm_EXT

/********** Fim do m�dulo de defini��o: LER  Ler par�metros de comandos **********/

#else
#endif

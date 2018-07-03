##################################################
###
### Diretivas de MAKE para o construto: BARALHO_DEBUG
### Gerado a partir de: ..\composicao\TesteBar_DEBUG.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = BARALHO_DEBUG


### Nomes de paths

Pdef                 = ..\Tabelas
Ph                   = ..\Srcs\BARALHO_DEBUG
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Srcs\BARALHO_DEBUG
Pc                   = ..\Srcs\BARALHO_DEBUG

### Nomes de diretórios para geração

Fdef                 = ..\Tabelas
Fh                   = ..\Srcs\BARALHO_DEBUG
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Srcs\BARALHO_DEBUG
Fc                   = ..\Srcs\BARALHO_DEBUG

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox  /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\baralho.obj   $(Fobj)\testbar.obj   $(Fobj)\lista.obj \
   Construto

### Limpar arquivos

limpa :
   ..\Ferramentas\CompileBanner /c$(NOME)
   ..\Ferramentas\CompileBanner /c$(NOME) >$(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\baralho.obj :  {$(Pc)}\baralho.c \
    {$(Ph)}baralho.h            {$(Ph)}cespdin.h            {$(Ph)}conta.h              \
    {$(Ph)}lista.h             
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\testbar.obj :  {$(Pc)}\testbar.c \
    {$(Ph)}baralho.h            {$(Ph)}generico.h           {$(Ph)}lerparm.h            \
    {$(Ph)}tst_espc.h          
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\baralho.obj   $(Fobj)\testbar.obj   $(Fobj)\lista.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: BARALHO_DEBUG
###
##################################################


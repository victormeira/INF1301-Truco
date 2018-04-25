@ECHO Iniciando o ambiente (environment) para compilar com o Microsoft Visual Studio ...

Call ..\ferramnt\vsvars32.bat

del ..\produto\*.err
del ..\objetos\*.obj

@ECHO Compilando todos os testes...

pushd .

nmake /F..\composicao\LISTA.make
nmake /F..\composicao\BARALHO.make

popd

del ..\objetos\*.obj

if exist ..\produto\*.err goto faz
goto sai

:faz

copy ..\produto\*.err ..\produto\compilatudo.err
notepad ..\produto\compilatudo.err

:sai

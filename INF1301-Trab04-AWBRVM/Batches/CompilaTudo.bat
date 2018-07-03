@ECHO Iniciando o ambiente (environment) para compilar com o Microsoft Visual Studio ...



Call ..\ferramentas\vsvars32.bat



del ..\produto\*.err

del ..\objetos\*.obj



@ECHO Compilando todos os testes...



pushd .



nmake /F..\composicao\LISTA.make

nmake /F..\composicao\BARALHO.make


nmake /F..\composicao\BARALHO_DEBUG.make



popd



del ..\objetos\*.obj



if exist ..\produto\*.err goto faz
goto sai



:faz


copy ..\produto\*.err ..\produto\compilatudo.err

notepad ..\produto\compilatudo.err



:sai

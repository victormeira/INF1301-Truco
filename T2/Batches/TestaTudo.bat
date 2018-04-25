if exist ..\scripts\estatisticas_lista.estat        del ..\scripts\estatisticas_lista.estat

if exist ..\scripts\estatisticas_baralho.estat   del ..\scripts\estatisticas_baralho.estat


del ..\produto\*.log


..\produto\TRAB2-1          /s..\scripts\Scratch         /l..\produto\Lista           /a..\scripts\estatisticas_lista

if errorlevel 4 goto sai


//..\produto\TRAB2-2          /s..\scripts\Baralho    /l..\produto\Baralho      /a..\scripts\estatisticas_baralho

//if errorlevel 4 goto sai


if exist ..\produto\*.log goto faz

goto sai


:faz


copy ..\produto\*.log ..\produto\TestaTudo.log

notepad ..\produto\TestaTudo.log


:sai

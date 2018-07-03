@ECHO OFF

if exist ..\scripts\estatisticas_baralho_DEBUG.estat   del ..\scripts\estatisticas_baralho_DEBUG.estat

if exist ..\produto\TesteBaralho_DEBUG.log   del ..\produto\TesteBaralho_DEBUG.log



..\produto\TRAB4-3          /s..\scripts\TesteContador    /l..\produto\Baralho_DEBUG      /a..\scripts\estatisticas_baralho_DEBUG

if errorlevel 4 goto sai


if exist ..\produto\TesteBaralho_DEBUG.log goto faz

goto sai


:faz


notepad ..\produto\TestaBaralho_DEBUG.log


:sai

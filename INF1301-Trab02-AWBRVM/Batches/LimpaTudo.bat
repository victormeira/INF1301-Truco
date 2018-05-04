@ECHO Removendo todos os arquivos criados após os ultimos testes...

pushd .

cd ..\Batches
del *.bak

cd ..\Composicao
del *.bak
del *.list
del *.make

cd ..\Srcs
del *.bak
del *.err

cd ..\Objetos
del *.bak
del *.obj
del *.build

cd ..\Produto
del *.bak
del *.log
del *.exe
del *.err

cd ..\Scripts
del *.bak
del *.estat


cd ..\Ferramnt
del *.bak
del *.err
del *.obj

popd
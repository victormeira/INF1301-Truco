@ECHO Gerando todos os arquivos necessarios para compilação dos projetos...

pushd  .

..\ferramnt\Gmake  /b..\composicao  /c..\composicao\LISTA
..\ferramnt\Gmake  /b..\composicao  /c..\composicao\BARALHO

popd

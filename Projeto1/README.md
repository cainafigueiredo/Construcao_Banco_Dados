# 1a Avaliação de CBD 2020/2 (Remoto)

## Avaliação das Organizações de Arquivos de Dados  (métodos de acesso primário)

Desenvolver uma banca de teste para a comparação do desempenho de um conjunto de Métodos de Acesso entre as três organizações primárias de arquivos de registros” (file of records), comumente usadas em SGBD Relacionais. Os indicadores de desempenho a serem levantados serão: 

1. **Espaço utilizado:** a ser computado através do total de blocos de memória  secundária utilizados pelo arquivo de registros e pelas eventuais estruturas de apoio.
2. **Número de Acessos:** a ser computados através da quantidade de blocos acessados pelo método de acesso conforme especificado abaixo. Essa medidas dará uma indicação indireta a respeito do espaço e do tempos de acesso necessários à execução das operações com a organização primária adotada.

## Os Métodos de Acesso a serem programados são os seguintes:

1. **(INSERT):** 
- Inserção de um único registro.
- Inserção de um conjunto de registros.

2. **(SELECT):**
- Seleção de um único registro (Find) pela sua chave primária (ou campo UNIQUE). Por exemplo, selecionar o registro de um ALUNO pelo seu DRE fornecido.
- Seleção de conjunto de registros (FindAll) cujas chaves primárias (ou campo UNIQUE) estejam contidas em um conjunto de valores não necessariamente sequenciais. Por exemplo, selecionar todos os registros dos ALUNOS cuja lista de DRE estão inscritos na TURMA de código 1020.
- Seleção de um conjunto de registros (FindAll) cujas chaves primárias (ou campo UNIQUE) estejam contidas em uma faixa de valores dado como parâmetro, por exemplo, todos os ALUNOS cujo DRE esteja na faixa entre "119nnnnnn" e "120nnnnnn" (onde "n" é qualquer dígito de 0 a 9, ou em SQL: ... where DRE between 119000000 and DRE 
- Seleção de todos os registros (FindAll) cujos valores de um campo não chave sejam iguais a um dado parâmetro fornecido. Ou seja, seleção por um campo que permite repetição de valores entre registros. Por exemplo, recuperar todos os registros das PESSOAS cujo campo CIDADE seja igual a "Rio de Janeiro".

3. **(DELETE):**
- Remoção de um único registro selecionado através da chave primária (ou campo cujo valor seja único), por exemplo, remover o ALUNO cujo DRE é dado.
- Remoção de um conjunto de registros selecionados por algum critério, por exemplo, remover todos os ALUNOS da tabela INSCRITOS cuja turma seja a de NUMERO=1023.

4. **(Reorganizar):** 
- Reorganizar o arquivo retirando os registros marcados como removidos, diminuindo o tamanho do arquivo original. Essa operação será executado periodicamente segundo certos critérios.
- Reorganizar arquivo com organização primária sequencial ordenado, que possuem arquivos auxiliares de Extensão (conforme especificado a seguir), utilizando algoritmos como o Merge Sort Externo.

A operação de UPDATE foi considerada como sendo uma remoção seguida de uma inserção e, portanto, não deverá ser programada.

## Organizações Primárias a serem testadas

Cada um desses métodos deverá ser desenvolvido para as seguintes organizações primárias do arquivo de registros:

1. **Heap**, ou arquivo sem qualquer ordenação, com registros de tamanho fixos, inserção de novos ao final do arquivo, e remoção baseada em lista encadeada dos registros removidos, que deverão ser reaproveitados em uma nova inserção posterior a remoção.

2. **Heap**, ou sequencial sem qualquer ordenação, com registros de tamanho variável (por exemplo, campos strings, campos multivalorados, etc.). Os campos de tamanho variável podem ser organizados por caracteres de marcação, ou por Record Head contendo (posição, tamanho) dos cada campos de tamanho variável. As inserções deve ser ao final do arquivo, e os registros removidos deverão ser apenas marcados. O espaço dos registros deletados deverá ser retirado do arquivo através de processo periódico de Reorganização do mesmo, quando atingido certos critérios.

3. Arquivo **ordenado** por um campo de ordenação escolhido, com registros de tamanho fixo. As inserções de novos registros deverão ocorrer em um arquivo de Extensão com posterior reordenação, após certo critério ser atingido, entre o arquivo Principal e a sua Extensão. Remoção através de marcação do registro deletado, com posterior Reorganização do arquivo, retirando os espaços dos registros removidos. Essa reorganização pode se dar em conjunto com a reordenação de junção com o arquivo auxiliar de Extensão.

4. **Hash externo estático**, distribuídos segundo uma campo chave de hashing (ou campo cujo valor seja único), usando como tamanho do bucket um múltiplo do tamanho dos blocos de memória, tratamento de colisão por lista em conjunto de overflow buckets. Pode ser utilizada uma função de hashing básica, do tipo “função módulo”, usando o número de buckets alocados, ou utilizar outra que melhor se adequa ao(s) domínio(s) do campo(s) de hashing escolhido(s) (por exemplo, pela primeira letra de um campo string que distribui entre 27 buckets sequenciais por ordem alfabética do resultado do hashing). Se for usar uma função de hashing que mantém a ordenação, como no exemplo anterior, isso deverá ser assinalado no trabalho.

## Orientações Gerais

Os registros podem todos serem de tamanho menor que o tamanho do bloco escolhido (ou seja, cada bloco de memória pode acomodar um conjunto de registros). No caso das organizações por ordenação e hash, os registros pode todos serem de tamanho fixo, com atributos (campos) igualmente de tamanho fixo. A blocagem dos registros pode ser unspanned (ou seja, sem quebra de registros entre blocos). Todavia, o grupo que quiser usar registros de tamanho variável, ou mesmo blocagem spanned, ou mesmo testar registros maiores que um bloco, está livre para apresentar essas variações devidamente assinaladas no trabalho entregue.


Todo Arquivo de Registros, em qualquer das organização testadas, deverá ter um FILE HEAD contendo informações gerais, tais como, indicação do esquema de dados que o arquivo codifica (em geral o nome da tabela relacional), número de registros no arquivo, fator de blocagem, tamanhos e localizações relativas dos campos fixos e variáveis dentro dos registros, ponteiro para o início da lista de registros deletados, timestamps de criação e alteração do arquivo, e o que mais o grupo achar conveniente registrar sobre a estrutura do arquivo de registros.

A base de dados de entrada deverá estar em formato texto (.CSV ou outro qualquer) e ser processada para gerar as inserções em lote. A escolha da base é livre, porém deverá ter um tamanho que seja maior que a memória RAM do computador (para provocar o I/O de disco) e ordenação externa. Há diversos sites de geração de bases fakes (https://www.guiadoexcel.com.br/base-de-dados-teste-excel/) ou repositórios com bases reais, tais como, os repositórios públicos nacionais e estrangeiros :

1. “Portal Brasileiro de Dados Abertos”: http://dados.gov.br/

2. IBGE: https://www.ibge.gov.br/pt/inicio.html aba Estatísticas

3. Armazém de dados do IPP/Rio de Janeiro: http://www.data.rio/

4. Dados de SP: http://www.governoaberto.sp.gov.br/

5. Datasus: http://www.datasus.gov.br

6. Free Databases: https://www.ebsco.com/products/research-databases/free-databases

7. Relativo a mortalidade, SOA, https://www.mortality.org/, 

8. Nasa, DOAJ, SSRN, PLS, OpenDOAR, BASE, DBPL Etc.... 

## O resultado a ser entregue será na forma de:

1. Um relatório descrevendo todas as opções adotadas no desenvolvimento da bancada de teste, tais como, o tamanho do bloco de memória adotado, o fator de blocagem, a descrição da base de dados usada no teste, a descrição dos campos, das chaves, das estruturações dos arquivos adotadas, campos utilizados em ordenações, funções de Hash adotada, a estrutura dos HEADs dos arquivos, etc; 
2. Link para o repositório (tipo Git) contendo a hierarquia de arquivos de programas do projeto da bancada de teste, bem como  todo os arquivos auxiliares utilizados e gerados, em particular o Projeto Funcional da bancada, incluindo o Projeto Descritivo de cada rotina programada (no mais simples, o pseudo código da mesma).
3. Tabelas resumo com os valores dos indicadores de desempenhos produzidos durante os testes.
4. Um texto contendo uma conclusão comparativa a respeitos dos resultados obtidos, finalizando com a recomendação de qual organização primária utilizar para cada "caso" de bases de dados e aplicação (parta de exemplos específicos)
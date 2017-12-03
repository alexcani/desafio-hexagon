# Desafio Técnico - Hexagon Agriculture

Desenvolvido por Alex Cani - 03/12/2017

Este repositório contém minha solução para o desafio técnico de Attitude Estimation.

1. Como compilar e rodar
1. Metodologia
1. Visualização dos dados

### Como Compilar e Rodar

O programa foi desenvolvido utilizando o MS Visual Studio Community 2017.

Uma versão compilada e funcional (testada em Windows 7) está disponível na pasta Release na raíz do repositório. (Lembre-se de colocar
o arquivo .log com os dados do acelerômetro na mesma pasta do executável).

Para compilar sua própria versão basta utilizar um compilador qualquer de C++ e compilar o arquivo "Desafio Hexagon Agricultue.cpp". Por
 exemplo, para o compilar via linha de comando do Visual Studio: cl /EHsc "Desafio Hexagon Agricultue.cpp"
 
 Para executar o programa basta rodar o executável. Caso o arquivo com os dados não esteja presente ou não exista permissão para
 criação de arquivos, uma mensagem de erro será apresentada.
 
 ### Metodologia
 
 Para realizar a estimação dos ângulos e roll e pitch, foi utilizada a metodologia descrita em [AN3461](http://www.nxp.com/docs/en/application-note/AN3461.pdf).
 
 As equações utilizadas foram 37 e 38, que evitam problemas de instabilidade numérica para regiões de singularidade. Além disso, foi
 utilizada a função atan2(...), que determinar automaticamente o quadrante do ângulo com base nos sinais dos parâmetros.
 
 A estrutura geral do programa consiste em:
 
 1. Abrir os arquivos de entrada e saída, verificando se as operações foram realizadas com sucesso.
 1. Extrair os dados da medição crua do acelerômetro (8g). De acordo com o datasheet disponível [neste link](https://www.nxp.com/docs/en/data-sheet/MMA8451Q.pdf),
 o modo 8g implica em uma escala de 1024 contagens/g. Isto foi interpretado como significando que, por exemplo, para uma leitura [0 0 1024] os valores
 equivalentes, em g, sejam [0 0 1].
 1. Negar a medição (x = -x) e dividir por 1024 devido à escala.
 1. Calcular através das fórmulas os valores dos ângulos.
 1. Escrever no arquivo de saída os valores convertidos em graus, no formato
 >> roll; pitch
 
 ### Visualização dos dados
 
 Com o arquivo de saída finalizado, um gráfico dos ângulos de roll e pitch em função do tempo foi feito (utilizando MATLAB).
 
 ![grafico](https://github.com/alexcani/desafio-hexagon/blob/master/grafico.png)
 
 ![aa](https://media1.tenor.com/images/7034a32187884f417a6d64e8f3cc4500/tenor.gif?itemid=6223390)

Esse código é a implemteção do algoritmo da Árvore de Huffman, consiste apenas na criação da Árvore e a exibição dos códigos binários dos caracteres.

O que é a Árvore de Huffman:
A Árvore de Huffman é um método de compressão que usa as probabilidades de ocorrência dos símbolos no conjunto de dados a ser comprimido para determinar códigos de tamanho variável para cada símbolo. Ele foi desenvolvido em 1952 por David A. Huffman que era, na época, estudante de doutorado no MIT, e foi publicado no artigo "A Method for the Construction of Minimum-Redundancy Codes".

Uma árvore binária completa, chamada de árvore de Huffman é construída recursivamente a partir da junção dos dois símbolos de menor probabilidade, que são então somados em símbolos auxiliares e estes símbolos auxiliares recolocados no conjunto de símbolos. O processo termina quando todos os símbolos forem unidos em símbolos auxiliares, formando uma árvore binária. A árvore é então percorrida, atribuindo-se valores binários de 1 ou 0 para cada aresta, e os códigos são gerados a partir desse percurso.

A codificação gerada tem também a garantia de ser não ambígua, pois nenhum código pode ser o prefixo de outro código. O resultado do algoritmo de Huffman pode ser visto como uma tabela de códigos de tamanho variável para codificar um símbolo da fonte. Assim como em outros métodos de codificação, os símbolos mais comuns são geralmente representados usando-se menos dígitos que os símbolos que aparecem com menos frequência.

![image](https://user-images.githubusercontent.com/44614612/137076967-7fe07a1e-0f39-4cff-b6a6-dd887f9136d7.png)

Execução:
Para executar o Código apenas compile e execute o arquivo .c, em seguida insira a quantidade de caracteres aleatórios que deseja (n). Resultando nos códigos binários dos n caracteres. 

# Trabalho de Estrutura De Dados II
Repositório para armazenar e organizar os arquivos da parte 2 do trabalho de ED2 do período 2020/3 (UFJF).

Integrantes:
- Alexandre Vitor Silva Braga
- Caio Cedrola Rocha
- Marcelo Ian Rezende Menezes
- Igor Correa Rodrigues

## Instruções para compilação e execução
### Main
```
make
./main DIRETÓRIO_PARA_OS_ARQUIVOS_CSV
```
A main.cpp implementa a leitura dos arquivos csv(etapas 1 e 2) e a análise das estruturas
balanceadas(etapa 5).
### Módulo de testes
```
make modulo
./modulo DIRETÓRIO_PARA_OS_ARQUIVOS_CSV
```
O arquivo modulo_de_teste.cpp permite a verificação do funcionamento das estruturas
implementadas, imprimindo os dados no terminal ou nos arquivos `Quadtree.txt`, `HashTable.txt`,
`AVLTree.txt`, `ArvoreB20.txt` e `ArvoreB200.txt`
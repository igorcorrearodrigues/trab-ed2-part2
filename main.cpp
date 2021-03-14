#include <iostream>
#include <fstream>
#include <limits>
#include <chrono>

#include "HashTable.hpp"
#include "Quadtree.hpp"
#include "ArvB.hpp"
#include "AVLTree.hpp"

#define REMOVE_CSV_HEADER(_ifs) \
	(_ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'))

#define ERR_INVAL_ARGS 1
#define ERR_FALHA_ARQ  2

template<typename ArvoreType>
void insereNChavesDaTabela(ArvoreType& arv, HashTable& t, size_t n)
{
	std::vector<size_t> valores = t.getRandomHashes(n);

	for (const auto& val : valores)
		arv.insere(val);
}

void insercaoNasArvores(HashTable& tabela, size_t n)
{
	AVLTree arvoreAvl;
	ArvB arvB20(20);
	ArvB arvB200(200);

	insereNChavesDaTabela(arvoreAvl, tabela, n);
	insereNChavesDaTabela(arvB20, tabela, n);
	insereNChavesDaTabela(arvB200, tabela, n);
}

int main(int argc, char *argv[])
{
	const char *nomeDoPrograma = *argv;

	if (argc != 2) {
		std::cerr << "Uso: " << nomeDoPrograma << " DIR_DOS_ARQUIVOS_CSV\n";
		return ERR_INVAL_ARGS;
	}

	const std::string csvDir = argv[1];

	// Leitura do arquivo coordenadas
	std::string nomeArquivoCoordenadas = csvDir + "/brazil_cities_coordinates.csv";
	std::ifstream arquivoCoordenadas(nomeArquivoCoordenadas);

	if (!arquivoCoordenadas.is_open()) {
		// std::cerr << nomeDoPrograma << ": falha ao abrir o arquivo: `" << nomeArquivoCoordenadas << "`\n";
		return ERR_FALHA_ARQ;
	}

	Quadtree quadtree;
	Cidade cidadeInput;

	REMOVE_CSV_HEADER(arquivoCoordenadas);
	while (arquivoCoordenadas >> cidadeInput)
		quadtree.insere(new Cidade(cidadeInput));
	quadtree.desenhaMapa();

	arquivoCoordenadas.close();

	// Leitura do arquivo pre-processado
	std::string nomeArquivo = csvDir + "/brazil_covid19_cities_processado.csv";
	std::ifstream arquivoPreProcessado(nomeArquivo);

	if (!arquivoPreProcessado.is_open()) {
		std::cerr << nomeDoPrograma << ":falha ao abrir o arquivo `" << nomeArquivo << "`\n";
		return ERR_FALHA_ARQ;
	}


	HashTable tabela;
	Registro r;

	REMOVE_CSV_HEADER(arquivoPreProcessado);
	while (arquivoPreProcessado)
		tabela.insere(r);

	arquivoPreProcessado.close();

	insercaoNasArvores(tabela, 10000);
	insercaoNasArvores(tabela, 50000);
	insercaoNasArvores(tabela, 100000);
	insercaoNasArvores(tabela, 500000);
	insercaoNasArvores(tabela, 1000000);

	return 0;
}

#include <iostream>
#include <fstream>
#include <limits>

#include "Cidade.hpp"
#include "Registro.hpp"
#include "HashTable.hpp"
#include "Quadtree.hpp"

#define REMOVE_CSV_HEADER(_ifs) \
	(_ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'))

#define ERR_INVAL_ARGS 1
#define ERR_FALHA_ARQ  2

int main(int argc, char *argv[])
{
	const char *nomeDoPrograma = *argv;

	if (argc != 2) {
		std::cerr << "Uso: " << nomeDoPrograma << " DIR_DOS_ARQUIVOS_CSV\n";
		return ERR_INVAL_ARGS;
	}

	const std::string csvDir = argv[1];

	// Leitura do arquivo coordenadas
	{
		std::string nomeArquivoCoordenadas = csvDir + "/brazil_cities_coordinates.csv";
		std::ifstream arquivoCoordenadas(nomeArquivoCoordenadas);

		if (!arquivoCoordenadas.is_open()) {
			std::cerr << nomeDoPrograma << ": falha ao abrir o arquivo: `" << nomeArquivoCoordenadas << "`\n";
			return ERR_FALHA_ARQ;
		}

		REMOVE_CSV_HEADER(arquivoCoordenadas);

		Quadtree arvore;
		Cidade cidadeInput;
		while (arquivoCoordenadas >> cidadeInput)
			arvore.insere(&cidadeInput);

		arquivoCoordenadas.close();
	}

	// Leitura do arquivo pre-processado
	{
		std::string nomeArquivo = csvDir + "/brazil_covid19_cities_processado.csv";
		std::ifstream arquivoPreProcessado(nomeArquivo);

		if (!arquivoPreProcessado.is_open()) {
			std::cerr << nomeDoPrograma << ":falha ao abrir o arquivo `" << nomeArquivo << "`\n";
			return ERR_FALHA_ARQ;
		}

		REMOVE_CSV_HEADER(arquivoPreProcessado);

		HashTable tabela;
		Registro r;
		while (arquivoPreProcessado >> r)
			tabela.insere(r);
	}

	return 0;
}

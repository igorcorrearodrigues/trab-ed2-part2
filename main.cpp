#include <iostream>
#include <fstream>
#include <limits>

#include "Cidade.hpp"

#define CSV_DIR (argv[1])

#define ERR_INVAL_ARGS 1
#define ERR_FALHA_ARQ  2

int main(int argc, char *argv[])
{
	const char *progname = *argv;

	if (argc != 2) {
		std::cerr << "Uso: " << progname << " DIR_DOS_ARQUIVOS_CSV\n";
		return ERR_INVAL_ARGS;
	}

	std::string nomeArquivoCordenadas = std::string(CSV_DIR) + "/brazil_cities_coordinates.csv";
	std::ifstream arquivoCordenadas(nomeArquivoCordenadas);

	if (!arquivoCordenadas.is_open()) {
		std::cerr << progname << ": falha ao abrir o arquivo: `" << nomeArquivoCordenadas << "`\n";
		return ERR_FALHA_ARQ;
	}

	// Remove o header do csv
	arquivoCordenadas.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Cidade cidadeInput;
	while (arquivoCordenadas >> cidadeInput)
		std::cout << cidadeInput << '\n';

	return 0;
}

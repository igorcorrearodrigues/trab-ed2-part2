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
	std::cerr << "Pegando os valores da hash\n";
	std::vector<size_t> valores = t.getRandomHashes(n);
	std::cerr << "Terminou de pegar os valores da hash\n";

	for (const auto& val : valores){
		//std::cerr << "inserindo valor: " << val << std::endl;
		arv.insere(val);
	}
}

int totalDeCasosB(std::string codigo, ArvB b) {
	return b.totalCasosCidade(codigo);
}

size_t totalDeCasosAVL(std::string codigo, AVLTree avl) {	
	return avl.totalCasosCidade(codigo);
}

void insercaoNasArvores(HashTable& tabela, size_t n)
{
	AVLTree arvoreAvl(&tabela);
	ArvB arvB20(20, &tabela);
	ArvB arvB200(200, &tabela);

	insereNChavesDaTabela(arvoreAvl, tabela, n);
	std::cout << "total de casos AVL: " << arvoreAvl.totalCasosCidade("120001") << std::endl;
	insereNChavesDaTabela(arvB20, tabela, n);
	std::cout << "total de casos B20: " << arvB20.totalCasosCidade("120001") << std::endl;
	insereNChavesDaTabela(arvB200, tabela, n);
	std::cout << "total de casos B200: " << arvB200.totalCasosCidade("120001") << std::endl;
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
		std::cerr << nomeDoPrograma << ": falha ao abrir o arquivo: `" << nomeArquivoCoordenadas << "`\n";
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

	size_t n = 0;

	REMOVE_CSV_HEADER(arquivoPreProcessado);
	while (arquivoPreProcessado >> r && n++ < 50001)
		tabela.insere(r);

	arquivoPreProcessado.close();

	std::cout << "Primeira insercão\n";
	insercaoNasArvores(tabela, 10000);
	std::cout << "Segunda insercão\n";
	insercaoNasArvores(tabela, 50000);
	// std::cout << "Terceira insercão\n";
	// insercaoNasArvores(tabela, 100000);
	// std::cout << "Quarta insercão\n";
	// insercaoNasArvores(tabela, 500000);
	// std::cout << "Quinta insercão\n";
	// insercaoNasArvores(tabela, 1000000);

	// S1

	std::string codigo;
	for (;;) {
		/* code */
		std::cout << "S1) Obter o total de casos de uma cidade\n\n";
		std::cout << "Digite o código de uma cidade: ";

		std::cin >> codigo;

		if (CodigoDaCidade::validate(codigo))
			break;

		std::cout << "*** Código inválido ***\n\n";
	}

	std::cout << "Total de casos na cidade com código `" << codigo << "`: ";
	// std::cout << arv.totalCasosCidade(codigo);
	std::cout << '\n';
	
	// S2
	double x0, y0;
	double x1, y1;

	std::cout << "S2) Obter o total de casos nas cidades contidas no\n";
	std::cout << "intervalo [(x0, y0), (x1, y1)], onde x0 e x1 são latitudes e y0 e y1 são longitudes.\n\n";
	std::cout << "Digite x0, y0, x1, y1: ";

	std::cin >> x0 >> y0 >> x1 >> y1;

	std::cout << "Buscando cidades no intervalo [(" << x0 << ", " << y0 << "), (" << x1 << ", " << y1 << ")]...\n";

	quadtree.desenhaMapaRegional(x0, y0, x1, y1);
	std::list<Cidade*> cidadesNaRegiao = quadtree.buscaRegiao(x0, y0, x1, y1);

	std::cout << "Numero de cidades encontradas: " << cidadesNaRegiao.size() << '\n';

	for (const auto cidade_ptr: cidadesNaRegiao) {
		std::cout << "Dados da cidade: " << *cidade_ptr << '\n';
		std::cout << "Total de casos: ";
		// total de casos
	}

	return 0;
}

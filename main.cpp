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
void insereNChavesDaTabela(ArvoreType& arv, HashTable& t, size_t n);

template<typename ArvType>
void insereNChavesNaArvore(HashTable& ht, Quadtree& quad, size_t n, ArvType& arv, std::string title);

int main(int argc, char *argv[])
{
	const char *nomeDoPrograma = *argv;

	srand(time(NULL));

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
		std::cerr << nomeDoPrograma << ": falha ao abrir o arquivo `" << nomeArquivo << "`\n";
		return ERR_FALHA_ARQ;
	}


	HashTable tabela;
	Registro r;

	REMOVE_CSV_HEADER(arquivoPreProcessado);
	while (arquivoPreProcessado >> r)
		tabela.insere(r);

	arquivoPreProcessado.close();

	// Arvore AVL
	{
		AVLTree avl(&tabela);
		insereNChavesNaArvore(tabela, quadtree, 10000, avl, "AVL_10.000.txt");
	}
	// {
	// 	AVLTree avl(&tabela);
	// 	insereNChavesNaArvore(tabela, quadtree, 50000, avl, "AVL_500.000.txt");
	// }
	// {
	// 	AVLTree avl(&tabela);
	// 	insereNChavesNaArvore(tabela, quadtree, 100000, avl, "AVL_100.000.txt");
	// }
	// {
	// 	AVLTree avl(&tabela);
	// 	insereNChavesNaArvore(tabela, quadtree, 500000, avl, "AVL_500.000.txt");
	// }
	// {
	// 	AVLTree avl(&tabela);
	// 	insereNChavesNaArvore(tabela, quadtree, 1000000, avl, "AVL_1000.000.txt");
	// }

	// Arvore B20
	{
		ArvB arv(20, &tabela);
		insereNChavesNaArvore(tabela, quadtree, 10000, arv, "ArvB20_10.000.txt");
	}
	// {
	// 	ArvB arv(20, &tabela);
	// 	insereNChavesNaArvore(tabela, quadtree, 50000, arv, "ArvB20_500.000.txt");
	// }
	// {
	// 	ArvB arv(20, &tabela);
	// 	insereNChavesNaArvore(tabela, quadtree, 100000, arv, "ArvB20_100.000.txt");
	// }
	// {
	// 	ArvB arv(20, &tabela);
	// 	insereNChavesNaArvore(tabela, quadtree, 500000, arv, "ArvB20_500.000.txt");
	// }
	// {
	// 	ArvB arv(20, &tabela);
	// 	insereNChavesNaArvore(tabela, quadtree, 1000000, arv, "ArvB20_1000.000.txt");
	// }

	// Arvore B200
	{
		ArvB arv(200, &tabela);
		insereNChavesNaArvore(tabela, quadtree, 10000, arv, "ArvB200_10.000.txt");
	}
	// {
	// 	ArvB arv(200, &tabela);
	// 	insereNChavesNaArvore(tabela, quadtree, 50000, arv, "ArvB200_500.000.txt");
	// }
	// {
	// 	ArvB arv(200, &tabela);
	// 	insereNChavesNaArvore(tabela, quadtree, 100000, arv, "ArvB200_100.000.txt");
	// }
	// {
	// 	ArvB arv(200, &tabela);
	// 	insereNChavesNaArvore(tabela, quadtree, 500000, arv, "ArvB200_500.000.txt");
	// }
	// {
	// 	ArvB arv(200, &tabela);
	// 	insereNChavesNaArvore(tabela, quadtree, 1000000, arv, "ArvB200_1000.000.txt");
	// }
	return 0;
}

template<typename ArvType>
void insereNChavesNaArvore(HashTable& ht, Quadtree& quad, size_t n, ArvType& arv, std::string fileName)
{
	std::ofstream out(fileName);

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	insereNChavesDaTabela(arv, ht, n);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	out << "Tempo de inserção de " << n << " chaves [µs]:";
	out << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << '\n';
	// S1

	std::string codigo;
	for (;;) {
		std::cout << "S1) Obter o total de casos de uma cidade\n\n";
		std::cout << "Digite o código de uma cidade: ";

		std::cin >> codigo;

		if (CodigoDaCidade::validate(codigo))
			break;

		std::cout << "*** Código inválido ***\n\n";
	}

	out << "Total de casos na cidade com código `" << codigo << "`: ";
	begin = std::chrono::steady_clock::now();
	out << arv.totalCasosCidade(codigo) << '\n';
	end = std::chrono::steady_clock::now();
	out << "Numero de comparações: " << arv.comparacoesUltimaTotalCasos() << '\n';
	out << "Tempo busca [µs]:";
	out << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << '\n';
	
	// S2
	double x0, y0;
	double x1, y1;

	std::cout << "S2) Obter o total de casos nas cidades contidas no\n";
	std::cout << "intervalo [(x0, y0), (x1, y1)], onde x0 e x1 são latitudes e y0 e y1 são longitudes.\n\n";
	std::cout << "Digite x0, y0, x1, y1: ";

	std::cin >> x0 >> y0 >> x1 >> y1;

	out << "Buscando cidades no intervalo [(" << x0 << ", " << y0 << "), (" << x1 << ", " << y1 << ")]...\n";

	quad.desenhaMapaRegional(x0, y0, x1, y1);
	std::list<Cidade*> cidadesNaRegiao = quad.buscaRegiao(x0, y0, x1, y1);

	out << "Numero de cidades encontradas: " << cidadesNaRegiao.size() << '\n';

	size_t casosNaRegiao = 0;
	size_t totalComparacoes = 0;

	begin = std::chrono::steady_clock::now();
	for (const auto cidadePtr : cidadesNaRegiao) {
		size_t casos = arv.totalCasosCidade(cidadePtr->codigo());
		casosNaRegiao += casos;
		totalComparacoes += arv.comparacoesUltimaTotalCasos();

		// out << "Dados da cidade: " << *cidadePtr << '\n';
		// out << "Total de casos: " << casos << '\n';
	}
	end = std::chrono::steady_clock::now();
	out << "Total de casos na regiao: " << casosNaRegiao << '\n';
	out << "Total de comparacoes: " << totalComparacoes << '\n';
	out << "Tempo de busca total [µs]: ";
	out << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "\n\n";
}

template<typename ArvoreType>
void insereNChavesDaTabela(ArvoreType& arv, HashTable& t, size_t n)
{
	std::vector<size_t> valores = t.getRandomHashes(n);

	for (const auto& val : valores){
		arv.insere(val);
	}
}

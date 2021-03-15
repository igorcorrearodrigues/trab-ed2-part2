#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

#include "Quadtree.hpp"
#include "HashTable.hpp"
#include "AVLTree.hpp"
#include "ArvB.hpp"

using namespace std;

#define LIMITE_N 20

std::string arquivoRegistros = "/brazil_covid19_cities_processado.csv";
std::string arquivoCidades = "/brazil_cities_coordinates.csv";

void insereNaQuadtree(Quadtree& q, std::ostream& out, size_t n);
void insereNaTabelaHash(HashTable& t, std::ostream& out, size_t n);
void insereNaArvoreAvl(AVLTree& arv, std::ostream& out, size_t n);
void insereNaArvoreB(ArvB& arv, std::ostream& out, size_t n);

#define DECLARA_INSERE_FUNCTION(_function_name, _estrutura)  \
    void _function_name(size_t n)                            \
    {                                                        \
        _estrutura est;                                      \
        if (n > LIMITE_N) {                                  \
            ofstream arquivoSaida(#_estrutura ".txt"); \
            _function_name(est, arquivoSaida, n);            \
        } else {                                             \
            _function_name(est, std::cout, n);               \
        }                                                    \
    }

DECLARA_INSERE_FUNCTION(insereNaQuadtree, Quadtree)
DECLARA_INSERE_FUNCTION(insereNaTabelaHash, HashTable)

void insereNaArvoreAvl(size_t n)
{
    HashTable ht;
    AVLTree arv(&ht);

    if (n > LIMITE_N) {
        ofstream arquivoSaida("ArvB20.txt");
        insereNaTabelaHash(ht, arquivoSaida, n);
        insereNaArvoreAvl(arv, arquivoSaida, n);
    } else {
        insereNaArvoreAvl(arv, std::cout, n);
    }
}

void insereNaArvoreB20(size_t n)
{
    HashTable ht;
    ArvB arv(20, &ht);

    if (n > LIMITE_N) {
        ofstream arquivoSaida("ArvB20.txt");
        insereNaTabelaHash(ht, arquivoSaida, n);
        insereNaArvoreB(arv, arquivoSaida, n);
    } else {
        insereNaTabelaHash(ht, std::cout, n);
        insereNaArvoreB(arv, std::cout, n);
    }
}

void insereNaArvoreB200(size_t n)
{
    HashTable ht;
    ArvB arv(200, &ht);

    if (n > LIMITE_N) {
        ofstream arquivoSaida("ArvB200.txt");
        insereNaTabelaHash(ht, arquivoSaida, n);
        insereNaArvoreB(arv, arquivoSaida, n);
    } else {
        insereNaTabelaHash(ht, std::cout, n);
        insereNaArvoreB(arv, std::cout, n);
    }
}

struct MenuOpcao
{
    const char *text;
    void (*exec)(size_t);
};

#define OPCOES_SIZE (5)

MenuOpcao opcoes[] = {
    { "Quadtree"   , insereNaQuadtree   },
    { "Tabela Hash", insereNaTabelaHash },
    { "Árvore AVL" , insereNaArvoreAvl  },
    { "Árvore B20" , insereNaArvoreB20  },
    { "Árvore B200", insereNaArvoreB200 },
};

// #define OPCOES_SIZE (sizeof(opcoes) / sizeof(*opcoes))
#define OPCAO_SAIR (OPCOES_SIZE + 1)

inline bool validOption(unsigned option)
{
    return (option > 0 && option <= OPCOES_SIZE);
}

MenuOpcao *getOpcao(unsigned n)
{
    extern MenuOpcao opcoes[];

    return validOption(n) ? &opcoes[n - 1] : nullptr;
}

int main(int argc, char *argv[])
{
    unsigned opcao;
    extern std::string arquivoCidades;
    extern std::string arquivoRegistros;
    extern MenuOpcao opcoes[];

    if (argc != 2) {
        std::cerr << "Uso: " << *argv << " DIR_DOS_ARQUIVOS_CSV\n";
        return 1;
    }

    arquivoCidades = argv[1] + arquivoCidades;
    arquivoRegistros = argv[1] + arquivoRegistros;

    do
    {
        cout << "************************\n";
        cout << "*** Modulo de testes ***\n";
        cout << "************************\n\n";

        cout << "Escolha a estutura:\n";
        for (unsigned i = 0; i < OPCOES_SIZE; ++i)
            cout << (i + 1) << " - " << opcoes[i].text << '\n';
        cout << OPCAO_SAIR << " - " << "Sair\n";

        cout << "\nR: ";

        if (cin >> opcao) {
            if (opcao == OPCAO_SAIR) {
                cout << "Adios!\n";
                return 0;
            }
            MenuOpcao *escolhida = getOpcao(opcao);

            if (escolhida == nullptr) {
                std::cout << "Opção `" << opcao << "` inválida!!\n";
                continue;
            }
            std::cout << "Opção escolhida: [" << opcao << "]: `" << escolhida->text << "`\n";

            std::cout << "Digite n: ";

            size_t n;

            std::cin >> n;

            escolhida->exec(n);
        } else {
            cout << "Falha na leitura de opcao\n";
            return 1;
        }
    } while (true);
}

vector<Cidade> getNCidades(size_t n)
{
    extern std::string arquivoCidades;
    std::ifstream in(arquivoCidades);

    if (!in.is_open()) {
        std::cerr << "Falha ao abrir o arquivo `" << arquivoCidades << "`\n";
        return std::vector<Cidade>{};
    }

    std::vector<Cidade> aleatorios;
    Cidade read;

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (in >> read)
        aleatorios.push_back(read);
    aleatorios.resize(n);
    return aleatorios;
}

vector<Registro> getNRegistros(size_t n)
{
    extern std::string arquivoRegistros;
    std::ifstream in(arquivoRegistros);

    if (!in.is_open()) {
        std::cerr << "Falha ao abrir o arquivo `" << arquivoRegistros << "`\n";
        return std::vector<Registro>{};
    }

    std::vector<Registro> aleatorios;
    Registro read;

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (in >> read)
        aleatorios.push_back(read);
    aleatorios.resize(n);
    return aleatorios;
}

void insereNaQuadtree(Quadtree& q, std::ostream& out, size_t n)
{
    std::vector<Cidade> cidades = getNCidades(n);

    out << __FUNCTION__ << '\n';
    for (auto& cidade : cidades) {
        out << cidade << '\n';
        q.insere(new Cidade(std::move(cidade)));
    }
}

void insereNaTabelaHash(HashTable& t, std::ostream& out, size_t n)
{
    std::vector<Registro> registros = getNRegistros(n);

    out << __FUNCTION__ << '\n';
    for (auto& r : registros) {
        out << r << '\n';
        t.insere(r);
    }
}

void insereNaArvoreAvl(AVLTree& arv, std::ostream& out, size_t n)
{
    std::vector<size_t> hashes = arv.getHashTable()->getRandomHashes(n);
    
    out << __FUNCTION__ << '\n';
    for (size_t val : hashes) {
        out << "Inserindo: " << val << '\n';
        arv.insere(val);
    }
    out << arv << '\n';
}

void insereNaArvoreB(ArvB& arv, std::ostream& out, size_t n)
{
    std::vector<size_t> hashes = arv.getHashTable()->getRandomHashes(n);

    out << __FUNCTION__ << '\n';
    for (size_t val : hashes) {
        out << "Inserindo: " << val << '\n';
        arv.insere(val);
    }
}
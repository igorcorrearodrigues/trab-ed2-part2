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

void insereNaQuadtree(Quadtree& q, std::ostream& out, size_t n);
void insereNaTabelaHash(HashTable& t, std::ostream& out, size_t n);
void insereNaArvoreAvl(AVLTree& arv, std::ostream& out, size_t n);
void insereNaArvoreB(ArvB& arv, std::ostream& out, size_t n);

#define DECLARA_INSERE_FUNCTION(_function_name, _estrutura)  \
    void _function_name(size_t n)                            \
    {                                                        \
        _estrutura est;                                      \
        if (n > LIMITE_N) {                                  \
            ofstream arquivoSaida(#_estrutura ".saida.txt"); \
            _function_name(est, arquivoSaida, n);            \
        } else {                                             \
            _function_name(est, std::cout, n);               \
        }                                                    \
    }

DECLARA_INSERE_FUNCTION(insereNaQuadtree, Quadtree)
DECLARA_INSERE_FUNCTION(insereNaTabelaHash, HashTable)
DECLARA_INSERE_FUNCTION(insereNaArvoreAvl, AVLTree)

void insereNaArvoreB20(size_t n)
{
    ArvB arv(20);

    if (n > LIMITE_N) {
        ofstream arquivoSaida("ArvB20.saida.txt");
        insereNaArvoreB(arv, arquivoSaida, n);
    } else {
        insereNaArvoreB(arv, std::cout, n);
    }
}

void insereNaArvoreB200(size_t n)
{
    ArvB arv(200);

    if (n > LIMITE_N) {
        ofstream arquivoSaida("ArvB200.saida.txt");
        insereNaArvoreB(arv, arquivoSaida, n);
    } else {
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

int main()
{
    unsigned opcao;
    extern MenuOpcao opcoes[];

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
    const char filename[] = "./datasets/brazil_cities_coordinates.csv";
    std::ifstream in(filename);

    if (!in.is_open()) {
        std::cerr << "Falha ao abrir o arquivo `" << filename << "`\n";
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
    const char filename[] = "./datasets/brazil_covid19_cities_processado.csv";
    std::ifstream in(filename);

    if (!in.is_open()) {
        std::cerr << "Falha ao abrir o arquivo `" << filename << "`\n";
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

    for (auto& cidade : cidades) {
        out << cidade << '\n';
        q.insere(new Cidade(std::move(cidade)));
    }
}

void insereNaTabelaHash(HashTable& t, std::ostream& out, size_t n)
{
    std::vector<Registro> registros = getNRegistros(n);

    for (auto& r : registros) {
        out << r << '\n';
        t.insere(r);
    }
}

void insereNaArvoreAvl(AVLTree& arv, std::ostream& out, size_t n)
{
    out << __FUNCTION__ << '\n';
    for (size_t i = 0; i < n; ++i) {
        out << i << '\n';
        arv.insere(i);
    }
}

void insereNaArvoreB(ArvB& arv, std::ostream& out, size_t n)
{
    out << __FUNCTION__ << '\n';
    for (size_t i = 0; i < n; ++i) {
        out << i << '\n';
        arv.insere(i);
    }
}
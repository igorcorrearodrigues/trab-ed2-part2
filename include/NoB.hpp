#ifndef NOB_HPP
#define NOB_HPP

#include "HashTable.hpp"
#include "Registro.hpp"

class NoB
{
    int *chaves;
    size_t d;
    NoB **filhos;
    size_t n;
    bool folha;

    HashTable *tabela;
    int compMaiorQueID(size_t info, size_t id);

public:
    NoB(size_t d, bool folha, HashTable *tabela);
    ~NoB();
 
    bool isFolha();
    void imprimeLinear(); // Imprime as chaves em ordem crescente
    void imprimeEstrutura(); // Imprime a estrutura da arvore
    size_t procuraPosicao(int id, size_t& comps);
    size_t totalCasosCidade(std::string codigo);
    bool busca(int id, size_t& comps);
    void insereSeNaoCheio(int id); 
    void divideFilho(int i, NoB *filho); 

    size_t getAltura();

friend class ArvB;
};

#endif /* NOB_HPP */
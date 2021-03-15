#ifndef ARVB_HPP
#define ARVB_HPP

#include "NoB.hpp"

#include <chrono>

class ArvB 
{ 
    NoB *raiz;
    HashTable *tabela;

    size_t m; // Ordem da arvore, representa o maximo de filhos
    size_t comparacoes;
    std::chrono::microseconds _tempoBusca;
    std::chrono::microseconds _tempoInsercao;

public:
    ArvB(size_t m, HashTable *tabela)
    {
        this->raiz = NULL;
        this->m = m;
        this->tabela = tabela;
    };
  
    void imprimeLinear();
    void imprimeEstrutura();
    bool busca(int id);
    void insere(int id);
    size_t totalCasosCidade(std::string codigo);

    size_t comparacoesUltimaBusca();
    const std::chrono::microseconds& tempoUltimaBusca();
    const std::chrono::microseconds& tempoUltimaInsercao();

    size_t getAltura();
};

#endif /* ARVB_HPP */
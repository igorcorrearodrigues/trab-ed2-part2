#ifndef ARVB_HPP
#define ARVB_HPP

#include <chrono>

#include "NoB.hpp"

class ArvB
{
    NoB *raiz;
    size_t d; // Numero minimo de filhos

    HashTable *tabela;

    size_t comparacoes;
    size_t compTotalCasos;
    std::chrono::microseconds _tempoBusca;
    std::chrono::microseconds _tempoInsercao;

public:
    ArvB(size_t d, HashTable *tabela);
 
    void imprimeLinear();
    void imprimeEstrutura();
 
    bool busca(int id);
    void insere(int id); 

    size_t totalCasosCidade(std::string codigo);
    int compMaiorQueID(size_t info, size_t id);
    HashTable *getHashTable();

    size_t comparacoesUltimaBusca();
    size_t comparacoesUltimaTotalCasos();
    const std::chrono::microseconds& tempoUltimaBusca();
    const std::chrono::microseconds& tempoUltimaInsercao();


    size_t getAltura(); 
};

#endif /* ARVB_HPP */
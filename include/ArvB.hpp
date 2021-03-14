#ifndef ARVB_HPP
#define ARVB_HPP

#include "NoB.hpp"

class ArvB 
{ 
    NoB *raiz;
    size_t m; // Ordem da arvore, representa o maximo de filhos
    size_t comparacoes;

public:
    ArvB(size_t m)
    {
        this->raiz = NULL;
        this->m = m;
    };
  
    void imprimeLinear();
    void imprimeEstrutura();
    bool busca(int id);
    void insere(int id);

    size_t getComparacoes();

    size_t getAltura();
};

#endif /* ARVB_HPP */
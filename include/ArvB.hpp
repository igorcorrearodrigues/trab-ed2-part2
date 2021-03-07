#ifndef ARVB_HPP
#define ARVB_HPP

#include "NoB.hpp"

class ArvB 
{ 
    NoB *raiz;
    size_t m; // Ordem da arvore, representa o maximo de filhos
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
}; 

#endif /* ARVB_HPP */
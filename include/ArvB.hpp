#ifndef ARVB_HPP
#define ARVB_HPP

#include "NoB.hpp"

class ArvB
{
    NoB *raiz;
    size_t d;
public:
    ArvB(size_t d);
 
    void imprimeLinear();
    void imprimeEstrutura();
 
    bool busca(int id);
    void insere(int id); 
};

#endif /* ARVB_HPP */
#include <iostream>

#include "ArvB.hpp"

void ArvB::imprimeLinear()
{
    if (this->raiz != NULL) 
        this->raiz->imprimeLinear();
    else
        std::cout << "Arvore vazia!";
    std::cout << "\n";
}

void ArvB::imprimeEstrutura() 
{
    if (this->raiz != NULL) 
        this->raiz->imprimeEstrutura();
    else
        std::cout << "Arvore vazia!";
    std::cout << "\n";
}

bool ArvB::busca(int id) 
{
    this->comparacoes = 0;
    return (this->raiz == NULL) ? false : this->raiz->busca(id, comparacoes); 
} 

size_t ArvB::getComparacoes()
{
    return this->comparacoes;
}

void ArvB::insere(int id) 
{
    std::cout << "Insere " << id << "\n";

    if (this->raiz == NULL) {
        std::cout << "Raiz null" << std::endl;
        this->raiz = new NoB(this->m, true);
        this->raiz->insere(id);
    } else if (this->raiz->getN() == this->m-1) {
        std::cout << "Raiz cheia" << std::endl;
        // Se raiz estiver cheia, cria nova raiz
        NoB *novaRaiz = new NoB(this->m, false);
        novaRaiz->divideFilhoEInsere(this->raiz, 0, id); // Redistribui as chaves da raiz antiga 
        this->raiz = novaRaiz; // Atualiza raiz
        std::cout << "Setou nova raiz" << std::endl;
    }
    else {
        this->raiz->insere(id);
    }
}

size_t ArvB::getAltura()
{
    return (this->raiz == NULL) ? 0 : this->raiz->getAltura();
}

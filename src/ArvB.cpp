#include <iostream>

#include "../include/ArvB.hpp"

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
    return (this->raiz == NULL) ? false : this->raiz->busca(id); 
} 

void ArvB::insere(int id) 
{
    std::cout << "Insere " << id << "\n";

    if (this->raiz == NULL) {
        this->raiz = new NoB(this->m, true);
    } else if (this->raiz->n == this->m-1) {
        // Se raiz estiver cheia, cria nova raiz
        NoB *novaRaiz = new NoB(this->m, false);
        novaRaiz->filhos[0] = this->raiz; // Raiz antiga vira nó filho da nova raiz 
        novaRaiz->divideFilho(0); // Redistribui as chaves da raiz antiga 
        this->raiz = novaRaiz; // Atualiza raiz
    }

    this->raiz->insere(id); 
}

size_t ArvB::getAltura()
{
    return (this->raiz == NULL) ? 0 : this->raiz->getAltura();
}

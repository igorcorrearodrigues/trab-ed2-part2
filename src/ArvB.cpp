#include <iostream>

#include "../include/ArvB.hpp"

using namespace std;

ArvB::ArvB(size_t d) 
{  
    this->raiz = NULL;
    this->d = d; 
}

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

void ArvB::insere(int id) 
{ 
    cout << "Insere " << id << "\n";
    if (raiz == NULL) 
    { 
        cout << "Raiz nula\n";
        raiz = new NoB(d, true); 
        raiz->chaves[0] = id; 
        raiz->n = 1; 
        cout << "Setou nova raiz\n";
    } 
    else 
    { 
        if (raiz->n == 2*d-1) 
        { 
            cerr << "Raiz cheia, chama divide filho\n";
            NoB *novaRaiz = new NoB(d, false); 
  
            novaRaiz->filhos[0] = raiz; 
  
            novaRaiz->divideFilho(0, raiz); 
            cerr << "Dividiu filho\n";
            size_t i = 0; 
            if (novaRaiz->chaves[0] < id) 
                i++; 
            novaRaiz->filhos[i]->insereSeNaoCheio(id); 
  
            raiz = novaRaiz; 
            cout << "Inseriu e setou nova raiz\n";
        } 
        else 
            raiz->insereSeNaoCheio(id); 
    } 
} 

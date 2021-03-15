#include <iostream>

#include "../include/NoB.hpp"

using namespace std;

NoB::NoB(size_t d, bool folha)
{
    this->d = d;
    this->folha = folha;
 
    this->chaves = new int[2*d-1];
    this->filhos = new NoB *[2*d];
 
    this->n = 0;
}

NoB::~NoB()
{
    for (size_t i = 0; i < 2*d; i++)
        delete this->filhos[i];
    delete [] this->filhos;
    delete [] this->chaves;
}

void NoB::imprimeLinear()
{
    for (size_t i = 0; i < this->n; i++) 
    {
        // Percorre os nós filhos primeiro, para manter a ordem crescente
        if (!this->folha)
            filhos[i]->imprimeLinear();
        
        // Imprime as chaves atuais
        std::cout << this->chaves[i] << ", ";
    }
  
    // Percorre o último nó filho
    if (!this->folha)
        filhos[this->n]->imprimeLinear(); 
}


void NoB::imprimeEstrutura() 
{
    // Imprime as informações deste nó
    std::cout << "No " << this;
    std::cout << "\nChaves: ";
    for(size_t i = 0; i < this->n; i++)
        std::cout << this->chaves[i] << ", ";
    
    std::cout << "\nFilhos: ";
    for(size_t i = 0; i < this->n + 1; i++)
        std::cout << filhos[i] << ", ";
    std::cout << "\n";

    for (size_t i = 0; i <= this->n; i++) 
    {
        // Percorre os n filhos
        if (!this->folha)
            filhos[i]->imprimeEstrutura();
    }
}
 
bool NoB::busca(int id)
{
    int i = 0;
    while (i < (int) n && id > chaves[i])
        i++;
 
    if (chaves[i] == id)
        return true;
 
    if (this->folha)
        return false;
 
    return filhos[i]->busca(id);
}

void NoB::insereSeNaoCheio(int id) 
{ 
    int i = n-1; 
  
    if (this->folha) 
    {
        while (i >= 0 && chaves[i] > id) 
        { 
            chaves[i+1] = chaves[i]; 
            i--; 
        } 
  
        chaves[i+1] = id; 
        n = n+1; 
    } 
    else 
    { 
        while (i >= 0 && chaves[i] > id) 
            i--; 
  
        if (filhos[i+1]->n == 2*d-1) 
        { 
            divideFilho(i+1, filhos[i+1]); 
            if (chaves[i+1] < id) 
                i++; 
        } 
        filhos[i+1]->insereSeNaoCheio(id); 
    } 
} 

void NoB::divideFilho(int i, NoB *filho) 
{ 
    NoB *novoFilho = new NoB(filho->d, filho->folha); 
    novoFilho->n = d - 1; 
  
    for (size_t j = 0; j < d-1; j++) 
        novoFilho->chaves[j] = filho->chaves[j+d]; 
    cerr << "Copiou chaves\n";
  
    if (!filho->folha) 
    { 
        for (size_t j = 0; j < d; j++) 
            novoFilho->filhos[j] = filho->filhos[j+d]; 
    } 
    cerr << "Copiou filhos\n";
  
    filho->n = d - 1; 
  
    for (int j = n; j >= i+1; j--) 
        filhos[j+1] = filhos[j]; 
  
    filhos[i+1] = novoFilho; 
    cerr << "Moveu filhos para inserir na posicao\n";
  
  cerr << "n = " << this->n << "\n";
    for (int j = this->n-1; j >= i; j--) {
        cerr << "i = " << i << "\n";
        cerr << "j = " << j << "\n";
        bool condicao = j >= i;
        cerr << "j >= i ? " << condicao << "\n";
        if (j == 0)
            break;
        chaves[j+1] = chaves[j]; 
    }
  cerr << "Moveu chaves\n";
    chaves[i] = filho->chaves[d-1]; 
  
    this->n = this->n + 1; 
    cerr << "Fim\n";
} 
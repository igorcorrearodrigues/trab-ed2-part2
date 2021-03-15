#include <iostream>

#include "NoB.hpp"

using namespace std;

NoB::NoB(size_t d, bool folha, HashTable *tabela)
{
    this->d = d;
    this->folha = folha;
 
    this->chaves = new int[2*d-1];
    this->filhos = new NoB *[2*d];
 
    this->n = 0;

    this->tabela = tabela;
}

NoB::~NoB()
{
    for (size_t i = 0; i < 2*d; i++)
        delete this->filhos[i];
    delete [] this->filhos;
    delete [] this->chaves;
}

bool NoB::isFolha()
{
    return folha;
}

void NoB::imprimeLinear()
{
    for (size_t i = 0; i < this->n; i++) 
    {
        // Percorre os nós filhos primeiro, para manter a ordem crescente
        if (!isFolha())
            filhos[i]->imprimeLinear();
        
        // Imprime as chaves atuais
        std::cout << this->chaves[i] << ", ";
    }
  
    // Percorre o último nó filho
    if (!isFolha())
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
        if (!isFolha())
            filhos[i]->imprimeEstrutura();
    }
}

int NoB::compMaiorQueID(size_t info, size_t id) {
    Registro *r1 = this->tabela->get(info);
    Registro *r2 = this->tabela->get(id);
     if (r1->code() < r2->code())
        return -1;
    if (r2->code() < r1->code())
        return 1;
    if (r1->date() < r2->date())
        return -1;
    if (r2->date() < r1->date())
        return 1;
    return 0;
}

size_t NoB::procuraPosicao(int id, size_t& comps)
{
    size_t i = 0;
    while (i < this->n && (++comps) && this->compMaiorQueID(id, this->chaves[i]) > 0)
        i++;
    
    return i;
}
size_t NoB::totalCasosCidade(std::string codigo) {
    size_t totalCasos = 0;
    for (size_t i = 0; i < this->n; i++) {
        Registro *cidade = this->tabela->get(this->chaves[i]);
        if (!isFolha())
            totalCasos += filhos[i]->totalCasosCidade(codigo);
        if (cidade->code() == codigo)
            totalCasos += cidade->cases();
    }
    if (!isFolha())
        totalCasos += filhos[this->n]->totalCasosCidade(codigo);
    return totalCasos;
}

bool NoB::busca(int id, size_t& comps) 
{
    // Procura a posicao da chave
    size_t i = procuraPosicao(id, comps);
    int cR = this->compMaiorQueID(id, this->chaves[i]); 
    
    if ((++comps) && cR == 0)
        return true;
    else if (isFolha())
        return false;

    return filhos[i]->busca(id, comps);
}

void NoB::insereSeNaoCheio(int id) // Insere chave se nó nao estiver cheio
{ 
    int i = n-1; 
  
    if (isFolha()) 
    {
        while (i >= 0 && compMaiorQueID(id, this->chaves[i]) < 0) 
        { 
            chaves[i+1] = chaves[i]; 
            i--;
        } 
        chaves[i+1] = id; 
        n = n+1; 
    } 
    else 
    { 
        while (i >= 0 && compMaiorQueID(id, this->chaves[i]) < 0) 
            i--; 

        if (filhos[i+1]->n == 2*d-1) // Se filho estiver cheio
        { 
            divideFilho(i+1, filhos[i+1]); 
            if (compMaiorQueID(id, this->chaves[i+1]) > 0) 
                i++; 
        } 
        filhos[i+1]->insereSeNaoCheio(id); 
    }
} 

void NoB::divideFilho(int i, NoB *filho) // Divide filho e seta chave mediana para o pai
{ 
    NoB *novoFilho = new NoB(filho->d, filho->isFolha(), filho->tabela); 
    novoFilho->n = d - 1; 
  
    for (size_t j = 0; j < d-1; j++) 
        novoFilho->chaves[j] = filho->chaves[j+d]; 
  
    if (!filho->isFolha()) 
    { 
        for (size_t j = 0; j < d; j++) 
            novoFilho->filhos[j] = filho->filhos[j+d]; 
    } 
  
    filho->n = d - 1; 
  
    for (int j = n; j >= i+1; j--) 
        filhos[j+1] = filhos[j]; 
  
    filhos[i+1] = novoFilho; 
  
    for (int j = this->n-1; j >= i; j--) {
        if (j < 0)
            break;
        chaves[j+1] = chaves[j]; 
    }
    chaves[i] = filho->chaves[d-1]; 
  
    this->n++; 
} 

size_t NoB::getAltura()
{
    if (isFolha())
        return 0;
    
    size_t altura, maior = 0;
    for (size_t i = 0; i <= n; i++) {
        altura = filhos[i]->getAltura();
        if (maior < altura)
            maior = altura;
    }
    return maior + 1;
}

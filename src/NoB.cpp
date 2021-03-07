#include <iostream>

#include "../include/NoB.hpp"

NoB::NoB(size_t m, bool folha) 
{
    this->m = m;
    this->folha = folha;
    this->n = 0;
    this->chaves = new int[m-1];
    this->filhos = new NoB*[m];
} 

bool NoB::isFolha()
{
    return folha;
}

void NoB::atualizaN(size_t n)
{
    this->n = n;
}

size_t NoB::getN()
{
    return this->n;
}

size_t NoB::getM()
{
    return this->m;
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
    for(size_t i = 0; i < this->m; i++)
        std::cout << filhos[i] << ", ";
    std::cout << "\n";

    for (size_t i = 0; i <= this->n; i++) 
    {
        // Percorre os n filhos
        if (!isFolha())
            filhos[i]->imprimeEstrutura();
    }
}

size_t NoB::procuraPosicao(int id)
{
    size_t i = 0;
    while (i < this->n && id > this->chaves[i])
        i++;
    
    return i;
}

bool NoB::busca(int id) 
{
    // Procura a posicao da chave
    size_t i = procuraPosicao(id);

    if (this->chaves[i] == id)
        return true;
    else if (isFolha())
        return false;

    return filhos[i]->busca(id);
}

size_t NoB::procuraFilho(int id)
{
    int i = this->n - 1;
    while (i >= 0 && this->chaves[i] > id)
        i--;
    
    return i + 1;
}

void NoB::insere(int id) 
{ 
    // Se for folha, insere no nó atual
    // Condicao: nó nao deve estar cheio
    if (isFolha()) {
        int i = this->n - 1;

        // Move chaves maiores uma posicao à frente
        for ( ; i >= 0 && this->chaves[i] > id; i--)
            this->chaves[i+1] = this->chaves[i];
  
        this->chaves[i+1] = id;
        this->atualizaN(this->n + 1);

    } else {
        // Se nao for nó folha, procura nó filho
        size_t i = procuraFilho(id);

        // Verifica condicao de insercao
        // Se filho estiver cheio, divide o filho
        if (filhos[i]->n == this->m-1) {
            divideFilho(i);

            // Encontra posicao de insercao da nova chave
            if (this->chaves[i] < id) 
                i += 1;
        }

        filhos[i]->insere(id); 
    }
} 

void NoB::divideFilho(size_t i)
{
    NoB *filho = filhos[i];
    NoB *novoFilho = new NoB(filho->getM(), filho->folha);

    // Move as chaves da segunda metade do vetor para o novo filho
    for (size_t j = 0; j < (this->m-1)/2; j++)
        novoFilho->chaves[j] = std::move(filho->chaves[j+this->m/2]); 

    // Se nao for folha, move os nós filhos tambem
    if (!filho->isFolha())
        for (size_t j = 0; j <= this->m/2; j++)
            novoFilho->filhos[j] = filho->filhos[j+this->m/2];
      
    // Move os elementos maiores uma posição à frente
    for (size_t j = this->n; j > i; j--) {
        this->chaves[j] = std::move(this->chaves[j-1]);
        this->filhos[j+1] = this->filhos[j];
    }
  
    // Insere chave na posicao certa
    this->chaves[i] = std::move(filho->chaves[this->m/2-1]);
    this->filhos[i+1] = novoFilho;
    
    // Atualiza numero de chaves nos nós
    this->atualizaN(this->n + 1);
    filho->atualizaN(this->m/2-1);
    novoFilho->atualizaN((this->m-1)/2);
}

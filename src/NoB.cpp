#include <iostream>

#include "NoB.hpp"

NoB::NoB(size_t m, bool folha) 
{
    this->m = m;
    this->folha = folha;
    this->n = 0;
    this->chaves = new int[m-1];
    this->filhos = new NoB*[m];
}

NoB::~NoB()
{
    for (size_t i = 0; i < this->m; i++)
        delete this->filhos[i];
    delete [] this->filhos;
    delete [] this->chaves;
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

size_t NoB::procuraPosicao(int id, size_t& comps)
{
    size_t i = 0;
    while (i < this->n && (++comps) && id > this->chaves[i])
        i++;
    
    return i;
}

bool NoB::busca(int id, size_t& comps) 
{
    // Procura a posicao da chave
    size_t i = procuraPosicao(id, comps);

    if ((++comps) && this->chaves[i] == id)
        return true;
    else if (isFolha())
        return false;

    return filhos[i]->busca(id, comps);
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
            this->chaves[i+1] = std::move(this->chaves[i]);
  
        this->chaves[i+1] = id;
        this->atualizaN(this->n + 1);

    } else {
        // Se nao for nó folha, procura nó filho
        size_t i = procuraFilho(id);

        // Verifica condicao de insercao
        // Se filho estiver cheio, divide o filho
        if (this->filhos[i]->getN() == this->m-1)
            divideFilhoEInsere(this->filhos[i], i, id);

        else
            filhos[i]->insere(id); 
    }
} 

void NoB::divideFilhoEInsere(NoB *filho, size_t i, int id)
{
    // Se nó for raiz e filho[0] é nulo, entao atribui o filho 
    if (this->filhos[0] == NULL)
        this->filhos[0] = filho;
    
    NoB *novoFilho = new NoB(filho->getM(), filho->folha);

    // Guarda maior chave do vetor
    int maior = filho->chaves[filho->getN()-1];
    size_t j = filho->getN()-1;

    // Move chaves maiores que a chave id a ser inserida uma posicao à frente
    for ( ; j > 0 && filho->chaves[j-1] > id; j--)
        filho->chaves[j] = std::move(filho->chaves[j-1]);
    
    // Se o loop nao executou, entao a chave id é a maior das chaves
    if (j == filho->getN()-1)
        maior = id;
    else // Se encontrou a posicao de insercao da chave id, insere
        filho->chaves[j] = id;
    
    // Move as chaves da segunda metade do vetor para o novo filho
    for (j = 0; j < this->m/2-1; j++)
        novoFilho->chaves[j] = std::move(filho->chaves[j+(this->m+1)/2]);
    novoFilho->chaves[j] = maior;
    
    // Se nao for folha, move os nós filhos tambem
    if (!filho->isFolha())
        for (j = 0; j < this->m/2; j++)
            novoFilho->filhos[j] = filho->filhos[j+(this->m-1)/2+1];
    
    // Move os elementos maiores uma posição à frente
    for (j = this->n; j > i; j--) {
        this->chaves[j] = std::move(this->chaves[j-1]);
        this->filhos[j+1] = this->filhos[j];
    }
    
    // Insere chave mediana no nó pai
    this->chaves[i] = std::move(filho->chaves[(this->m-1)/2]);
    this->filhos[i+1] = novoFilho;
    
    // Atualiza numero de chaves nos nós
    this->atualizaN(this->n + 1);
    filho->atualizaN((this->m-1)/2);
    novoFilho->atualizaN(this->m/2);
}

size_t NoB::getAltura()
{
    if (isFolha())
        return 1;
    
    size_t altura, maior = 0;
    for (size_t i = 0; i <= this->n; i++) {
        altura = this->filhos[i]->getAltura();
        if (maior < altura)
            maior = altura;
    }
    return maior + 1;
}

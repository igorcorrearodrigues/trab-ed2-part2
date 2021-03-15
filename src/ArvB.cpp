#include <iostream>

#include "ArvB.hpp"

ArvB::ArvB(size_t d, HashTable *tabela) 
{  
    this->raiz = NULL;
    this->d = d; 
    this->tabela = tabela;
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

bool ArvB::busca(int id) 
{
    this->comparacoes = 0;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    bool result = (this->raiz == NULL) ? false : this->raiz->busca(id, comparacoes); 

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    this->_tempoBusca = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    return result;
} 

size_t ArvB::totalCasosCidade(std::string codigo) {
    return (raiz == NULL) ? 0 : raiz->totalCasosCidade(codigo);
}

size_t ArvB::comparacoesUltimaBusca()
{
    return this->comparacoes;
}

const std::chrono::microseconds& ArvB::tempoUltimaInsercao()
{
    return this->_tempoInsercao;
}

const std::chrono::microseconds& ArvB::tempoUltimaBusca()
{
    return this->_tempoBusca;
}

int ArvB::compMaiorQueID(size_t info, size_t id) {
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

void ArvB::insere(int id) 
{ 
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    if (raiz == NULL) 
    { 
        raiz = new NoB(this->d, true, this->tabela); 
        raiz->chaves[0] = id; 
        raiz->n = 1; 
    } 
    else 
    { 
        if (raiz->n == 2*d-1) // Se raiz estiver cheia
        { 
            NoB *novaRaiz = new NoB(this->d, false, this->tabela); 
            novaRaiz->filhos[0] = raiz; 
            novaRaiz->divideFilho(0, raiz); 

            size_t i = 0; 
            if (compMaiorQueID(id, novaRaiz->chaves[0]) > 0)
                i++; 
            novaRaiz->filhos[i]->insereSeNaoCheio(id); 
  
            raiz = novaRaiz; 
        } 
        else 
            raiz->insereSeNaoCheio(id); 
    } 

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    this->_tempoInsercao = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
} 

size_t ArvB::getAltura()
{
    return (raiz == NULL) ? 0 : raiz->getAltura();
}

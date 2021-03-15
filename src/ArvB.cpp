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
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    bool result = (this->raiz == NULL) ? false : this->raiz->busca(id, comparacoes); 

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    this->_tempoBusca = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    return result;
} 

size_t ArvB::totalCasosCidade(std::string codigo) {
    return this->raiz->totalCasosCidade(codigo);
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

void ArvB::insere(int id) 
{
    std::cout << "Insere " << id << "\n";

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    if (this->raiz == NULL) {
        std::cout << "Raiz null" << std::endl;
        this->raiz = new NoB(this->m, true, this->tabela);
        this->raiz->insere(id);
    } else if (this->raiz->getN() == this->m-1) {
        std::cout << "Raiz cheia" << std::endl;
        // Se raiz estiver cheia, cria nova raiz
        NoB *novaRaiz = new NoB(this->m, false, this->tabela);
        novaRaiz->divideFilhoEInsere(this->raiz, 0, id); // Redistribui as chaves da raiz antiga 
        this->raiz = novaRaiz; // Atualiza raiz
        std::cout << "Setou nova raiz" << std::endl;
    }
    else {
        this->raiz->insere(id);
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    this->_tempoInsercao = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
}

size_t ArvB::getAltura()
{
    return (this->raiz == NULL) ? 0 : this->raiz->getAltura();
}

#include <iostream>
#include <cassert>
#include <vector>

#include "AVLTree.hpp"

void testeArvAVLInsereEmOrdemCrescente();
void testeArvAVLInsereEmOrdemDecrescente();
void testeArvAVLInsereEmOrdemAleatoria();

int main(void)
{
    testeArvAVLInsereEmOrdemCrescente();
    testeArvAVLInsereEmOrdemDecrescente();
    testeArvAVLInsereEmOrdemAleatoria();

    return 0;
}

void testeTemplate(const std::vector<size_t>& valores)
{
    AVLTree arv;

    for (const auto& val : valores)
        arv.insere(val);
    for (const auto& val : valores)
        assert(arv.busca(val));
    assert(arv.busca(11) == false);
    arv.print(std::cout);
}

void testeArvAVLInsereEmOrdemCrescente()
{
    std::vector<size_t> valores;

    for (size_t i = 1; i <= 10; ++i)
        valores.push_back(i);
    testeTemplate(valores);
}

void testeArvAVLInsereEmOrdemDecrescente()
{
    std::vector<size_t> valores;

    for (size_t i = 10; i > 0; --i)
        valores.push_back(i);
    testeTemplate(valores);
}

void testeArvAVLInsereEmOrdemAleatoria()
{
    std::vector<size_t> valores;

    for (size_t i = 1; i <= 10; ++i)
        valores.push_back(i);

    std::vector<size_t> aleatorios;

    while (valores.size()) {
        size_t pos = random() % valores.size();
        aleatorios.push_back(valores[pos]);
        valores.erase(valores.begin() + pos);
    }

    testeTemplate(aleatorios);
}
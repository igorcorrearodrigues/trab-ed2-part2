#include <iostream>
#include <cassert>

#include "AVLTree.hpp"

int main(void)
{
    AVLTree arv;

    arv.insere(1);
    arv.insere(2);
    arv.insere(3);
    arv.insere(4);
    arv.insere(5);
    arv.insere(6);
    arv.insere(7);
    arv.insere(8);
    arv.insere(9);
    arv.insere(10);

    arv.print(std::cout);

    assert(arv.busca(1));
    assert(arv.busca(3));
    assert(arv.busca(2));
    assert(arv.busca(4));
    assert(arv.busca(5));
    assert(arv.busca(6));
    assert(arv.busca(7));
    assert(arv.busca(8));
    assert(arv.busca(9));
    assert(arv.busca(10));
    assert(arv.busca(11) == false);
    // assert(arv.getID() == 4);

    return 0;
}
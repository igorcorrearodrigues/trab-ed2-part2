#include "../include/AVLTree.hpp"

#include <cmath>

AVLTree::AVLTree() 
{
    this->setDir(nullptr);
    this->setEsq(nullptr);
    this->setFBal();
    this->id = NULL;
}

void AVLTree::setDir(AVLTree* dir) { this->dir = dir; }
void AVLTree::setEsq(AVLTree* esq) { this->esq = esq; }
void AVLTree::setFBal()
{
    this->fbal = this->getAltura(this->dir) - this->getAltura(this->esq);
}

size_t AVLTree::getAltura(AVLTree* no) {
    if (no == nullptr)
        return 0;
    return 1 + fmax(getAltura(this->dir), getAltura(this->esq));
}

void AVLTree::insere(size_t id) 
{

}
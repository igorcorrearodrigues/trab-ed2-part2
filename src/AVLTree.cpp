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
AVLTree* AVLTree::getEsq() { return this->esq; }
AVLTree* AVLTree::getDir() { return this->dir; }

void AVLTree::rotSEsq(AVLTree* noP) {
    AVLTree* noQ = noP->getDir();
    noP->setDir(noQ->getEsq());
    noQ->setEsq(noP);
}
void AVLTree::rotSDir(AVLTree* noP) {
    AVLTree* noQ = noP->getEsq();
    noP->setEsq(noQ->getDir());
    noQ->setDir(noP);
}
void AVLTree::rotDEsq(AVLTree* noP) {
    AVLTree* noQ = noP->getDir();
    AVLTree* noR = noQ->getEsq();
    noP->setDir(noR->getEsq());
    noQ->setEsq(noR->getDir());
    noR->setEsq(noP);
    noR->setDir(noQ);
}
void AVLTree::rotDDir(AVLTree* noP) {
    AVLTree* noQ = noP->getEsq();
    AVLTree* noR = noQ->getDir();
    noP->setEsq(noR->getDir());
    noQ->setDir(noR->getEsq());
    noR->setDir(noP);
    noR->setEsq(noQ);
}

void AVLTree::insere(size_t id) 
{

}
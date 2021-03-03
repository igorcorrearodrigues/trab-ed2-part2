#include "../include/AVLTree.hpp"

#include <cmath>

AVLTree::AVLTree() 
{
    this->setDir(NULL);
    this->setEsq(NULL);
    this->setFBal();
    this->id = -1;
}

void AVLTree::setID(size_t id) { this->id = id; }
void AVLTree::setDir(AVLTree* dir) { this->dir = dir; }
void AVLTree::setEsq(AVLTree* esq) { this->esq = esq; }
void AVLTree::setFBal()
{
    this->fbal = this->getAltura(this->dir) - this->getAltura(this->esq);
}

size_t AVLTree::getAltura(AVLTree* no) {
    if (no == NULL)
        return 0;
    return 1 + fmax(getAltura(this->dir), getAltura(this->esq));
}
size_t AVLTree::getID() { return this->id; }
size_t AVLTree::getFBal() { return this->fbal; }
AVLTree* AVLTree::getEsq() { return this->esq; }
AVLTree* AVLTree::getDir() { return this->dir; }

void AVLTree::rotSEsq(AVLTree* noP) {
    AVLTree* noQ = noP->getDir();
    noP->setDir(noQ->getEsq());
    noQ->setEsq(noP);

    noP->setFBal();
    noQ->setFBal();
}
void AVLTree::rotSDir(AVLTree* noP) {
    AVLTree* noQ = noP->getEsq();
    noP->setEsq(noQ->getDir());
    noQ->setDir(noP);

    noP->setFBal();
    noQ->setFBal();
}
void AVLTree::rotDEsq(AVLTree* noP) {
    AVLTree* noQ = noP->getDir();
    AVLTree* noR = noQ->getEsq();
    noP->setDir(noR->getEsq());
    noQ->setEsq(noR->getDir());
    noR->setEsq(noP);
    noR->setDir(noQ);
    
    noP->setFBal();
    noQ->setFBal();
    noR->setFBal();
}
void AVLTree::rotDDir(AVLTree* noP) {
    AVLTree* noQ = noP->getEsq();
    AVLTree* noR = noQ->getDir();
    noP->setEsq(noR->getDir());
    noQ->setDir(noR->getEsq());
    noR->setDir(noP);
    noR->setEsq(noQ);
    
    noP->setFBal();
    noQ->setFBal();
    noR->setFBal();
}

void AVLTree::insere(AVLTree* no, size_t id) 
{
    if (no == NULL) {
        no->setDir(NULL);
        no->setEsq(NULL);
        no->setID(id);
        no->setFBal();
        return;
    }
    else {
        if (id > no->getID()) {
            insere(no->getDir(), id);
        }
        else if (id < no->getID()) {
            insere(no->getEsq(), id);
        }
        else //no ja existe na arvore
            return; 
    }
    if (no->getFBal() == 2) {
        if (no->getDir()->getFBal() == -1) {
            no->rotDEsq(no);
        } 
        else {
            no->rotSEsq(no);
        } 
    }
    else if (no->getFBal() == -2) {
        if (no->getEsq()->getFBal() == 1) {
            no->rotDDir(no);
        }
        else {
            no->rotSDir(no);
        }
    }
}
#include "AVLTree.hpp"

#include <cmath>

AVLTree::AVLTree(size_t id) 
{
    this->setDir(nullptr);
    this->setEsq(nullptr);
    this->setFBal();
    this->setID(id);
}

AVLTree::~AVLTree()
{
	if (this->getDir())
		delete this->getDir();
	if (this->getEsq())
		delete this->getEsq();
}

void AVLTree::setID(size_t id)
{
    this->id = id;
}

void AVLTree::setDir(AVLTree* dir)
{
    this->dir = dir;
}

void AVLTree::setEsq(AVLTree* esq)
{
    this->esq = esq;
}

void AVLTree::setFBal()
{
    this->fbal = this->getAltura(this->dir) - this->getAltura(this->esq);
}

size_t AVLTree::getAltura(AVLTree* no) {
    if (no == nullptr)
        return 0;
    return 1 + fmax(getAltura(this->getDir()), getAltura(this->getEsq()));
}

size_t AVLTree::getID()
{
    return this->id;
}

size_t AVLTree::getFBal()
{
    return this->fbal;
}

AVLTree* AVLTree::getEsq()
{
    return this->esq;
}

AVLTree* AVLTree::getDir()
{
	  return this->dir;
}

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

static AVLTree *avlInsere(AVLTree *no, size_t id)
{
    if (no == nullptr) {
        no = new AVLTree(id);
        return no;
    } else {
        if (id > no->getID()) {
            no->setDir(avlInsere(no->getDir(), id));
        } else if (id < no->getID()) {
            no->setEsq(avlInsere(no->getEsq(), id));
        } else //no ja existe na arvore
            return no; 
    }
    if (no->getFBal() == 2) {
        if (no->getDir()->getFBal() == (size_t) -1) {
            no->rotDEsq(no);
        } 
        else {
            no->rotSEsq(no);
        } 
    }
    else if (no->getFBal() == (size_t) -2) {
        if (no->getEsq()->getFBal() == 1) {
            no->rotDDir(no);
        }
        else {
            no->rotSDir(no);
        }
    }
		return no;
}

void AVLTree::insere(size_t id) 
{
	avlInsere(this, id);
}

bool AVLTree::busca(size_t id)
{
	if (this->getID() == id)
		return true;
	if (id < this->getID())
		return (this->getEsq()) ? this->getEsq()->busca(id) : false;
	return (this->getDir()) ? this->getDir()->busca(id) : false;
}

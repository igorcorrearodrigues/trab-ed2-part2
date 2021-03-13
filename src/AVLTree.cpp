#include "AVLTree.hpp"

#include <cmath>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

AVLTree::~AVLTree()
{
    freeNodes(this->root);
}

AVLTree::AVLTree(): root(nullptr)
{
}

void AVLTree::freeNodes(AVLNode *no)
{
    if (no == nullptr)
        return;
    freeNodes(no->esq);
    freeNodes(no->dir);
    delete no;
}

AVLNode *AVLTree::insere(AVLNode *no, size_t info)
{
    if (no == nullptr) {
        return new AVLNode;
    }

    if (info > no->info) {
        no->dir = insere(no->dir, info);
    } else if (info < no->info) {
        no->esq = insere(no->esq, info);
    } else //no ja existe na arvore
        return no; 
    

    if (no->fbal == 2) {
        if (no->dir->fbal == (size_t) -1) {
            rotDEsq(no);
        } else
            rotSEsq(no);
    } else if (no->fbal == (size_t) -2) {
        if (no->esq->fbal == 1) {
            rotDDir(no);
        } else {
            rotSDir(no);
        }
    }
	return no;
}

bool AVLTree::busca(const AVLNode *no, size_t info)
{
    if (no == nullptr)
        return false;
    if (no->info == info)
        return true;
    if (info < no->info)
        return busca(no->esq, info);
    return busca(no->dir, info);
}

size_t AVLTree::calculaAltura(AVLNode *no)
{
    if (no == nullptr)
        return 0;
    return 1 + MAX(calculaAltura(no->dir), calculaAltura(no->esq));
}

void AVLTree::calculaFbal(AVLNode *no)
{
    no->fbal = calculaAltura(no->dir) - calculaAltura(no->esq);
}

void AVLTree::rotSEsq(AVLNode* noP)
{
    AVLNode* noQ = noP->dir;

    noP->dir = noQ->esq;
    noQ->esq = noP;

    calculaFbal(noP);
    calculaFbal(noQ);
}

void AVLTree::rotSDir(AVLNode* noP)
{
    AVLNode *noQ = noP->esq;
    noP->esq = noQ->dir;
    noQ->dir = noP;
    noQ->dir = noP;

    calculaFbal(noP);
    calculaFbal(noQ);
}

void AVLTree::rotDEsq(AVLNode* noP)
{
    AVLNode* noQ = noP->dir;
    AVLNode* noR = noQ->esq;

    noP->dir = noR->esq;
    noQ->esq = noR->dir;
    noR->esq = noP;
    noR->dir = noQ;

    calculaFbal(noP);
    calculaFbal(noQ);
    calculaFbal(noR);
}

void AVLTree::rotDDir(AVLNode* noP)
{
    AVLNode* noQ = noP->esq;
    AVLNode* noR = noQ->dir;

    noP->esq = noR->dir;
    noQ->dir = noR->esq;
    noQ->dir = noP;
    noR->esq = noQ;

    calculaFbal(noP);
    calculaFbal(noQ);
    calculaFbal(noR);
}

void AVLTree::insere(size_t id) 
{
    this->root = insere(root, id);
}

bool AVLTree::busca(size_t id)
{
    return busca(this->root, id);
}

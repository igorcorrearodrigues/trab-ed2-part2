#include "AVLTree.hpp"

#include <cmath>
#include <algorithm>

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
        no = new AVLNode;
        no->info = info;
        return no;
    }

    if (info > no->info) {
        no->dir = insere(no->dir, info);
    } else if (info < no->info) {
        no->esq = insere(no->esq, info);
    } else //no ja existe na arvore
        return no; 
    
    calculaFbal(no);

    if (no->fbal == 2) {
        if (no->dir->fbal == -1) {
            no = rotDEsq(no);
        } else
            no = rotSEsq(no);
    } else if (no->fbal == -2) {
        if (no->esq->fbal == 1) {
            no = rotDDir(no);
        } else {
            no = rotSDir(no);
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

long AVLTree::calculaAltura(AVLNode *no)
{
    if (no == nullptr)
        return 0;
    return 1 + std::max(calculaAltura(no->dir), calculaAltura(no->esq));
}

void AVLTree::calculaFbal(AVLNode *no)
{
    no->fbal = calculaAltura(no->dir) - calculaAltura(no->esq);
}

AVLNode *AVLTree::rotSEsq(AVLNode *noP)
{
    AVLNode *noQ = noP->dir;

    noP->dir = noQ->esq;
    noQ->esq = noP;

    calculaFbal(noP);
    calculaFbal(noQ);

    return noQ;
}

AVLNode *AVLTree::rotSDir(AVLNode *noP)
{
    AVLNode *noQ = noP->esq;
    noP->esq = noQ->dir;
    noQ->dir = noP;
    noQ->dir = noP;

    calculaFbal(noP);
    calculaFbal(noQ);

    return noQ;
}

AVLNode *AVLTree::rotDEsq(AVLNode *noP)
{
    AVLNode *noQ = noP->dir;
    AVLNode *noR = noQ->esq;

    noP->dir = noR->esq;
    noQ->esq = noR->dir;
    noR->esq = noP;
    noR->dir = noQ;

    calculaFbal(noP);
    calculaFbal(noQ);
    calculaFbal(noR);

    return noR;
}

AVLNode *AVLTree::rotDDir(AVLNode *noP)
{
    AVLNode *noQ = noP->esq;
    AVLNode *noR = noQ->dir;

    noP->esq = noR->dir;
    noQ->dir = noR->esq;
    noQ->dir = noP;
    noR->esq = noQ;

    calculaFbal(noP);
    calculaFbal(noQ);
    calculaFbal(noR);

    return noR;
}

void AVLTree::insere(size_t id) 
{
    this->root = insere(root, id);
}

std::ostream& AVLTree::avlNodePrint(std::string prefix, const AVLNode *node, std::ostream& out, bool isLeft)
{
    if (node != nullptr) {
        out << prefix;

        out << (isLeft ? "├──" : "└──" );

        // print the value of the node
        out << node->info << '\n';

        // enter the next tree level - left and right branch
        avlNodePrint(prefix + (isLeft ? "│   " : "    "), node->esq, out, true);
        avlNodePrint(prefix + (isLeft ? "│   " : "    "), node->dir, out, false);
    }
    return out;
}

bool AVLTree::busca(size_t id) const
{
    return busca(this->root, id);
}

std::ostream& AVLTree::print(std::ostream& stream) const
{
    return avlNodePrint("", this->root, stream, false);
}
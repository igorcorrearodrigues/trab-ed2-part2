#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <cmath>

class AVLTree 
{
    private:
        size_t id;
        AVLTree* esq;
        AVLTree* dir;
        size_t fbal;
    public:
        AVLTree(size_t id);

        void setID(size_t id);
        void setEsq(AVLTree* esq);
        void setDir(AVLTree* dir);
        void setFBal();

        size_t getAltura(AVLTree* no);
        size_t getID();
        size_t getFBal();
        AVLTree* getDir();
        AVLTree* getEsq();

        void rotSDir(AVLTree* noP);
        void rotSEsq(AVLTree* noP);
        void rotDDir(AVLTree* noP);
        void rotDEsq(AVLTree* noP);

        void insere(AVLTree* no, size_t id);
        bool busca(AVLTree* no, size_t id);
};

#endif // AVLTREE_HPP

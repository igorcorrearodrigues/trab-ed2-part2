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
        AVLTree();

        void setEsq(AVLTree* esq);
        void setDir(AVLTree* dir);
        void setFBal();

        size_t getAltura(AVLTree* no);

        void rotSDir(AVLTree* noP);
        void rotSEsq(AVLTree* noP);

        void insere(size_t id);
};

#endif // AVLTREE_HPP

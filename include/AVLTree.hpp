#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "AVLNode.hpp"

class AVLTree 
{
private:
	AVLNode *root;

	static void freeNodes(AVLNode *no);
	static AVLNode *insere(AVLNode *no, size_t info);
	static bool busca(const AVLNode *no, size_t info);
	static size_t calculaAltura(AVLNode *no);
	static void calculaFbal(AVLNode *no);
    static void rotSDir(AVLNode* noP);
    static void rotSEsq(AVLNode* noP);
    static void rotDDir(AVLNode* noP);
    static void rotDEsq(AVLNode* noP);
public:
    AVLTree();
    ~AVLTree();

    void setFBal();

    size_t getAltura(AVLTree* no);
    size_t getID();
    size_t getFBal();


    void insere(size_t id);
    bool busca(size_t id);
};

#endif // AVLTREE_HPP

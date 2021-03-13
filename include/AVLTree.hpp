#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "AVLNode.hpp"

#include <ostream>

class AVLTree 
{
private:
	AVLNode *root;

	static void freeNodes(AVLNode *no);
	static AVLNode *insere(AVLNode *no, size_t info);
    static AVLNode *rotSDir(AVLNode *noP);
    static AVLNode *rotSEsq(AVLNode *noP);
    static AVLNode *rotDDir(AVLNode *noP);
    static AVLNode *rotDEsq(AVLNode *noP);
	static bool busca(const AVLNode *no, size_t info);
	static long calculaAltura(AVLNode *no);
	static void calculaFbal(AVLNode *no);
    static std::ostream& avlNodePrint(std::string prefix, const AVLNode *no,
                                        std::ostream& out, bool isLeft);

public:
    AVLTree();
    ~AVLTree();

    void insere(size_t id);
    bool busca(size_t id) const;

    std::ostream& print(std::ostream& stream) const;
};

inline std::ostream& operator<<(std::ostream& out, const AVLTree& arv)
{
    return arv.print(out);
}

#endif // AVLTREE_HPP

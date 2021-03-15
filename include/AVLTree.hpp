#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "AVLNode.hpp"
#include "Registro.hpp"
#include "HashTable.hpp"

#include <ostream>
#include <chrono>

class AVLTree 
{
private:
	AVLNode *root;
    HashTable *tabela;

    size_t _comparacoesUltimaBusca;
    std::chrono::microseconds _tempoUltimaBusca;
    std::chrono::microseconds _tempoUltimaInsercao;

	static void freeNodes(AVLNode *no);
	AVLNode *insere(AVLNode *no, size_t info);
    static AVLNode *rotSDir(AVLNode *noP);
    static AVLNode *rotSEsq(AVLNode *noP);
    static AVLNode *rotDDir(AVLNode *noP);
    static AVLNode *rotDEsq(AVLNode *noP);
	bool busca(const AVLNode *no, size_t info, size_t& comps);
	static long calculaAltura(AVLNode *no);
	static void calculaFbal(AVLNode *no);
    int compMaiorQueID(size_t info, size_t id);
    int totalCasosCidade(AVLNode *no, std::string codigo);
    static std::ostream& avlNodePrint(std::string prefix, const AVLNode *no,
                                        std::ostream& out, bool isLeft);

public:
    AVLTree(HashTable *tabela);
    ~AVLTree();

    void insere(size_t id);
    bool busca(size_t id);
    int totalCasosCidade(std::string codigo);

    size_t comparacoesUltimaBusca();
    const std::chrono::microseconds& tempoUltimaBusca();
    const std::chrono::microseconds& tempoUltimaInsercao();

    std::ostream& print(std::ostream& stream) const;
};

inline std::ostream& operator<<(std::ostream& out, const AVLTree& arv)
{
    return arv.print(out);
}

#endif // AVLTREE_HPP

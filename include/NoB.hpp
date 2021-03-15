#ifndef NOB_HPP
#define NOB_HPP

class NoB
{
    int *chaves;
    size_t d;
    NoB **filhos;
    size_t n;
    bool folha;
public:
    NoB(size_t d, bool folha);
    ~NoB();
 
    bool isFolha();
    void imprimeLinear(); // Imprime as chaves em ordem crescente
    void imprimeEstrutura(); // Imprime a estrutura da arvore
 
    bool busca(int id);
    void insereSeNaoCheio(int id); 
    void divideFilho(int i, NoB *filho); 

    size_t getAltura();

friend class ArvB;
};

#endif /* NOB_HPP */
#ifndef NOB_HPP
#define NOB_HPP

class NoB 
{ 
    int *chaves;
    size_t m; // Numero maximo de filhos 
    NoB **filhos; // Vetor de ponteiros para os filhos
    size_t n; // Numero de chaves preenchidas
    bool folha;

    void atualizaN(size_t n);
    size_t procuraPosicao(int id, size_t& comps); // Procura posicao da chave
    size_t procuraFilho(int id); // Procura posicao do nó filho
    
public: 
    NoB(size_t m, bool folha);
    ~NoB();

    size_t getN();
    size_t getM();

    bool isFolha();
    bool busca(int id, size_t& comps);
    void insere(int id); // Insere chave no nó se nao estiver cheio
    
    // Divide nó filho de indice i quando ele estiver cheio e insere a chave
    void divideFilhoEInsere(NoB *filho, size_t i, int id); 
  
    void imprimeLinear(); // Imprime as chaves em ordem crescente
    void imprimeEstrutura(); // Imprime a estrutura da arvore

    size_t getAltura();
}; 

#endif /* NOB_HPP */
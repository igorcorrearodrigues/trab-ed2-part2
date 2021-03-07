#ifndef NOB_HPP
#define NOB_HPP

class NoB 
{ 
    int *chaves;
    size_t m; // Numero maximo de filhos 
    NoB **filhos;
    size_t n; // Numero de chaves preenchidas
    bool folha;

    void atualizaN(size_t n);
    size_t procuraPosicao(int id); // Procura posicao da chave
    size_t procuraFilho(int id); // Procura posicao do nó filho
    
public: 
    NoB(size_t m, bool folha);
  
    size_t getN();
    size_t getM();

    bool isFolha();
    bool busca(int id);
    void insere(int id); // Insere chave no nó se nao estiver cheio
    void divideFilho(size_t i); // Divide nó filho de indice i quando ele estiver cheio
  
    void imprimeLinear(); // Imprime as chaves em ordem crescente
    void imprimeEstrutura(); // Imprime a estrutura da arvore

friend class ArvB; 
}; 

#endif /* NOB_HPP */
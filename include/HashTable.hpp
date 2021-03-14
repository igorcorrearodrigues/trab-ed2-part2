#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#define TABLE_M 1431490

#include "Registro.hpp"
#include <vector>

struct No
{
	const static size_t STATUS_LIVRE    = 1;
	const static size_t STATUS_OCUPADO  = 2;
	const static size_t STATUS_REMOVIDO = 3;

	Registro info;
	char status;

	No();
};

class HashTable
{
private:
	No *tabela;
	std::vector<size_t> hashes;

	No *_buscar(std::string codigo, std::string data);

public:
	HashTable();
	~HashTable();

	bool insere(const Registro& r);
	Registro *buscar(std::string codigoDaCidade, std::string data);
	void remover(std::string codigoDaCidade, std::string data);
	std::vector<size_t> getRandomHashes(size_t n);
};

#endif // HASH_TABLE_HPP

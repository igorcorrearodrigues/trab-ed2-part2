#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <unordered_map>

#include "Registro.hpp"

class HashTable
{
private:
	std::unordered_map<std::string, Registro> table;

public:
	size_t tamanho() const;

	void insere(const Registro& r);
	const Registro& buscar(std::string codigoDaCidade, std::string data);
	void remover(std::string codigoDaCidade, std::string data);
};

#endif // HASH_TABLE_HPP

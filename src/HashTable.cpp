#include "HashTable.hpp"

static std::string gerarChave(std::string codigo, std::string data)
{
	return codigo + '-' + data;
}

size_t HashTable::tamanho() const
{
	return this->table.size();
}

void HashTable::insere(const Registro& r)
{
	std::string chave = gerarChave(r.code(), r.date());
	this->table[chave] = r;
}

const Registro& HashTable::buscar(std::string codigo, std::string data)
{
	return this->table[gerarChave(codigo, data)];
}

void HashTable::remover(std::string codigo, std::string data)
{
	this->table.erase(gerarChave(codigo, data));
}

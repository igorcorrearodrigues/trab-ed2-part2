#include "HashTable.hpp"

#define _INSERE(no, r) do { no.info = r; no.status = No::STATUS_OCUPADO; } while (0)

static size_t h1(std::string codigo, std::string data)
{
	std::string s = codigo + data;
	size_t hash = 0;

	for (auto c : s) {
		hash = hash * 256 + c;
	}
	return hash;
}

static size_t h2(std::string codigo, std::string data)
{
	std::string s = codigo + data;
	size_t hash = 0;

	size_t pos = 0;
	for (auto c : s) {
		hash += (c + 31 * pos++);
	}
	return hash;
}

static size_t getPos(std::string codigo, std::string data, size_t i)
{
	if (i == 0)
		return h1(codigo, data) % TABLE_M;
	return (h1(codigo, data) + i * h2(codigo, data)) % TABLE_M;
}

static size_t getPos(const Registro& r, size_t i)
{
	return getPos(r.code(), r.date(), i);
}

bool HashTable::insere(const Registro& r)
{
	for (size_t i = 0; i < TABLE_M; ++i) {
		size_t pos = getPos(r, i);

		if (this->tabela[pos].status != No::STATUS_OCUPADO) {
			_INSERE(this->tabela[pos], r);
			return true;
		}
	}
	return false;
}

HashTable::No *HashTable::_buscar(std::string codigo, std::string data)
{
	for (size_t i = 0; i < TABLE_M; ++i) {
		No *no = this->tabela + getPos(codigo, data, i);

		if (no->status == No::STATUS_LIVRE)
			break;
		if (no->status == No::STATUS_OCUPADO) {
			const Registro& info = no->info;

			if (info.code() == codigo && info.date() == data)
				return no;
		}
	}
	return nullptr;
}

Registro* HashTable::buscar(std::string codigo, std::string data)
{
	No *noptr;

	if ((noptr = this->_buscar(codigo, data)) == nullptr)
		return nullptr;
	return &(noptr->info);
}

void HashTable::remover(std::string codigo, std::string data)
{
	No *noptr;

	if ((noptr = this->_buscar(codigo, data)) != nullptr) {
		noptr->status = No::STATUS_REMOVIDO;
	}
}

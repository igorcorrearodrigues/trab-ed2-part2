#include "Cidade.hpp"

const std::string& Cidade::nome() const
{
	return this->_nome;
}

double Cidade::latitude() const
{
	return this->_latitude;
}

double Cidade::longitude() const
{
	return this->_longitude;
}

unsigned Cidade::codigo() const
{
	return this->_codigo;
}

uint8_t Cidade::codigoDoEstado() const
{
	return this->_codigoDoEstado;
}

bool Cidade::isCapital() const
{
	return this->_isCapital;
}

std::ostream& Cidade::print(std::ostream& out) const
{
	// state_code,city_code,city_name,lat,long,capital
	return out << this->codigoDoEstado() << ',' << this->codigo() << ','
		<< this->nome() << ',' << this->latitude() << ','
		<< this->longitude() << ','
		<< ((this->isCapital()) ? "TRUE" : "FALSE");
}

std::istream& Cidade::read(std::istream& in)
{
	throw "Not yet implemented";
	return in;
}

#include "Cidade.hpp"
#include "utils.hpp"

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

const std::string& Cidade::codigo() const
{
	return this->_codigo;
}

int Cidade::codigoDoEstado() const
{
	return this->_codigoDoEstado;
}

bool Cidade::isCapital() const
{
	return this->_isCapital;
}

void Cidade::setNome(const std::string& nome)
{
	this->_nome = nome;
}

void Cidade::setLatitude(double latitude)
{
	this->_latitude = latitude;
}

void Cidade::setLongitude(double longitude)
{
	this->_longitude = longitude;
}

void Cidade::setCodigo(const std::string& codigo)
{
	this->_codigo = codigo;
}

void Cidade::setCodigoDoEstado(int codigo)
{
	this->_codigoDoEstado = codigo;
}

void Cidade::setCapital(bool isCapital)
{
	this->_isCapital = isCapital;
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
	std::string line;
	size_t pos = 0;

	if (std::getline(in, line)) {
		// state_code,city_code,city_name,lat,long,capital
		this->setCodigoDoEstado(std::stoi(string_tok(line, ',', &pos)));
		this->setCodigo(string_tok(line, ',', &pos));
		this->setNome(string_tok(line, ',', &pos));
		this->setLatitude(std::stod(string_tok(line, ',', &pos)));
		this->setLongitude(std::stod(string_tok(line, ',', &pos)));
		this->setCapital(string_tok(line, ',', &pos) == "TRUE");
	}
	return in;
}

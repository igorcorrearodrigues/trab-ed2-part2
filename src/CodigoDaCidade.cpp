#include "CodigoDaCidade.hpp"

CodigoDaCidade::CodigoDaCidade(): _code("")
{
}

CodigoDaCidade::CodigoDaCidade(const std::string& code):
    _code(code)
{
}

void CodigoDaCidade::set(const std::string& code)
{
    this->_code = code;
    if (this->_code.size() > 6)
        this->_code.resize(6);
}

const std::string& CodigoDaCidade::toString() const
{
    return this->_code;
}

CodigoDaCidade::operator const std::string&() const
{
    return this->_code;
}

CodigoDaCidade& CodigoDaCidade::operator=(const std::string& code)
{
    this->set(code);
    return (*this);
}
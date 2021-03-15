#ifndef CODIGO_DA_CIDADE_HPP
#define CODIGO_DA_CIDADE_HPP

#include <string>

class CodigoDaCidade
{
private:
    std::string _code;

public:
    CodigoDaCidade();
    CodigoDaCidade(const std::string& code);

    void set(const std::string& code);
    const std::string& toString() const;
    operator const std::string&() const;
    CodigoDaCidade& operator=(const std::string& code);
};

#endif // CODIGO_DA_CIDADE_HPP
#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>   // strtod, strtol
#include <limits>    // numeric_limits
#include <cmath>     // isnan, isinf (ou implementação manual se necessário)
#include <cctype>    // isprint, isdigit

// Helper para verificar se double é realmente int
static bool isPseudoLiteral(const std::string& s)
{
    return (s == "nan" || s == "nanf" || 
            s == "+inf" || s == "inf" || s == "+inff" || s == "inff" ||
            s == "-inf" || s == "-inff");
}

static bool isCharLiteral(const std::string& s)
{
    return (s.length() == 3 && s[0] == '\'' && s[2] == '\'');
}

static bool isIntLiteral(const std::string& s)
{
    if (s.empty() || isPseudoLiteral(s) || isCharLiteral(s))
        return false;
    
    size_t start = (s[0] == '-' || s[0] == '+') ? 1 : 0;
    if (start >= s.length())
        return false;
    
    for (size_t i = start; i < s.length(); ++i)
    {
        if (!std::isdigit(s[i]) && s[i] != 'f') // 'f' permitido temporariamente para análise
            return false;
    }
    return (s.find('.') == std::string::npos && s.find('f') == std::string::npos);
}

/*static bool isFloatLiteral(const std::string& s)
{
    return (s.length() > 1 && s[s.length() - 1] == 'f' && !isCharLiteral(s));
}*/

void ScalarConverter::convert(const std::string& literal)
{
    // === 1. Pseudo-literais ===
    if (literal == "nan" || literal == "nanf")
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
        return;
    }
    if (literal == "+inf" || literal == "inf" || literal == "+inff" || literal == "inff")
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
        return;
    }
    if (literal == "-inf" || literal == "-inff")
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
        return;
    }

    // === 2. Char literal ===
    if (isCharLiteral(literal))
    {
        char c = literal[1];
        
        // Char
        std::cout << "char: ";
        if (std::isprint(static_cast<unsigned char>(c)))
            std::cout << "'" << c << "'";
        else
            std::cout << "Non displayable";
        std::cout << std::endl;

        // Int - usando static_cast explicitamente
        std::cout << "int: " << static_cast<int>(c) << std::endl;

        // Float - static_cast + formatação precisa
        std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;

        // Double - static_cast + formatação precisa
        std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
        return;
    }

    // === 3. Conversão numérica com strtod (C++98 compliant) ===
    char* endptr = NULL;
    double dValue = ::strtod(literal.c_str(), &endptr);
    
    // Verificar se conversão foi válida
    bool validConversion = (endptr != literal.c_str() && *endptr == '\0');
    bool isFloatSuffix = (literal.size() > 0 && literal[literal.size() - 1] == 'f');
    
    if (isFloatSuffix)
    {
        std::string withoutF = literal.substr(0, literal.size() - 1);
        dValue = ::strtod(withoutF.c_str(), &endptr);
        validConversion = (endptr != withoutF.c_str() && *endptr == '\0');
    }

    if (!validConversion && !isIntLiteral(literal))
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    // === 4. Impressões com casts explícitos ===
    
    // Char
    std::cout << "char: ";
    if (dValue < static_cast<double>(std::numeric_limits<char>::min()) ||
        dValue > static_cast<double>(std::numeric_limits<char>::max()) ||
        std::floor(dValue) != dValue)
    {
        std::cout << "impossible";
    }
    else
    {
        char c = static_cast<char>(static_cast<int>(dValue)); // static_cast duplo para demonstrar
        if (std::isprint(static_cast<unsigned char>(c)))
            std::cout << "'" << c << "'";
        else
            std::cout << "Non displayable";
    }
    std::cout << std::endl;

    // Int
    std::cout << "int: ";
    if (dValue < static_cast<double>(std::numeric_limits<int>::min()) ||
        dValue > static_cast<double>(std::numeric_limits<int>::max()) ||
        std::floor(dValue) != dValue)
    {
        std::cout << "impossible";
    }
    else
    {
        std::cout << static_cast<int>(dValue);
    }
    std::cout << std::endl;

    // Float
    std::cout << "float: ";
    float fValue = static_cast<float>(dValue);
    if (dValue < static_cast<double>(-std::numeric_limits<float>::max()) ||
        dValue > static_cast<double>(std::numeric_limits<float>::max()))
    {
        std::cout << "impossible";
    }
    else
    {
        // Formatação manual para evitar problemas com locales
        if (fValue == static_cast<float>(static_cast<int>(fValue)))
            std::cout << fValue << ".0f";
        else
            std::cout << fValue << "f";
    }
    std::cout << std::endl;

    // Double
    std::cout << "double: ";
    if (dValue == static_cast<double>(static_cast<int>(dValue)))
        std::cout << dValue << ".0";
    else
        std::cout << dValue;
    std::cout << std::endl;
}

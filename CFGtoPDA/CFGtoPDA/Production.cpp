#include "Production.h"

std::string Production::getU() const
{
    return U;
}
std::string Production::getV() const
{
    return V;
}

std::istream& operator>>(std::istream& in, Production& production)
{
    in >> production.U >> production.V;
    return in;
}

std::ostream& operator<<(std::ostream& os, Production& production)
{
    os << production.U << "->" << production.V;
    return os;
}

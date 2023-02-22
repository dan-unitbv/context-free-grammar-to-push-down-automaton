#pragma once
#include <iostream>
#include <string>
class Production {
private:
    std::string U;
    std::string V;
public:
    Production() = default;
    ~Production() = default;

    std::string getU() const;
    std::string getV() const;

    void setU(const std::string& u)
    {
        U = u;
    }
    void setV(const std::string& v)
    {
        V = v;
    }

    friend std::istream& operator>>(std::istream& in, Production& production);
    friend std::ostream& operator<<(std::ostream& os, Production& production);
};
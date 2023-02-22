#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "Production.h"
class Grammar
{
private:
    std::unordered_set<char> nonterminals;
    std::unordered_set<char> terminals;
    char start_symbol;
    std::vector<Production> productions;
public:

    Grammar() = default;

    ~Grammar() = default;

    Grammar(const std::vector<char>& nonterminals, const std::vector<char>& terminals, char& start_symbol, const std::vector<Production>& productions) :
        nonterminals{ nonterminals.begin(), nonterminals.end() },
        terminals{ terminals.begin(), terminals.end() },
        start_symbol{ start_symbol },
        productions{ productions.begin(), productions.end() } {
    }

    const std::unordered_set<char>& getNonterminals() const
    {
        return nonterminals;
    }

    void setNonterminals(const std::unordered_set<char>& nonterminals)
    {
        Grammar::nonterminals = nonterminals;
    }

    const std::unordered_set<char>& getTerminals() const
    {
        return terminals;
    }

    void setTerminals(const std::unordered_set<char>& terminals)
    {
        Grammar::terminals = terminals;
    }

    char getStartSymbol() const
    {
        return start_symbol;
    }

    void setStartSymbol(char start_symbol)
    {
        Grammar::start_symbol = start_symbol;
    }

    const std::vector<Production>& getProductions() const
    {
        return productions;
    }

    void setProductions(const std::vector<Production>& productions)
    {
        Grammar::productions = productions;
    }

    bool VerifyGrammar();
    void ReadGrammar();
    void PrintGrammar();
    bool IsCFG();
    void SimplifyGrammar();
    void FirstSimplifyGrammar();
    void SecondSimplifyGrammar();
    void ThirdSimplifyGrammar();
    void ConvertToGNF();
};
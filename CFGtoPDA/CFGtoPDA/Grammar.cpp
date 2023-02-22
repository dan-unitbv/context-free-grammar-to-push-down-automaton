#include "Grammar.h"

bool Grammar::VerifyGrammar()
{
    if (nonterminals.size() == 0 || terminals.size() == 0)
        return false;

    if (nonterminals.find(start_symbol) == nonterminals.end())
        return false;

    for (auto& nonterminal : nonterminals)
    {
        if (terminals.find(nonterminal) != terminals.end())
            return false;
    }

    for (auto& terminal : terminals)
    {
        if (nonterminals.find(terminal) != nonterminals.end())
            return false;
    }

    bool startSymbolProduction = false;
    for (auto& production : productions) {
        if (production.getU().length() == 1 && production.getU()[0] == 'S')
        {
            startSymbolProduction = true;
        }
    }
    if (startSymbolProduction == false)
        return false;

    bool minOneNonterminal = false;
    for (auto& production : productions)
    {
        for (int i = 0; i < production.getU().length(); i++)
        {
            if (nonterminals.find(production.getU()[i]) == nonterminals.end())
            {
                if (terminals.find(production.getU()[i]) == terminals.end())
                    return false;
            }
            else
                minOneNonterminal = true;
        }
        if (production.getV().length() == 0 || production.getU().length() == 0)
            return false;
    }
    if (minOneNonterminal == false)
        return false;
    return true;
}

void Grammar::ReadGrammar()
{
    std::ifstream fin("grammar.txt");

    int nr_nonterminals, nr_terminals, nr_productions;

    char nonterminal;
    fin >> nr_nonterminals;

    for (int i = 0; i < nr_nonterminals; i++)
    {
        fin >> nonterminal;
        nonterminals.insert(nonterminal);
    }

    char terminal;
    fin >> nr_terminals;

    for (int i = 0; i < nr_terminals; i++)
    {
        fin >> terminal;
        terminals.insert(terminal);
    }

    fin >> start_symbol;

    std::string u;
    std::string v;
    fin >> nr_productions;

    for (int i = 0; i < nr_productions; i++)
    {
        Production production;
        fin >> production;
        productions.push_back(production);
    }

    fin.close();
}

void Grammar::PrintGrammar()
{
    std::cout << "nonterminals: ";
    for (auto& nonterminal : nonterminals)
    {
        std::cout << nonterminal << " ";
    }
    std::cout << std::endl;

    std::cout << "terminals: ";
    for (auto& terminal : terminals)
    {
        std::cout << terminal << " ";
    }
    std::cout << std::endl;

    std::cout << "start symbol: ";
    std::cout << start_symbol;
    std::cout << std::endl;

    std::cout << "productions: ";
    for (auto& production : productions)
    {
        std::cout << production << " ";
    }
    std::cout << std::endl;
}

bool Grammar::IsCFG()
{
    for (auto& production : productions)
    {
        if (production.getU().length() != 1)
        {
            return false;
        }

        if (nonterminals.find(production.getU()[0]) == nonterminals.end())
            return false;

        for (int i = 0; i < production.getV().length(); i++)
        {
            if (nonterminals.find(production.getV()[i]) == nonterminals.end())
                if (terminals.find(production.getV()[i]) == terminals.end())
                    return false;
        }
    }

    return true;
}

void Grammar::FirstSimplifyGrammar()
{
    std::unordered_set<char> doGenerateTerminals;

    for (auto& production : productions)
    {
        if (production.getV().length() == 1)
        {
            if (terminals.find(production.getV()[0]) != terminals.end())
            {
                doGenerateTerminals.insert(production.getU()[0]);
            }
        }
    }

    while (true)
    {
        int size = doGenerateTerminals.size();
        for (auto& production : productions)
        {
            bool terminalOrGeneratesTerminal = true;
            for (auto& character : production.getV())
            {
                if (terminals.find(character) == terminals.end() && doGenerateTerminals.find(character) == doGenerateTerminals.end())
                {
                    terminalOrGeneratesTerminal = false;
                }
            }
            if (terminalOrGeneratesTerminal == true)
            {
                doGenerateTerminals.insert(production.getU()[0]);
            }
        }
        if (doGenerateTerminals.size() == size)
        {
            break;
        }
    }

    std::vector<int> positionsToRemove;

    for (auto production = productions.begin(); production != productions.end(); production++)
    {
        if (doGenerateTerminals.find((*production).getU()[0]) == doGenerateTerminals.end())
        {
            if(std::find(positionsToRemove.begin(), positionsToRemove.end(), production - productions.begin()) == positionsToRemove.end())
                positionsToRemove.push_back(production - productions.begin());
        }
        else
        {
            for (auto& character : (*production).getV())
            {
                if (doGenerateTerminals.find(character) == doGenerateTerminals.end() && nonterminals.find(character) != nonterminals.end())
                {
                    if (std::find(positionsToRemove.begin(), positionsToRemove.end(), production - productions.begin()) == positionsToRemove.end())
                        positionsToRemove.push_back(production - productions.begin());
                }
            }
        }
    }

    int j = 0;

    for (auto& position : positionsToRemove)
    {
        productions.erase(productions.begin() + position);
        for (int i = j; i < positionsToRemove.size(); i++)
        {
            positionsToRemove[i]--;
        }
        j++;
    }

    std::vector<char> nonterminalsToRemove;

    for (auto& nonterminal : nonterminals)
    {
        bool isUsed = false;
        for (auto& production : productions)
        {
            if (production.getU()[0] == nonterminal)
                isUsed = true;
        }
        if (isUsed == false)
            nonterminalsToRemove.push_back(nonterminal);
    }
    for (int i = 0; i < nonterminalsToRemove.size(); i++)
    {
        nonterminals.erase(nonterminalsToRemove[i]);
    }
}

void Grammar::SecondSimplifyGrammar()
{
    std::unordered_set<char> areAccesible;

    areAccesible.insert(start_symbol);

    while (true)
    {
        int size = areAccesible.size();
        for (auto& production : productions)
        {
            if (areAccesible.find(production.getU()[0]) != areAccesible.end())
            {
                for (auto& character : production.getV())
                {
                    if (nonterminals.find(character) != nonterminals.end())
                    {
                        areAccesible.insert(character);
                    }
                }
            }
        }
        if (areAccesible.size() == size)
        {
            break;
        }
    }

    std::vector<int> positionsToRemove;

    for (auto production = productions.begin(); production != productions.end(); production++)
    {
        if (areAccesible.find((*production).getU()[0]) == areAccesible.end())
        {
            if (std::find(positionsToRemove.begin(), positionsToRemove.end(), production - productions.begin()) == positionsToRemove.end())
                positionsToRemove.push_back(production - productions.begin());
        }
        else
        {
            for (auto character : (*production).getV())
            {
                if (areAccesible.find(character) == areAccesible.end() && nonterminals.find(character) != nonterminals.end())
                {
                    if (std::find(positionsToRemove.begin(), positionsToRemove.end(), production - productions.begin()) == positionsToRemove.end())
                        positionsToRemove.push_back(production - productions.begin());
                }
            }
        }
    }

    int j = 0;

    for (auto& position : positionsToRemove)
    {
        productions.erase(productions.begin() + position);
        for (int i = j; i < positionsToRemove.size(); i++)
        {
            positionsToRemove[i]--;
        }
        j++;
    }

    std::vector<char> nonterminalsToRemove;

    for (auto& nonterminal : nonterminals)
    {
        bool isUsed = false;
        for (auto& production : productions)
        {
            if (production.getU()[0] == nonterminal)
                isUsed = true;
        }
        if (isUsed == false)
            nonterminalsToRemove.push_back(nonterminal);
    }
    for (int i = 0; i < nonterminalsToRemove.size(); i++)
    {
        nonterminals.erase(nonterminalsToRemove[i]);
    }
}

void Grammar::ThirdSimplifyGrammar()
{

}

void Grammar::SimplifyGrammar()
{
    FirstSimplifyGrammar();
    SecondSimplifyGrammar();
}

void Grammar::ConvertToGNF()
{

}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include "Production.h"
#include "Grammar.h"
#include "PushDownAutomaton.h"

auto CFGtoPDA(Grammar g)
{
    auto states = std::vector<char>{};
    auto alphabet = std::vector<char>{ g.getTerminals().begin(), g.getTerminals().end() };
    auto alphabetPDA = std::vector<char>{ g.getNonterminals().begin(), g.getNonterminals().end() };
    auto transitions = std::vector<std::pair<std::tuple<char, char, char>, std::pair<char, std::string>>>{};
    char initial_state = 'q';
    char initial_statePDA = g.getStartSymbol();
    states.push_back(initial_state);
    char lambda = '$';

    for (auto& production : g.getProductions()) {
        if (production.getV().size() == 1)
        {
            std::tuple<char, char, char> transition_tuple;
            std::pair<char, std::string> transition_pair;
            std::get<0>(transition_tuple) = initial_state;
            std::get<1>(transition_tuple) = production.getV()[0];
            std::get<2>(transition_tuple) = production.getU()[0];

            transition_pair.first = initial_state;
            transition_pair.second = lambda;

            transitions.emplace_back(std::make_pair(transition_tuple, transition_pair));
        }
        else
        {
            std::tuple<char, char, char> transition_tuple;
            std::pair<char, std::string> transition_pair;
            std::get<0>(transition_tuple) = initial_state;
            std::get<1>(transition_tuple) = production.getV()[0];
            std::get<2>(transition_tuple) = production.getU()[0];

            std::string restOfV = production.getV();
            restOfV.erase(restOfV.begin());
            transition_pair.first = initial_state;
            transition_pair.second = restOfV;

            transitions.emplace_back(std::make_pair(transition_tuple, transition_pair));
        }
    }
    return PushDownAutomaton{ states, alphabet, alphabetPDA, transitions, initial_state, initial_statePDA };
}

void ReadWord(std::string& word)
{
    std::cout << "Enter a word: \n";
    std::cin >> word;
}

int main()
{
    Grammar g;
    PushDownAutomaton a;
    g.ReadGrammar();
    std::cout << "Press 'a' to print the grammar." << std::endl;
    std::cout << "Press 'b' to simplify the grammar (2/3) and print it." << std::endl;
    std::cout << "Press 'c' to create a push-down automaton from a given context free grammar already in GNF." << std::endl;
    std::cout << "Press 'd' to check if the push-down automaton is deterministic." << std::endl;
    std::cout << "Press 'e' to exit." << std::endl;
    if (g.VerifyGrammar() == true && g.IsCFG() == true)
    {
        std::string option;
        bool menu = true;
        while (menu == true)
        {
            std::cin >> option;
            if (option.length() == 1)
                switch (option[0])
                {
                case 'a':
                {
                    g.PrintGrammar();
                    std::cout << std::endl;
                    break;
                }
                case 'b':
                {
                    g.SimplifyGrammar();
                    g.PrintGrammar();
                    std::cout << std::endl;
                    break;
                }
                case 'c':
                {
                    a = CFGtoPDA(g);
                    a.PrintAutomaton();
                    std::cout << std::endl;
                    break;
                }
                case 'd':
                {
                    if (a.IsDeterministic() == 1)
                        std::cout << "The push-down automaton is deterministic." << std::endl;
                    else
                        std::cout << "The push-down automaton is nondeterministic." << std::endl;
                    std::cout << std::endl;
                    break;
                }
                case 'e':
                {
                    menu = false;
                    break;
                }
                default:
                {
                    if (option[0] < 'a' || option[0] > 'g')
                    {
                        std::cout << "Not an option, try again:" << std::endl;
                        std::cout << std::endl;
                    }
                }
                }
            else
            {
                std::cout << "Not an option, try again:" << std::endl;
                std::cout << std::endl;
            }
        }
    }
    else
    {
        std::cout << std::endl;
        std::cout << "The grammar is wrong or not context free.";
    }
    return 0;
}


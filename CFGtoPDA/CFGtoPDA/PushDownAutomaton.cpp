#include "PushDownAutomaton.h"

void PushDownAutomaton::PrintAutomaton()
{
    std::cout << std::endl;

    std::cout << "states: ";
    for (auto state : states)
    {
        std::cout << state << " ";
    }
    std::cout << std::endl;

    std::cout << "alphabet: ";
    for (auto symbol : alphabet)
    {
        std::cout << symbol << " ";
    }
    std::cout << std::endl;

    std::cout << "alphabet PDA: ";
    for (auto symbol : alphabetPDA)
    {
        std::cout << symbol << " ";
    }
    std::cout << std::endl;

    std::cout << "transitions: ";

    std::unordered_set<int> jumpovers;

    for (int i = 0; i < transitions.size(); i++)
    {
        if (jumpovers.find(i) != jumpovers.end())
            continue;
        std::cout << "&(" << std::get<0>(transitions[i].first) << "," << std::get<1>(transitions[i].first) << "," << std::get<2>(transitions[i].first) << ") = " << "{(" << transitions[i].second.first << "," << transitions[i].second.second << "), ";
        for (int j = i + 1; j < transitions.size(); j++)
        {
            if (j == transitions.size())
                break;

            if (std::get<0>(transitions[j].first) == std::get<0>(transitions[i].first) && std::get<1>(transitions[j].first) == std::get<1>(transitions[i].first) && std::get<2>(transitions[j].first) == std::get<2>(transitions[i].first))
            {
                std::cout << "(" << transitions[j].second.first << "," << transitions[j].second.second << "), ";
                jumpovers.insert(j);
            }
        }
        if (i != transitions.size() - 1)
            std::cout << "\b\b}, ";
        else
            std::cout << "\b\b}";

    }

    std::cout << std::endl;

    std::cout << "initial state: ";
    std::cout << initial_state;
    std::cout << std::endl;

    std::cout << "initial state PDA: ";
    std::cout << initial_statePDA;
    std::cout << std::endl;
}

bool PushDownAutomaton::IsDeterministic()
{
    for (int i = 0; i < transitions.size() - 1; i++)
    {
        for (int j = i + 1; j < transitions.size(); j++)
        {
            if (std::get<0>(transitions[i].first) == std::get<0>(transitions[j].first))
                if (std::get<2>(transitions[i].first) == std::get<2>(transitions[j].first))
                    if (std::get<1>(transitions[i].first) == std::get<1>(transitions[j].first))
                        return false;

            if (std::get<0>(transitions[i].first) == std::get<0>(transitions[j].first))
                if (std::get<2>(transitions[i].first) == std::get<2>(transitions[j].first))
                    if ((std::get<1>(transitions[i].first) == '$' && std::get<1>(transitions[j].first) != '$') || (std::get<1>(transitions[i].first) != '$' && std::get<1>(transitions[j].first) == '$'))
                        return false;
        }
    }
    return true;
}
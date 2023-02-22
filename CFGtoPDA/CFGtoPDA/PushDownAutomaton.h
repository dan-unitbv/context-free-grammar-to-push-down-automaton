#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_set>
class PushDownAutomaton
{
private:
    std::unordered_set<char> states;
    std::unordered_set<char> alphabet;
    std::unordered_set<char> alphabetPDA;
    std::vector<std::pair<std::tuple<char, char, char>, std::pair<char, std::string>>> transitions;
    char initial_state;
    char initial_statePDA;
public:

    PushDownAutomaton() = default;

    ~PushDownAutomaton() = default;

    PushDownAutomaton(const std::vector<char>& states, const std::vector<char>& alphabet, const std::vector<char>& alphabetPDA, const  std::vector<std::pair<std::tuple<char, char, char>, std::pair<char, std::string>>>& transitions, char& initial_state, char& initial_statePDA) :
        states{ states.begin(), states.end() },
        alphabet{ alphabet.begin(), alphabet.end() },
        alphabetPDA{ alphabetPDA.begin(), alphabetPDA.end() },
        transitions{ transitions.begin(), transitions.end() },
        initial_state{ initial_state },
        initial_statePDA{ initial_statePDA } {
    }

    const std::unordered_set<char>& getStates() const
    {
        return states;
    }

    void setStates(const std::unordered_set<char>& states)
    {
        PushDownAutomaton::states = states;
    }

    const std::unordered_set<char>& getAlphabet() const
    {
        return alphabet;
    }

    void setAlphabet(const std::unordered_set<char>& alphabet)
    {
        PushDownAutomaton::alphabet = alphabet;
    }

    const std::unordered_set<char>& getAlphabetPDA() const
    {
        return alphabetPDA;
    }

    void setAlphabetPDA(const std::unordered_set<char>& alphabetPDA)
    {
        PushDownAutomaton::alphabetPDA = alphabetPDA;
    }

    const std::vector<std::pair<std::tuple<char, char, char>, std::pair<char, std::string>>>& getTransitions() const
    {
        return transitions;
    }

    void setTransitions(const  std::vector<std::pair<std::tuple<char, char, char>, std::pair<char, std::string>>>& transitions)
    {
        PushDownAutomaton::transitions = transitions;
    }

    char getInitialState() const
    {
        return initial_state;
    }

    void setInitialState(char initial_state)
    {
        PushDownAutomaton::initial_state = initial_state;
    }

    char getInitialStatePDA() const
    {
        return initial_state;
    }

    void setInitialStatePDA(char initial_statePDA)
    {
        PushDownAutomaton::initial_statePDA = initial_statePDA;
    }

    void PrintAutomaton();
    bool IsDeterministic();
};
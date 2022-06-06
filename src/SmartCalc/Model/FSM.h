#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "Tree.h"
#include "functionPtr.h"
namespace s21 {

using Action = std::function<void(void)>;

template <class S, class E>
struct transition {
    S _firstState;
    E _event;
    S _secondState;
    Action _action;
};

template <class S, class E>
class FSM {
    using TransitionTable = std::vector<transition<S, E>>;

 public:
    FSM(std::string alphabet, std::initializer_list<S> states, S start_state,
        std::initializer_list<S> finish_states, std::initializer_list<E> events)
        : _alphabet(alphabet), _states(states), _events(0), _finishStates(0), _startState() {
        if (std::find(_states.begin(), _states.end(), _startState) == _states.end())
            throw std::invalid_argument(
                "Invalid argument, start state does not belong to the set of states!");
        _startState = start_state;
        for (auto& i : finish_states) {
            if (std::find(_states.begin(), _states.end(), _startState) == _states.end())
                throw std::invalid_argument(
                    "Invalid argument, start state does not belong to the set of states!");
            _finishStates.push_back(i);
        }
        _events = events;
    }

    bool _checkSymbolInAlphabet(char i) {
        return std::find(_alphabet.begin(), _alphabet.end(), i) != _alphabet.end();
    }

    bool is_finish() {
        return (std::find(_finishStates.begin(), _finishStates.end(), _currentState) != _finishStates.end());
    }

    void addWay(S FState, E event, S SState, Action action) {
        _transitions.push_back({FState, event, SState, action});
    }

    void process(E event) {
        for (auto i = _transitions.begin(); i != _transitions.end(); i++) {
            if ((i->_firstState == _currentState) && (i->_event == event)) {
                try {
                    i->_action();
                    _currentState = i->_secondState;
                    return;
                } catch (const std::exception& e) {
                    throw;
                }
            }
        }
        throw std::invalid_argument("Event error!");
    }

    void resetCurrentState() { _currentState = _startState; }

    S getCurrentState() { return _currentState; }

 private:
    std::string _alphabet;
    std::vector<S> _states;
    std::vector<E> _events;
    std::vector<S> _finishStates;
    S _startState;
    S _currentState;
    TransitionTable _transitions;
};

}  // namespace s21

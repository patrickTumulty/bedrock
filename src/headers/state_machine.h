//
// Created by Patrick Tumulty on 2/26/23.
//

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <map>
#include <mutex>
#include <vector>
#include "bedrock.h"

BEDROCK_NAMESPACE_START

/**
 * Generic state machine
 *
 * @tparam T State transition event
 * @tparam V State type
 */
template<typename T, typename V>
class StateMachine
{
public:
    explicit StateMachine(V initialState) : currentState(initialState), listeners(std::vector<std::function<void(V, V)>*>()) { }

    /**
     * Handle state transition event
     *
     * @param event transition event
     * @return true if event was handled, else false
     */
    bool handle(T event)
    {
        std::scoped_lock lock { stateTransitionLock };

        if (stateTransitionsMap.find(currentState) != stateTransitionsMap.end() &&
            stateTransitionsMap[currentState].find(event) != stateTransitionsMap[currentState].end())
        {
            doStateTransition(stateTransitionsMap[currentState][event]);
            return true;
        }
        return false;
    }

    /**
     * Add state transition
     *
     * @param state state
     * @param transitions event to state transitions map for given state
     */
    void addStateTransition(V state, std::map<T, V> transitions)
    {
        stateTransitionsMap[state] = std::move(transitions);
    }

    /**
     * Get current state machine state
     *
     * @return current state
     */
    V getCurrentState()
    {
        return currentState;
    }

    /**
     * Add state machine listener
     *
     * @param listener listener
     */
    void addListener(std::function<void(V, V)> *listener)
    {
        listeners.push_back(listener);
    }

    /**
     * Remove state machine listener
     *
     * @param listener listener
     */
    void removeListener(std::function<void(V, V)> *listener)
    {
        if (listeners.empty())
            return;
        auto predicate = [listener](std::function<void(V, V)> *cb) { return cb == listener; };
        listeners.erase(std::remove_if(listeners.begin(),
                                       listeners.end(),
                                       predicate));
    }

private:
    /**
     * Do state transition
     *
     * @param newState new state
     */
    void doStateTransition(V newState)
    {
        auto prev = currentState;
        currentState = newState;

        notifyListeners(prev);
    }

    /**
     * Notify listeners of state change
     *
     * @param prev previous state
     */
    void notifyListeners(V prev)
    {
        for (std::function<void(V, V)> *listener : listeners)
        {
            if (listener != nullptr)
            {
                (*listener)(prev, currentState);
            }
        }
    }

    std::mutex stateTransitionLock;
    std::map<V, std::map<T, V>> stateTransitionsMap;
    std::vector<std::function<void(V, V)>*> listeners;
    V currentState;
};

BEDROCK_NAMESPACE_END

#endif

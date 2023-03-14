//
// Created by Patrick Tumulty on 2/26/23.
//

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <map>
#include <mutex>
#include <vector>

/**
 * Generic state machine
 *
 * @tparam V State type
 */
template<typename V>
class StateMachineListener
{
public:
    virtual void stateChanged(V previousState, V newState) = 0;
};

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
    explicit StateMachine(V initialState);

    bool handle(T event);
    void addStateTransition(V state, std::map<T, V> transitions);
    V getCurrentState();

    void addListener(StateMachineListener<V> *listener);
//    void removeListener(std::shared_ptr<StateMachineListener<V>> listener);

private:
    void doStateTransition(V newState);

    std::mutex stateTransitionLock;
    std::map<V, std::map<T, V>> stateTransitionsMap;
    std::vector<StateMachineListener<V> *> listeners;
    V currentState;
};


template<typename T, typename V>
StateMachine<T, V>::StateMachine(V initialState) : currentState(initialState), listeners(std::vector<StateMachineListener<V>*>())
{

}

/**
 * Add state machine listener
 *
 * @param listener listener
 */
template<typename T, typename V>
void StateMachine<T, V>::addListener(StateMachineListener<V> *listener)
{
    listeners.push_back(listener);
}

///**
// * Remove state machine listener
// *
// * @param listener listener
// */
//template<typename T, typename V>
//void StateMachine<T, V>::removeListener(std::shared_ptr<StateMachineListener<V>> listener)
//{
//    listeners.erase(std::remove_if(listeners.begin(), listeners.end(), [listener](std::shared_ptr<StateMachineListener<V>> l)
//    {
//        return listener.get() && l.get();
//    }), listeners.end());
//}

/**
 * Do state transition
 *
 * @param newState new state
 */
template<typename T, typename V>
void StateMachine<T, V>::doStateTransition(V newState)
{
//    std::scoped_lock lock { stateTransitionLock };

    auto prev = currentState;
    currentState = newState;

    for (StateMachineListener<V> *listener : listeners)
    {
        if (listener != nullptr)
        {
            listener->stateChanged(prev, currentState);
        }
    }
}

/**
 * Get current state
 *
 * @return current state
 */
template<typename T, typename V>
V StateMachine<T, V>::getCurrentState()
{
    return currentState;
}

/**
 * Add state transition
 *
 * @param state state
 * @param transitions transitions map
 */
template<typename T, typename V>
void StateMachine<T, V>::addStateTransition(V state, std::map<T, V> transitions)
{
    stateTransitionsMap[state] = std::move(transitions);
}

/**
 * Handle state change
 *
 * @param event state change event
 * @return true if the event was handled, else false
 */
template<typename T, typename V>
bool StateMachine<T, V>::handle(T event)
{
    if (stateTransitionsMap.find(currentState) != stateTransitionsMap.end() &&
        stateTransitionsMap[currentState].find(event) != stateTransitionsMap[currentState].end())
    {
        doStateTransition(stateTransitionsMap[currentState][event]);
        return true;
    }
    return false;
}

#endif

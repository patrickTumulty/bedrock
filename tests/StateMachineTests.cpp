//
// Created by Patrick Tumulty on 3/13/23.
//
#include <gtest/gtest.h>
#include "TestReadyStateMachine.h"

#include <thread>


TEST(StateMachineTests, StateTransitionTest)
{
    TestReadyStateMachine stateMachine(NOT_READY);

    ASSERT_EQ(stateMachine.getCurrentState(), NOT_READY);
    ASSERT_FALSE(stateMachine.handle(SUCCESS));
    ASSERT_EQ(stateMachine.getCurrentState(), NOT_READY);
    ASSERT_TRUE(stateMachine.handle(SEND_INIT));
    ASSERT_EQ(stateMachine.getCurrentState(), SENDING_INIT);
    ASSERT_TRUE(stateMachine.handle(SUCCESS));
    ASSERT_EQ(stateMachine.getCurrentState(), READY);
}

TEST(StateMachineTests, StateChangeListenerTest)
{
    TestReadyStateMachine stateMachine(NOT_READY);

    bool listenerCalled = false;
    std::function<void(TestState, TestState)> listenerCallback = [&listenerCalled](TestState prev, TestState current)
    {
        ASSERT_EQ(prev, NOT_READY);
        ASSERT_EQ(current, SENDING_RESET);
        listenerCalled = true;
    };
    stateMachine.addListener(&listenerCallback);

    ASSERT_TRUE(stateMachine.handle(SEND_RESET));

    ASSERT_TRUE(listenerCalled);

    listenerCalled = false;

    stateMachine.removeListener(&listenerCallback);

    ASSERT_TRUE(stateMachine.handle(FAILURE));

    ASSERT_FALSE(listenerCalled);
}

void transitionStates(TestReadyStateMachine *stateMachine, TestStateEvent event, TestState expectedState, TestState expectedTransitionState)
{
    for (int i = 0; i < 20; i++)
    {
        if (stateMachine->getCurrentState() == expectedState && stateMachine->handle(event))
        {
            ASSERT_EQ(stateMachine->getCurrentState(), expectedTransitionState);
        }
    }
}

void stateMachineThreadingTest()
{
    TestReadyStateMachine stateMachine(NOT_READY);

    std::thread t1(transitionStates, &stateMachine, SEND_INIT, NOT_READY, SENDING_INIT);
    std::thread t2(transitionStates, &stateMachine, SUCCESS, SENDING_INIT, READY);
    std::thread t3(transitionStates, &stateMachine, SEND_RESET, READY, SENDING_RESET);

    t1.join();
    t2.join();
    t3.join();
}

TEST(StateMachineTests, MultithreadStateChangeTest)
{
    for (int i = 0; i < 100; i++)
    {
        stateMachineThreadingTest();
    }
}
//
// Created by Patrick Tumulty on 3/13/23.
//
#include <gtest/gtest.h>
#include "CommonPPAPI.h"
#include "TestReadyStateMachine.h"

#include <iostream>




// Demonstrate some basic assertions.
TEST(StateMachineTests, StateTransitions)
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

TEST(StateMachineTests, StateChangeListener)
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
//
// Created by Patrick Tumulty on 3/13/23.
//

#ifndef SLACK_JAW_TESTREADYSTATEMACHINE_H
#define SLACK_JAW_TESTREADYSTATEMACHINE_H

#include "StateMachine.h"

enum TestState
{
    READY,
    SENDING_INIT,
    SENDING_RESET,
    NOT_READY,
    FATAL
};

enum TestStateEvent
{
    SEND_RESET,
    SEND_INIT,
    SUCCESS,
    FAILURE
};

class TestReadyStateMachine : public commonpp::StateMachine<TestStateEvent, TestState>
{
public:
    explicit TestReadyStateMachine(TestState initialState);

};

#endif //SLACK_JAW_TESTREADYSTATEMACHINE_H

//
// Created by Patrick Tumulty on 3/13/23.
//

#include "TestReadyStateMachine.h"

TestReadyStateMachine::TestReadyStateMachine(TestState initialState) : StateMachine(initialState)
{
    addStateTransition(NOT_READY, {
        { SEND_INIT, SENDING_INIT },
        { SEND_RESET, SENDING_RESET }
    });

    addStateTransition(SENDING_INIT, {
        { SUCCESS, READY },
        { FAILURE, NOT_READY }
    });

    addStateTransition(SENDING_RESET, {
        { SUCCESS, NOT_READY },
        { FAILURE, FATAL }
    });

    addStateTransition(READY, {
        { SEND_RESET, SENDING_RESET },
    });

    addStateTransition(FATAL, {
        { SEND_RESET, SENDING_RESET }
    });
}

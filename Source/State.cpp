//
// Created by harshdeep on 21/10/19.
//

#include <State.hpp>


//State
State::State(StateStack& stateStack, Context context) : mStack(&stateStack) , mContext(context)
{
}

State::Context State::getContext() const
{
    return mContext;
}

void State::requestStackPush(States stateID)
{
    mStack->pushState(stateID);
}

void State::requestStackPop()
{
    mStack->popState();
}

void State::requestStackClear()
{
    mStack->clearStates();
}
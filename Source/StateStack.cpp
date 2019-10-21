//
// Created by harshdeep on 21/10/19.
//
#include <StateStack.hpp>

StateStack::StateStack(State::Context context) : mContext(context)
{
}


void StateStack::handleEvent(const sf::Event& event)
{
    for(auto itr = mStack.rbegin() ; itr != mStack.rend() ; ++itr) //delivery order is stack
    {
        if(!(*itr)->handleEvent(event))
        {
            break; //so the state can decide if it wants input to be passed to the other states or not
        }
    }
    applyPendingChanges();
}

void StateStack::update(sf::Time dt)
{
    for(auto itr = mStack.rbegin() ; itr != mStack.rend() ; itr++) //delivery order is stack
    {
        if(!(*itr)->update(dt))
        {
            return; //so the state can decide if it wants other states to be updated or not
        }
    }
    applyPendingChanges();
}

void StateStack::draw()
{
    std::for_each(mStack.begin(), mStack.end(), [](auto iter){
        (*iter)->draw();
    });
    applyPendingChanges();
}

State::Ptr StateStack::createState(States stateID)
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());

    return found->second();
}

void StateStack::applyPendingChanges()
{
    for(auto& change : mPendingList)
    {
        switch(change.action)
        {
            case Action::Pop:
                mStack.pop_back();
                break;
            case Action::Push:
                mStack.push_back(createState(change.stateID));
                break;
            case Action::Clear:
                mStack.clear();
                break;
        }
    }
    mPendingList.clear();
}

void StateStack::pushState(States stateID)
{
    auto change = PendingChange();
    change.action = Action::Push;
    change.stateID = stateID;
    mPendingList.push_back( change );
}

void StateStack::popState()
{
    auto change = PendingChange();
    change.action = Action::Pop;
    mPendingList.push_back( change );
}

void StateStack::clearStates()
{
    PendingChange change;
    change.action = Action::Clear;
    mPendingList.push_back( change );
}

bool StateStack::isEmpty() const
{
    return mStack.empty();
}
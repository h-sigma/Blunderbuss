//
// Created by harshdeep on 21/10/19.
//

#ifndef BLUNDERBUSS_STATESTACK_HPP
#define BLUNDERBUSS_STATESTACK_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include <map>
#include "StateIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include "State.hpp"

class StateStack{
public:
    enum class Action{
        Pop, Push, Clear, NoOp
    };
public:
    explicit StateStack(State::Context context);
    template<typename T> void registerState(States stateID);

    void draw();
    void update(sf::Time dt);
    void handleEvent(const sf::Event& event);

    void pushState(States stateID);
    void popState();
    void clearStates();

    [[nodiscard]] bool isEmpty() const;
private:
    State::Ptr createState(States stateID);
    void applyPendingChanges();
private:
    struct PendingChange{
        PendingChange() = default;
        StateStack::Action action = Action::NoOp;
        States stateID = States::Null;
    };
private:
    State::Context mContext;
    std::vector<State::Ptr> mStack;
    std::vector<PendingChange> mPendingList;
    std::map<States, std::function<State::Ptr()> > mFactories;
};

template<typename T> void StateStack::registerState(States stateID)
{
    mFactories[stateID] = [this](){
        return std::make_unique<T>(*this, mContext);
    };
}

#endif //BLUNDERBUSS_STATESTACK_HPP

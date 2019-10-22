//
// Created by harshdeep on 21/10/19.
//

#ifndef BLUNDERBUSS_GAMESTATE_HPP
#define BLUNDERBUSS_GAMESTATE_HPP

#include <State.hpp>
#include "World.hpp"

class GameState : public State
{
public:
    typedef std::unique_ptr<State> Ptr;
public:
    GameState(StateStack& stateStack, Context context);
    bool handleEvent(const sf::Event& event) final;
    bool update(sf::Time dt) final;
    void draw() final;
private:
    World mWorld;
};

#endif //BLUNDERBUSS_GAMESTATE_HPP

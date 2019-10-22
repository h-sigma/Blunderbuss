//
// Created by harshdeep on 21/10/19.
//

#include <GameState.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

GameState::GameState(StateStack &stateStack, Context context)
: State(stateStack, context)
, mWorld(context)
{

}

bool GameState::handleEvent(const sf::Event &event) {
    mWorld.pushEventToQueue(event);
    return false;
}

bool GameState::update(sf::Time dt) {
    mWorld.update(dt);
    return true;
}

void GameState::draw() {
    mContext.mRenderWindow->draw(mWorld);
}


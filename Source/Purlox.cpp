//
// Created by harshdeep on 19/10/19.
//

#include <SFML/System.hpp>
#include <Purlox.hpp>
#include <GameObject.hpp>
#include <World.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>


void PurloxInput::setup() {

}

void PurloxInput::update(class GameObject & gameObject, sf::Time, class World & world) {
    handleMovement(gameObject, world);
    auto queue = world.readQueue();
    for(auto& item : queue)
    {
        if(item == World::Event::Print)
        {
            auto pos = gameObject.getPosition();
            std::cout << pos.x << "," << pos.y << std::endl;
        }
    }
}

void PurloxInput::handleMovement(class GameObject & , class World &)  {

}

/*
 *  GRAPHICS COMPONENT CODE
 */

void PurloxGraphics::setup() {
    mTexture.loadFromFile("Media/Character/Purlox.png");
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(mRects[mCurrentRect]);
}

void PurloxGraphics::update(class SceneObject &, sf::Time, class World &) {
    static int frameCount = 0;
    frameCount++;
    if(frameCount == 10)
    {
        frameCount = 0;
        mCurrentRect++;
    }
    if(mCurrentRect >= mTotalRects)
        mCurrentRect = 0;
    mSprite.setTextureRect(mRects[mCurrentRect]);
}

sf::FloatRect PurloxGraphics::getBoundingRect() const {
    return sf::FloatRect();
}

void PurloxGraphics::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

/*
 *  PHYSICS CODE
 */

void PurloxPhysics::setup() {

}

void PurloxPhysics::update(class GameObject &, sf::Time, class World &) {

}

//
// Created by admin on 10/15/2019.
//

#include <GameObject.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

GameObject::GameObject(Category category, InputComponent * input, PhysicsComponent * physics, GraphicsComponent * graphics)
: SceneObject(category)
, mInput(input)
, mPhysics(physics)
, mGraphics(graphics)
{
}

sf::FloatRect GameObject::getBoundingRect() const {
    return mGraphics->getBoundingRect();
}

void GameObject::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(*mGraphics, states);
}

void GameObject::updateCurrent(sf::Time) {
    //mInput->update(*this, dt);
    //mPhysics->update(*this, dt);
    //mGraphics->update(*this, dt);
}


//
// Created by admin on 10/15/2019.
//

#include <GameObject.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

GameObject::GameObject(InputComponent * input, PhysicsComponent * physics, GraphicsComponent * graphics, Category::ID category = Category::GameObject)
: SceneObject(category)
, mInput(input)
, mPhysics(physics)
, mGraphics(graphics)
{
    mInput->setup();
    mPhysics->setup();
    mGraphics->setup();
}

void GameObject::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(*mGraphics, states);
}

void GameObject::updateCurrent(sf::Time dt, class World& world) {
    mInput->update(*this, dt, world);
    mPhysics->update(*this, dt, world);
    mGraphics->update(*this, dt, world);
}

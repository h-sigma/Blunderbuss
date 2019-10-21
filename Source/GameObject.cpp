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
}

void GameObject::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(*mGraphics, states);
}

void GameObject::updateCurrent(sf::Time dt, SceneObject* World) {
    mInput->update(*this, dt, World);
    mPhysics->update(*this, dt, World);
    mGraphics->update(*this, dt, World);
}

GameObject::~GameObject() {
    delete mInput;
    delete mPhysics;
    delete mGraphics;
}

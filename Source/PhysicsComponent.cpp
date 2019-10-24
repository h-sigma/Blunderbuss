//
// Created by harshdeep on 24/10/19.
//

#include <PhysicsComponent.hpp>

void PhysicsComponent::addForce(float magnitude, sf::Vector2f direction, PhysicsComponent::Forces force, sf::Time duration) {
    mForces.emplace_back(force, magnitude, direction, duration);
}


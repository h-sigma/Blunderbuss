//
// Created by harshdeep on 18/10/19.
//

#ifndef BLUNDERBUSS_PHYSICSCOMPONENT_HPP
#define BLUNDERBUSS_PHYSICSCOMPONENT_HPP

#include <imconfig.h>
#include <vector>
#include <SFML/System/Time.hpp>
#include <cstdint>

class PhysicsComponent
{
public:
    enum Forces{
        Impulse, Continuous, Timed
    };
public:
    virtual ~PhysicsComponent() = default;
    virtual void setup() = 0;
    virtual void update(class GameObject&, class sf::Time, class World&) = 0;
    void addForce(float magnitude, sf::Vector2f direction, Forces force, sf::Time duration = sf::Time::Zero);
protected:
    struct Force{
        Forces force = Impulse;
        float magnitude = 0.0f;
        sf::Vector2f direction;
        sf::Time duration;
        Force(Forces f, float m, sf::Vector2f di, sf::Time du = sf::Time::Zero) : force(f), magnitude(m), direction(di), duration(du) {}
    };
protected:
    std::vector<Force> mForces;
};


#endif //BLUNDERBUSS_PHYSICSCOMPONENT_HPP

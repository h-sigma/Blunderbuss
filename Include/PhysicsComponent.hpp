//
// Created by harshdeep on 18/10/19.
//

#ifndef BLUNDERBUSS_PHYSICSCOMPONENT_HPP
#define BLUNDERBUSS_PHYSICSCOMPONENT_HPP

class GameObject;
class SceneObject;

namespace sf{
    class Time;
}

class PhysicsComponent
{
public:
    virtual ~PhysicsComponent() = default;
    virtual void setup() = 0;
    virtual void update(class GameObject&, sf::Time, class World&) = 0;
};


#endif //BLUNDERBUSS_PHYSICSCOMPONENT_HPP

//
// Created by harshdeep on 18/10/19.
//

#ifndef BLUNDERBUSS_PHYSICSCOMPONENT_HPP
#define BLUNDERBUSS_PHYSICSCOMPONENT_HPP

class GameObject;

class PhysicsComponent
{
public:
    virtual ~PhysicsComponent() = default;
    virtual void update(class GameObject&, sf::Time) = 0;
};


#endif //BLUNDERBUSS_PHYSICSCOMPONENT_HPP

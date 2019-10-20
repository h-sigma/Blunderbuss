//
// Created by harshdeep on 18/10/19.
//

#ifndef BLUNDERBUSS_INPUTCOMPONENT_HPP
#define BLUNDERBUSS_INPUTCOMPONENT_HPP

class SceneObject;
class GameObject;

namespace sf{
    class Time;
}

class InputComponent
{
public:
    virtual ~InputComponent() = default;
    virtual void update(class GameObject&, sf::Time, class SceneObject*) = 0;
};

#endif //BLUNDERBUSS_INPUTCOMPONENT_HPP

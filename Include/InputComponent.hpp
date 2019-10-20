//
// Created by harshdeep on 18/10/19.
//

#ifndef BLUNDERBUSS_INPUTCOMPONENT_HPP
#define BLUNDERBUSS_INPUTCOMPONENT_HPP

class GameObject;
class World;

class InputComponent
{
public:
    virtual ~InputComponent() = default;
    virtual void update(class GameObject&, World&) = 0;
};

#endif //BLUNDERBUSS_INPUTCOMPONENT_HPP

//
// Created by harshdeep on 18/10/19.
//

#ifndef BLUNDERBUSS_INPUTCOMPONENT_HPP
#define BLUNDERBUSS_INPUTCOMPONENT_HPP

#include <PatternMatch.hpp>
#include <World.hpp>

namespace sf{
    class Time;
}

class InputComponent
{
public:
    virtual ~InputComponent() = default;
    virtual void setup(class GameObject*) = 0;
    virtual void update(sf::Time, class World&);
protected:
    PatternMatch<World::Event> mPM;
};

#endif //BLUNDERBUSS_INPUTCOMPONENT_HPP

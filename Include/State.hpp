//
// Created by harshdeep on 21/10/19.
//

#ifndef BLUNDERBUSS_STATE_HPP
#define BLUNDERBUSS_STATE_HPP

#include "ResourceHolder.hpp"
#include "ResourceIdentifier.hpp"
#include "StateIdentifiers.hpp"

class Player;
class StateStack;

namespace sf{
    class RenderWindow;
    class Event;
    class Time;
}

class State{
public:
    typedef std::unique_ptr<State> Ptr;
    struct Context{
        Context(const Context&) = default;
        sf::RenderWindow* mRenderWindow;
        TextureHolder* mTextureHolder;
        FontHolder* mFontHolder;
    };
public:
    State(StateStack& stateStack, Context context);
    virtual ~State() = default;

    virtual bool handleEvent(const sf::Event& event) = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual void draw() = 0;
protected:
    [[nodiscard]] Context getContext() const;

    void requestStackPush(States stateID);
    void requestStackPop();
    void requestStackClear();

    Context mContext;
private:
    StateStack* mStack;
};

#endif //BLUNDERBUSS_STATE_HPP

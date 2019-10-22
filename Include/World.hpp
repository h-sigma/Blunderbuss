//
// Created by harshdeep on 22/10/19.
//

#ifndef BLUNDERBUSS_WORLD_HPP
#define BLUNDERBUSS_WORLD_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <queue>
#include <State.hpp>
#include <SceneLoader.hpp>

namespace sf{
    class Event;
    class RenderStates;
    class RenderTarget;
}

class World : public sf::Drawable {
public:
    enum class Event{
        moveUp, moveLeft, moveDown, moveRight, Jump,
    };
    using EventQueue = std::vector<World::Event>;
public:
    explicit World(State::Context);

    void update(sf::Time);

    [[nodiscard]] const EventQueue& readQueue() const { return mQueue; }
    void pushEventToQueue(const sf::Event& event);
protected:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
    EventQueue mQueue;
    State::Context mContext;
    SceneLoader mLoader;
};


#endif //BLUNDERBUSS_WORLD_HPP

//
// Created by harshdeep on 22/10/19.
//

#ifndef BLUNDERBUSS_WORLD_HPP
#define BLUNDERBUSS_WORLD_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <queue>
#include <State.hpp>
#include <SceneLoader.hpp>
#include <PrefabDispenser.hpp>

namespace sf{
    class Event;
    class RenderStates;
    class RenderTarget;
}

class World : public sf::Drawable {
public:
    enum class Event : uint{
        Nil, Up, Left, Down, Right, Jump, Print, Press, Drag, Release
    };
//    static uint operatoruint(Event event){
//        return static_cast<uint>(event);
//    }
    using EventQueue = std::vector<World::Event>;
public:
    explicit World(State::Context);
    ~World() override = default;

    void update(sf::Time);

    [[nodiscard]] const EventQueue& readQueue() const { return mQueue; }
    void pushEventToQueue(const sf::Event& event);
    void pushEventToQueue(World::Event);
    void queueLoadScene(std::string);
protected:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
    void loadScene();
    std::string mNextSceneToLoad = "";
    void clearQueue();
private:
    EventQueue mQueue;
    State::Context mContext;
    PrefabDispenser mDispenser;
    SceneLoader mLoader;
    SceneObject::Ptr mGameScene;
};


#endif //BLUNDERBUSS_WORLD_HPP

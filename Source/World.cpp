//
// Created by harshdeep on 22/10/19.
//

#include <World.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/Event.hpp>
#include <TestScene.hpp>

void World::pushEventToQueue(const sf::Event &event) {
    //Modify this to have a "key mapper" later
    switch(event.type)
    {
        case sf::Event::Closed:
            break;
        case sf::Event::Resized:
            break;
        case sf::Event::LostFocus:
            break;
        case sf::Event::GainedFocus:
            break;
        case sf::Event::TextEntered:
            break;
        case sf::Event::MouseWheelMoved:
            break;
        case sf::Event::MouseWheelScrolled:
            break;
        case sf::Event::MouseButtonPressed:
            break;
        case sf::Event::MouseButtonReleased:
            break;
        case sf::Event::MouseMoved:
            break;
        case sf::Event::MouseEntered:
            break;
        case sf::Event::MouseLeft:
            break;
        case sf::Event::JoystickButtonPressed:
            break;
        case sf::Event::JoystickButtonReleased:
            break;
        case sf::Event::JoystickMoved:
            break;
        case sf::Event::JoystickConnected:
            break;
        case sf::Event::JoystickDisconnected:
            break;
        case sf::Event::TouchBegan:
            break;
        case sf::Event::TouchMoved:
            break;
        case sf::Event::TouchEnded:
            break;
        case sf::Event::SensorChanged:
            break;
        case sf::Event::Count:
            break;
        case sf::Event::KeyReleased:
            break;
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
                case sf::Keyboard::Up:
                    mQueue.push_back(Event::Up);
                    break;
                case sf::Keyboard::Down:
                    mQueue.push_back(Event::Down);
                    break;
                case sf::Keyboard::Left:
                    mQueue.push_back(Event::Left);
                    break;
                case sf::Keyboard::Right:
                    mQueue.push_back(Event::Right);
                    break;
                case sf::Keyboard::Z:
                    mQueue.push_back(Event::Jump);
                    break;
                case sf::Keyboard::P:
                    mQueue.push_back(Event::Print);
                    break;
                default:
                    break;
            }
            break;

    }
}

World::World(State::Context context) : mContext(context), mLoader(mDispenser), mGameScene(nullptr){
    mLoader.registerScene<TestScene>("TestScene");
    queueLoadScene("TestScene");
}

void World::update(sf::Time dt) {
    loadScene();

    if(mGameScene)
        mGameScene->update(dt, *this);
    mQueue.clear();
}

void World::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    if(mGameScene)
        target.draw(*mGameScene, states);
}

void World::queueLoadScene(std::string sceneName) {
    mNextSceneToLoad = std::move(sceneName);
}

void World::loadScene() {
    if(!mNextSceneToLoad.empty())
        mGameScene = mLoader.loadScene(mNextSceneToLoad);
    mNextSceneToLoad.clear();
}

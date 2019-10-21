//
// Created by harshdeep on 20/10/19.
//

#ifndef BLUNDERBUSS_APPLICATION_HPP
#define BLUNDERBUSS_APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifier.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include "StateStack.hpp"

namespace sf{
    class Time;
}

class Application
{
public:
    explicit Application();
    void run();
private:
    void processInput();
    void update(sf::Time dt);
    void render();
private:
    sf::RenderWindow mWindow;
    TextureHolder mTextureHolder;
    FontHolder mFontHolder;
    StateStack mStack;
    //MusicPlayer, SoundPlayer => Some other day!
    //StateStack and StateContext => Soon, amigos!
    const sf::Time timePerFrame;
};

#endif //BLUNDERBUSS_APPLICATION_HPP

//
// Created by harshdeep on 20/10/19.
//

#include <SFML/Window/Event.hpp>
#include <GameState.hpp>
#include "Application.hpp"

Application::Application()
        : mWindow(sf::VideoMode(1280,800), "Blunderbuss", sf::Style::Default)
        , mStack(State::Context{&mWindow, &mTextureHolder, &mFontHolder})
        , timePerFrame(sf::seconds(1.f/60.f))
{
    mStack.registerState<GameState>(States::Game);
    mStack.pushState(States::Game);
}


void Application::run() {
    auto clock = sf::Clock();
    auto dt = sf::Time::Zero;
    while(mWindow.isOpen())
    {
        processInput();
        dt += clock.restart();
        while(dt >= timePerFrame)
        {
            dt -= timePerFrame;

            if(mStack.isEmpty())
                mWindow.close();

            update(timePerFrame);
        }
        render();
    }
}

void Application::processInput() {
    auto event = sf::Event();
    while(mWindow.pollEvent(event))
    {
        //call handleEvent on states
        if(event.type == sf::Event::Closed)
            mStack.clearStates();
        mStack.handleEvent(event);
    }
}

void Application::update(sf::Time dt) {
    mStack.update(dt);
}

void Application::render() {
    //call render on stack
    mStack.draw();
}

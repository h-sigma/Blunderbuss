//
// Created by harshdeep on 19/10/19.
//

#include <SFML/System.hpp>
#include <Purlox.hpp>
#include <GameObject.hpp>
#include <Utility.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>


void PurloxInput::setup(class GameObject* gameObject) {
    using namespace std::placeholders;
    using Event = World::Event;

    auto printBind = std::bind(&PurloxInput::print, gameObject);
    mPM.bindFunc<decltype(printBind), Event::Print, Event::Print>(printBind);

    auto flickBeginBind = std::bind(&PurloxInput::flickBegin, this, gameObject);
    mPM.bindFunc<decltype(flickBeginBind), Event::Press>(flickBeginBind);

    auto flickActionBind = std::bind(&PurloxInput::flickAction, this, gameObject);
    mPM.bindFunc<decltype(flickActionBind), Event::Press, Event::Drag, Event::Release>(flickActionBind);
}

void PurloxInput::print(GameObject* gameObject) {
    if(gameObject == nullptr)
        return;
    auto pos = gameObject->getPosition();
    auto PC = dynamic_cast<PurloxPhysics*>(gameObject->getPhysicsComponent());
    auto vel = sf::Vector2f();
    if(PC)
        vel = PC->mVelocity;
    std::printf("Pos:[%.2f,%.2f] Vel:[%2.f,%2.f]\n", pos.x, pos.y, vel.x, vel.y );
    std::cout << std::flush;
}

void PurloxInput::flickBegin(GameObject *) {
    mPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
    flickClock.restart();
}

void PurloxInput::flickAction(GameObject * gameObject) {
    float flickMinimumDistance = 5.f;
    auto dist = static_cast<sf::Vector2f>(sf::Mouse::getPosition()) - mPos;
    if(magnitude(dist) < flickMinimumDistance)
        return;
    static auto flickClock = sf::Clock();
    static auto timeBetweenFlicks = sf::Time::Zero;
    const sf::Time mFlickInterval = sf::seconds(0.5);
    timeBetweenFlicks += flickClock.restart();
    if(timeBetweenFlicks < mFlickInterval)
        return;
    if(flickClock.restart() > sf::seconds(1.5f))
        return;
    timeBetweenFlicks = sf::Time::Zero;
    gameObject->getPhysicsComponent()->addForce(200.f, dist, PhysicsComponent::Forces::Impulse);
}

/*
 *  GRAPHICS COMPONENT CODE
 */

void PurloxGraphics::setup() {
    mTexture.loadFromFile("Media/Character/Purlox.png");
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(mRects[mCurrentRect]);
}

void PurloxGraphics::update(class SceneObject &, sf::Time, class World &) {
    static int frameCount = 0;
    frameCount++;
    if(frameCount == 10)
    {
        frameCount = 0;
        mCurrentRect++;
    }
    if(mCurrentRect >= mTotalRects)
        mCurrentRect = 0;
    mSprite.setTextureRect(mRects[mCurrentRect]);
}

sf::FloatRect PurloxGraphics::getBoundingRect() const {
    return sf::FloatRect(mRects[mCurrentRect]);
}

void PurloxGraphics::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

/*
 *  PHYSICS CODE
 */

void PurloxPhysics::setup() {

}

void PurloxPhysics::update(class GameObject & gameObject, sf::Time dt, class World &) {
    auto dragForce = [&gameObject, this]() -> PhysicsComponent::Force {
        //drag R = ½ρCAv2
        auto vel = magnitude(mVelocity);
        auto C = float{1.5f};
        auto A = float{2 * 0.64f * 0.64f * 3.14f};
        auto rho = 1; //water
        auto dragMag = 0.5 * rho * A * C * vel;
        auto direction = -(mVelocity / vel);
        return PhysicsComponent::Force(Forces::Impulse, dragMag, direction);
    };
    if(mVelocity != sf::Vector2f{0.f, 0.f})
        mForces.push_back(dragForce());
    resolveForces(gameObject, dt);
    gameObject.move(mVelocity * dt.asSeconds());
}

void PurloxPhysics::resolveForces(class GameObject & gameObject, sf::Time dt) {
    for(auto& force : mForces)
    {
        auto acceleration = force.direction * force.magnitude / mMass;
        auto velocity = acceleration * dt.asSeconds();
        mVelocity += velocity;
        force.duration -= dt;
    }
    mForces.erase(std::remove_if(mForces.begin(),mForces.end(),[](PhysicsComponent::Force& force)->bool{
        return (force.force == PhysicsComponent::Impulse) || ((force.duration <= sf::Time::Zero) && (force.force != PhysicsComponent::Continuous));
    }), mForces.end());
}

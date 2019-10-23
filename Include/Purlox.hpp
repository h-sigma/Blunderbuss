//
// Created by harshdeep on 19/10/19.
//

#ifndef BLUNDERBUSS_PURLOX_HPP
#define BLUNDERBUSS_PURLOX_HPP

#include <InputComponent.hpp>
#include <GraphicsComponent.hpp>
#include <PhysicsComponent.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class PurloxInput : public InputComponent
{
public:
    ~PurloxInput() final = default;
    void setup() final;
    void update(class GameObject&, sf::Time, class World&) override;
private:
    void handleMovement(class GameObject&, class World &) ;
private:
    //state variables
};

class PurloxGraphics : public GraphicsComponent
{
public:
    PurloxGraphics() = default;
    ~PurloxGraphics() final = default;
    void setup() final;
    void update(class SceneObject&, sf::Time, class World&) final;
    [[nodiscard]] sf::FloatRect getBoundingRect() const final;
protected:
    void draw(sf::RenderTarget&, sf::RenderStates) const final;
private:
    sf::Texture mTexture;
    sf::Sprite mSprite;
    const sf::IntRect mRects[8] = {
            {128*0, 0, 128, 128},
            {128*1, 0, 128, 128},
            {128*2, 0, 128, 128},
            {128*3, 0, 128, 128},
            {128*4, 0, 128, 128},
            {128*5, 0, 128, 128},
            {128*6, 0, 128, 128},
            {128*7, 0, 128, 128}
    };
    const int mTotalRects = 8;
    int mCurrentRect = 0;
};


class PurloxPhysics : public PhysicsComponent

{
public:
    ~PurloxPhysics() final = default;
    void setup() final;
    void update(class GameObject&, sf::Time, class World&) final;
};

#endif //BLUNDERBUSS_PURLOX_HPP

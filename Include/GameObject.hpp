//
// Created by harshdeep on 17/10/19.
//

#ifndef BLUNDERBUSS_GAMEOBJECT_HPP
#define BLUNDERBUSS_GAMEOBJECT_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SceneObject.hpp>
#include <InputComponent.hpp>
#include <PhysicsComponent.hpp>
#include <GraphicsComponent.hpp>
#include <ComponentQueue.hpp>

class GameObject : public SceneObject
{
public:
    explicit GameObject(Category, InputComponent*, PhysicsComponent*, GraphicsComponent*);
    sf::FloatRect getBoundingRect() const override;
    void drawCurrent(sf::RenderTarget&, sf::RenderStates) const override;
    void updateCurrent(sf::Time dt) override;
protected:

private:
    InputComponent* mInput;
    PhysicsComponent* mPhysics;
    GraphicsComponent* mGraphics;
};

#endif //BLUNDERBUSS_GAMEOBJECT_HPP

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
    explicit GameObject(InputComponent*, PhysicsComponent*, GraphicsComponent*, Category::ID);
    ~GameObject() override = default;
    void drawCurrent    (sf::RenderTarget&, sf::RenderStates) const override;
    void updateCurrent  (sf::Time dt,       class World&    )       override;
    InputComponent*     getInputComponent()     const { return mInput.get()   ; }
    PhysicsComponent*   getPhysicsComponent()   const { return mPhysics.get() ; }
    GraphicsComponent*  getGraphicsComponent()  const { return mGraphics.get(); }
protected:
private:
    std::unique_ptr<InputComponent>     mInput;
    std::unique_ptr<PhysicsComponent>   mPhysics;
    std::unique_ptr<GraphicsComponent>  mGraphics;
};

#endif //BLUNDERBUSS_GAMEOBJECT_HPP

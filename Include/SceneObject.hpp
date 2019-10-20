//
// Created by harshdeep on 18/10/19.
//

#ifndef BLUNDERBUSS_SCENEOBJECT_HPP
#define BLUNDERBUSS_SCENEOBJECT_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>
#include <vector>
#include <SFML/System/Time.hpp>
#include <Category.hpp>

/*
 * A SceneObject has a position in space (a 3x3 Matrix Transform for position, rotation, scale), can be
 */

class SceneObject : public sf::Transformable, public sf::NonCopyable
{
public:
    using Ptr = std::unique_ptr<SceneObject>;
    using Pair = std::pair<SceneObject*, SceneObject*>;
public:
    explicit SceneObject(Category::ID category = Category::SceneObject);
    ~SceneObject() override = default;

    void update(sf::Time, SceneObject* World);   //time, world

    void attachChild(Ptr child);
    Ptr detachChild(const SceneObject& node);

    sf::Transform getWorldTransform() const;
    sf::Vector2f getWorldPosition() const;
    virtual sf::FloatRect getBoundingRect() const { return sf::FloatRect{}; }

    [[nodiscard]] Category::ID getCategory() const noexcept { return mCategory; }
protected:
    void draw(sf::RenderTarget&, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;
    virtual void updateCurrent(sf::Time dt, SceneObject*);
    void updateChildren(sf::Time dt, SceneObject* World);
protected:
    Category::ID mCategory;
private:
    std::vector<Ptr> mChildren;
    SceneObject* mParent;
};

#endif //BLUNDERBUSS_SCENEOBJECT_HPP

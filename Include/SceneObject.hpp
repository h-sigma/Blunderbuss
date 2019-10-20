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
    explicit SceneObject(Category category = Category::SceneObject);

    void update(sf::Time);

    void attachChild(Ptr child);
    Ptr detachChild(const SceneObject& node);

    sf::Transform getWorldTransform() const;
    sf::Vector2f getWorldPosition() const;
    virtual sf::FloatRect getBoundingRect() const { return sf::FloatRect{}; }

    [[nodiscard]] Category getCategory() const noexcept { return mCategory; }
protected:
    void draw(sf::RenderTarget&, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;
    virtual void updateCurrent(sf::Time dt);
    void updateChildren(sf::Time dt);
protected:
    Category mCategory;
private:
    std::vector<Ptr> mChildren;
    SceneObject* mParent;
};

#endif //BLUNDERBUSS_SCENEOBJECT_HPP

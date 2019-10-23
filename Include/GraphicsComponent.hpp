//
// Created by harshdeep on 18/10/19.
//

#ifndef BLUNDERBUSS_GRAPHICSCOMPONENT_HPP
#define BLUNDERBUSS_GRAPHICSCOMPONENT_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>

class SceneObject;

namespace sf{
    class RenderTarget;
    class RenderStates;
    class Time;
}

class GraphicsComponent : public sf::Drawable
{
public:
    ~GraphicsComponent() override = default;
    virtual void update(class SceneObject&, sf::Time, class World&) = 0;
    [[nodiscard]] virtual sf::FloatRect getBoundingRect() const = 0;
protected:
    void draw(sf::RenderTarget&, sf::RenderStates) const override = 0;
};


#endif //BLUNDERBUSS_GRAPHICSCOMPONENT_HPP

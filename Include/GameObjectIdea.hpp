//
// Created by harshdeep on 20/10/19.
//

#ifndef BLUNDERBUSS_GAMEOBJECTIDEA_HPP
#define BLUNDERBUSS_GAMEOBJECTIDEA_HPP

#include "SceneObject.hpp"

template<typename... Args>
class GameObjectIdea : public SceneObject
{
public:
    explicit GameObjectIdea(Category category, Args&&... args);
    template<typename T> T getComponent();
private:
    std::tuple<Args...> mComponents;
};

template<typename... Args>
GameObjectIdea<Args...>::GameObjectIdea(Category category, Args &&... args)
:   SceneObject(category)
,   mComponents(std::forward(args)...)
{
}

template<typename... Args>
template<typename T>
T GameObjectIdea<Args...>::getComponent() {
    return std::get<T>(mComponents);
}


#endif //BLUNDERBUSS_GAMEOBJECTIDEA_HPP

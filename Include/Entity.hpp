//
// Created by harshdeep on 24/10/19.
//

#ifndef BLUNDERBUSS_ENTITY_HPP
#define BLUNDERBUSS_ENTITY_HPP

#include <vector>

class Component
{};

class Entity
{
public:
    explicit Entity() = default;
    template <typename T> T* getComponent();
private:
    std::vector<Component*> mComponents;
};

template<typename T>
T *Entity::getComponent() {
    for(auto& component : mComponents)
    {
        if(dynamic_cast<T*>(component))
            return component;
    }
    return nullptr;
}

#endif //BLUNDERBUSS_ENTITY_HPP

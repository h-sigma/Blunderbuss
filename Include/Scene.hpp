//
// Created by harshdeep on 22/10/19.
//

#ifndef BLUNDERBUSS_SCENE_HPP
#define BLUNDERBUSS_SCENE_HPP

#include <SceneObject.hpp>
#include <PrefabDispenser.hpp>

template<typename Derived>
class Scene
{
public:
    using Ptr = SceneObject::Ptr;
public:
    Scene() = delete;
    static void setup(PrefabDispenser& dispenser)
    {
        Derived::setup(dispenser);
    }
    static Ptr get(const PrefabDispenser& dispenser)
    {
        return Derived::get(dispenser);
    }
};

#endif //BLUNDERBUSS_SCENE_HPP

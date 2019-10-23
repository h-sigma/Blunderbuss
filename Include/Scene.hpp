//
// Created by harshdeep on 22/10/19.
//

#ifndef BLUNDERBUSS_SCENE_HPP
#define BLUNDERBUSS_SCENE_HPP

#include <SceneObject.hpp>
#include <PrefabDispenser.hpp>

class Scene
{
public:
    using Ptr = SceneObject::Ptr;
public:
    explicit Scene() = default;
    virtual ~Scene() = default;
    virtual Ptr get(PrefabDispenser&) = 0;
protected:
    //Implementation Details
};

#endif //BLUNDERBUSS_SCENE_HPP

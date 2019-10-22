//
// Created by harshdeep on 22/10/19.
//

#ifndef BLUNDERBUSS_SCENELOADER_HPP
#define BLUNDERBUSS_SCENELOADER_HPP


#include <SceneObject.hpp>
class Scene;

class SceneLoader {
public:
    using Ptr = SceneObject::Ptr;
public:
    explicit SceneLoader() = default;
    Ptr loadScene(const std::string&);
    void registerScene(const std::string&, Scene);
private:
    //implementation details
};


#endif //BLUNDERBUSS_SCENELOADER_HPP

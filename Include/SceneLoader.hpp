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
    template<typename T> void registerScene(const std::string&);
private:
    //implementation details
};


#endif //BLUNDERBUSS_SCENELOADER_HPP

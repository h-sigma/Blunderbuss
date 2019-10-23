//
// Created by harshdeep on 22/10/19.
//

#ifndef BLUNDERBUSS_SCENELOADER_HPP
#define BLUNDERBUSS_SCENELOADER_HPP


#include <SceneObject.hpp>
#include <unordered_map>
#include <functional>

class Scene;

class SceneLoader {
public:
    using Ptr = SceneObject::Ptr;
public:
    explicit SceneLoader(class PrefabDispenser&);
    [[nodiscard]] Ptr loadScene(const std::string&);
    template<typename T> void registerScene(const std::string&);
private:
    //implementation details
    class PrefabDispenser& mDispenser;
    std::unordered_map<std::string, std::function<Ptr()>> mMap;
};


#endif //BLUNDERBUSS_SCENELOADER_HPP

//
// Created by harshdeep on 22/10/19.
//

#ifndef BLUNDERBUSS_SCENELOADER_HPP
#define BLUNDERBUSS_SCENELOADER_HPP


#include <SceneObject.hpp>
#include <unordered_map>
#include <functional>
#include <cassert>

template<typename Derived> class Scene;

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

template<typename T>
void SceneLoader::registerScene(const std::string & sceneName) {
    static_assert(std::is_base_of_v<Scene<T>, T>, "Scene to be registered must derive from class Scene.");
    Scene<T>::setup(mDispenser);
    assert(mMap.find(sceneName) == mMap.end());
    mMap.emplace(sceneName, [this](){
        return Scene<T>::get(mDispenser);
    });
}


#endif //BLUNDERBUSS_SCENELOADER_HPP

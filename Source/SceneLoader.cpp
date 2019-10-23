//
// Created by harshdeep on 22/10/19.
//

#include <SceneLoader.hpp>
#include <Scene.hpp>
#include <cassert>

SceneLoader::SceneLoader(PrefabDispenser & dispenser) : mDispenser(dispenser) {
}

SceneLoader::Ptr SceneLoader::loadScene(const std::string & sceneName) {
    assert(mMap.find(sceneName) != mMap.end());
    return mMap[sceneName]();
}

template<typename T>
void SceneLoader::registerScene(const std::string & sceneName) {
    static_assert(std::is_base_of_v<Scene, T>, "Scene to be registered must derive from class Scene.");
    assert(mMap.find(sceneName) == mMap.end());
    mMap.emplace(sceneName, [this](){
        return T().get(mDispenser);
    });
}

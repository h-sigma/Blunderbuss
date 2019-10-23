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

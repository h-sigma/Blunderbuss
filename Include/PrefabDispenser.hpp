//
// Created by harshdeep on 22/10/19.
//

#ifndef BLUNDERBUSS_PREFABDISPENSER_HPP
#define BLUNDERBUSS_PREFABDISPENSER_HPP

#include <memory>
#include <cassert>
#include <functional>
#include <unordered_map>
#include <SceneObject.hpp>

class PrefabDispenser {
public:
    using Func = std::function<SceneObject*()>;
public:
    PrefabDispenser() = default;
    template<typename T> std::unique_ptr<T> getPrefab(const std::string&) const;
    void addPrefab(const std::string&, Func&);
private:
    std::unordered_map<std::string, Func> mMap;
};

template<typename T>
std::unique_ptr<T> PrefabDispenser::getPrefab(const std::string & name) const {
    auto found = mMap.find(name);
    assert(found != mMap.end());
    auto result = found->second();
    assert(dynamic_cast<T*>(result));
    return std::unique_ptr<T>(static_cast<T*>(result));
}


#endif //BLUNDERBUSS_PREFABDISPENSER_HPP

//
// Created by harshdeep on 22/10/19.
//

#ifndef BLUNDERBUSS_PREFABDISPENSER_HPP
#define BLUNDERBUSS_PREFABDISPENSER_HPP


#include <memory>
#include <functional>
#include <SceneObject.hpp>

class PrefabDispenser {
public:
    PrefabDispenser() = default;
    template<typename T> std::unique_ptr<T> getPrefab(const std::string&) const;
    template<typename T> void addPrefab(std::function<SceneObject::Ptr()>);
private:
    //implementation details
};


#endif //BLUNDERBUSS_PREFABDISPENSER_HPP

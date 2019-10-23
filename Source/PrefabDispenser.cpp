//
// Created by harshdeep on 22/10/19.
//

#include <PrefabDispenser.hpp>

void PrefabDispenser::addPrefab(const std::string& name, const Func& func) {
    assert(mMap.find(name) == mMap.end());
    mMap.emplace(name, func);
}
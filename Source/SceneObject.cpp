//
// Created by harshdeep on 18/10/19.
//

#include <SceneObject.hpp>
#include <cassert>

SceneObject::SceneObject(Category::ID category) : mCategory(category), mParent(nullptr) {

}

void SceneObject::attachChild(SceneObject::Ptr child) {
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneObject::Ptr SceneObject::detachChild(const SceneObject &node) {
    auto found_if = std::find_if(begin(mChildren), end(mChildren), [&node](const Ptr& sceneobj) { return sceneobj.get() == &node; });
    assert(found_if != mChildren.end());
    auto found_object = std::move(*found_if);
    found_object->mParent = nullptr;
    mChildren.erase(found_if);
    return found_object;
}

sf::Transform SceneObject::getWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;

    for(const SceneObject* node = this ; node != nullptr ; node = node->mParent )
    {
        transform *= node->getTransform();
    }

    return transform;
}

sf::Vector2f SceneObject::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f();
}

void SceneObject::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawCurrent(target, states);

    std::for_each(begin(mChildren), end(mChildren), [&target, states](const Ptr& childObj) { childObj->draw(target,states); });
}

void SceneObject::drawCurrent(sf::RenderTarget &, sf::RenderStates) const {
    //by default draws nothing, simpyly an interface
}

void SceneObject::update(sf::Time dt, SceneObject* World) {
    updateCurrent(dt, World);
    updateChildren(dt, World);
}

void SceneObject::updateCurrent(sf::Time, SceneObject*) {
    // by default does nothing
}

void SceneObject::updateChildren(sf::Time dt, SceneObject* World)  {
    std::for_each(begin(mChildren), end(mChildren), [dt, World](Ptr& childObj) { childObj->update(dt, World); });
}

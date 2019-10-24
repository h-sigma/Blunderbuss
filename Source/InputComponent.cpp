//
// Created by harshdeep on 24/10/19.
//

#include <InputComponent.hpp>
#include <GameObject.hpp>
#include <SFML/System/Time.hpp>

void InputComponent::update(sf::Time, class World & world) {
    auto queue = world.readQueue();
    queue.erase(std::unique(queue.begin(), queue.end()), queue.end());
    for(auto& item : queue)
    {
        mPM.match(item);
    }
}
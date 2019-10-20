//
// Created by harshdeep on 19/10/19.
//

#ifndef BLUNDERBUSS_COMPONENTQUEUE_HPP
#define BLUNDERBUSS_COMPONENTQUEUE_HPP

#include <vector>
#include <optional>

#include <FixedRingBuffer.hpp>

template <typename T>
class ComponentQueue
{
public:
    enum Type { Physics, Input, Graphics, TotalTypes };
public:
    virtual ~ComponentQueue() = default;
    std::optional<T> pop(Type);
    void push(Type, T);
private:
    std::vector<FixedRingBuffer<T,100>> mQueue;
};

template<typename T>
std::optional<T> ComponentQueue<T>::pop(ComponentQueue::Type) {
    if(mQueue.empty())
        return {};

}

template<typename T>
void ComponentQueue<T>::push(ComponentQueue::Type, T) {

}

#endif //BLUNDERBUSS_COMPONENTQUEUE_HPP

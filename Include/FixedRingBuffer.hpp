//
// Created by harshdeep on 19/10/19.
//

#ifndef BLUNDERBUSS_FIXEDRINGBUFFER_HPP
#define BLUNDERBUSS_FIXEDRINGBUFFER_HPP

#include <cstddef>
#include <array>
#include <optional>

template <typename T, std::size_t Size>
class FixedRingBuffer
{
public:
    explicit FixedRingBuffer() = default;
    bool push(const T&) noexcept(std::is_nothrow_copy_assignable_v<T>) ;
    bool push(T&&) noexcept(std::is_nothrow_move_constructible_v<T>) ;
    template<typename... Args> T* emplace(Args &&...);
    std::optional<T> pop() noexcept(std::is_nothrow_move_constructible_v<T>) ;
    void clear() noexcept;
    [[nodiscard]] bool is_empty() const noexcept ;
    [[nodiscard]] bool is_full() const noexcept ;
    [[nodiscard]] constexpr std::size_t  capacity() const noexcept ;
    [[nodiscard]] std::size_t size() const noexcept ;
private:
    std::array<T, Size> buffer_;
    std::size_t tail_ = 0u, head_ = 0u;
    bool full_ = false;
    // tail always rests at the next element to be inserted
};

template<typename T, std::size_t Size>
bool FixedRingBuffer<T, Size>::push(const T& t) noexcept(std::is_nothrow_copy_assignable_v<T>) {
    if(is_full())
        return false;
    buffer_[tail_] = t;
    tail_++;
    if(tail_ == Size)
        tail_ = 0u;
    if(tail_ == head_)
        full_ = true;
    return true;
}

template<typename T, std::size_t Size>
bool FixedRingBuffer<T, Size>::push(T && t) noexcept(std::is_nothrow_move_constructible_v<T>) {
    if(is_full())
        return false;
    buffer_[tail_] = t;
    tail_++;
    if(tail_ == Size)
        tail_ = 0u;
    if(tail_ == head_)
        full_ = true;
    return true;
}

template<typename T, std::size_t Size>
std::optional<T> FixedRingBuffer<T, Size>::pop() noexcept(std::is_nothrow_move_constructible_v<T>) {
    if(is_empty())
        return {};
    auto found = head_;
    head_++;
    if(head_ == Size)
        head_ = 0u;
    full_ = false;
    return {std::move(buffer_[found])};
}

template<typename T, std::size_t Size>
bool FixedRingBuffer<T, Size>::is_empty() const noexcept {
    return head_ == tail_ && !is_full();
}

template<typename T, std::size_t Size>
bool FixedRingBuffer<T, Size>::is_full() const noexcept {
    return full_;
}

template<typename T, std::size_t Size>
void FixedRingBuffer<T, Size>::clear() noexcept {
    head_ == tail_ == 0u;
    full_ = false;
}

template<typename T, std::size_t Size>
constexpr std::size_t FixedRingBuffer<T, Size>::capacity() const noexcept {
    return Size;
}

template<typename T, std::size_t Size>
std::size_t FixedRingBuffer<T, Size>::size() const noexcept {
    if(tail_ < head_)
        return capacity() - (head_ - tail_) ;
    else if(head_ < tail_)
        return tail_ - head_;
    else
    {
        if(is_full())
            return capacity();
        else
            return 0u;  //empty
    }
}

template<typename T, std::size_t Size>
template<typename... Args>
T* FixedRingBuffer<T, Size>::emplace(Args &&... args) {
    if(is_full())
        return nullptr;
    new(&buffer_[tail_]) T(std::forward<Args>(args)...);
    auto t = &buffer_[tail_];
    tail_++;
    if(tail_ == Size)
        tail_ = 0u;
    if(tail_ == head_)
        full_ = true;
    return t;
}

#endif //BLUNDERBUSS_FIXEDRINGBUFFER_HPP

//
// Created by harshdeep on 19/10/19.
//

#ifndef BLUNDERBUSS_DYNAMICRINGBUFFER_HPP
#define BLUNDERBUSS_DYNAMICRINGBUFFER_HPP

#include <cstddef>
#include <type_traits>
#include <optional>
#include <memory>
#include <vector>
#include <iterator>

template<typename T, class C = std::vector<T>>
class DynamicRingBuffer
{
public:
    explicit DynamicRingBuffer(std::size_t size);

    void push(const T&) noexcept(std::is_nothrow_copy_assignable_v<T>) ;
    void push(T&&) noexcept(std::is_nothrow_move_constructible_v<T>) ;
    template<typename... Args> T& emplace(Args &&...);
    std::optional<T> pop() noexcept(std::is_nothrow_move_constructible_v<T>) ;

    void clear() noexcept ;
    [[nodiscard]] bool is_empty() const noexcept ;
    [[nodiscard]] constexpr std::size_t  capacity() const noexcept ;
    [[nodiscard]] std::size_t size() const noexcept ;
private:
    [[nodiscard]] bool is_full() const noexcept ;
    void expandBuffer();
private:
    C buffer_;
    std::size_t capacity_;
    typename C::iterator tail_, head_;
    bool full_;
public:
    typedef typename C::allocator_type allocator_type;
    typedef typename C::value_type value_type;
    typedef typename C::reference reference;
    typedef typename C::const_reference const_reference;
    typedef typename C::difference_type difference_type;
    typedef typename C::size_type size_type;

    class iterator {
    public:
        typedef typename C::difference_type difference_type;
        typedef typename C::value_type value_type;
        typedef typename C::reference reference;
        typedef typename C::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category; //or another tag

        iterator() = default;
        iterator(const iterator&);
        ~iterator() = default;

        iterator& operator=(const iterator&);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

        iterator& operator++();

        reference operator*() const;
        pointer operator->() const;
    private:
        typename C::iterator iter_;
        DynamicRingBuffer<T, C>* container_ = nullptr;
        bool is_begin_ = false;
        friend class DynamicRingBuffer;
    };
    class const_iterator {
    public:
        typedef typename C::difference_type difference_type;
        typedef typename C::value_type value_type;
        typedef const typename C::reference reference;
        typedef const typename C::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category; //or another tag

        const_iterator () = default;
        const_iterator (const const_iterator&);
        explicit const_iterator (const iterator&);
        ~const_iterator() = default;

        const_iterator& operator=(const const_iterator&);
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;

        const_iterator& operator++();

        reference operator*() const;
        pointer operator->() const;
    private:
        typename C::const_iterator iter_;
        const DynamicRingBuffer<T, C> * container_ = nullptr;
        bool is_begin_ = false;
        friend class DynamicRingBuffer;
    };
    friend class iterator;
    friend class const_iterator;

    typedef std::reverse_iterator<iterator> reverse_iterator; //optional
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator; //optional

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
};


template<typename T, class C>
DynamicRingBuffer<T, C>::DynamicRingBuffer(std::size_t size)
: buffer_(size)
, capacity_(size)
, tail_(buffer_.begin())
, head_(buffer_.begin())
, full_(false) {

}


template<typename T, class C>
void DynamicRingBuffer<T, C>::push(const T& t) noexcept(std::is_nothrow_copy_assignable_v<T>) {
    if(is_full())
        expandBuffer();
    *tail_ = t;
    tail_++;
    if(tail_ == buffer_.end())
        tail_ = buffer_.begin();
    if(tail_ == head_)
        full_ = true;
}

template<typename T, class C>
void DynamicRingBuffer<T, C>::push(T && t) noexcept(std::is_nothrow_move_constructible_v<T>) {
    if(is_full())
        expandBuffer();
    *tail_ = t;
    tail_++;
    if(tail_ == buffer_.end())
        tail_ = buffer_.begin();
    if(tail_ == head_)
        full_ = true;
}

template<typename T, class C>
std::optional<T> DynamicRingBuffer<T, C>::pop() noexcept(std::is_nothrow_move_constructible_v<T>) {
    if(is_empty())
        return {};
    std::move_iterator<decltype(head_)> found (head_);
    head_++;
    if(head_ == buffer_.end())
        head_ = buffer_.begin();
    full_ = false;
    return {*found};
}

template<typename T, class C>
bool DynamicRingBuffer<T, C>::is_empty() const noexcept {
    return head_ == tail_ && !is_full();
}

template<typename T, class C>
bool DynamicRingBuffer<T, C>::is_full() const noexcept {
    return full_;
}

template<typename T, class C>
void DynamicRingBuffer<T, C>::clear() noexcept {
    buffer_.clear();
    head_ = tail_ = buffer_.begin();
    full_ = false;
}

template<typename T, class C>
constexpr std::size_t DynamicRingBuffer<T, C>::capacity() const noexcept {
    return capacity_;
}

template<typename T, class C>
std::size_t DynamicRingBuffer<T, C>::size() const noexcept {
    if(tail_ < head_)
        return capacity() - std::distance(tail_, head_) ;
    else if(head_ < tail_)
        return std::distance(head_, tail_);
    else
    {
        if(is_full())
            return capacity();
        else
            return 0u;  //empty
    }
}

template<typename T, class C>
template<typename... Args>
T& DynamicRingBuffer<T, C>::emplace(Args &&... args) {
    if(is_full())
        expandBuffer();
    new(&(*tail_)) T(std::forward<Args>(args)...);
    auto& t = *tail_;
    tail_++;
    if(tail_ == buffer_.end())
        tail_ = buffer_.begin();
    if(tail_ == head_)
        full_ = true;
    return t;
}

template<typename T, class C>
void DynamicRingBuffer<T, C>::expandBuffer() {
    const int expandBy = 2;
    const auto newCapacity = capacity() * expandBy;
    auto newBuffer = std::vector<T>(newCapacity);

    std::size_t tailIndex;

    auto bufferShapeA = [this, &newBuffer, &tailIndex]() noexcept { // [...head----tail...]
        auto newEnd = std::move(buffer_.begin(), buffer_.end(), newBuffer.begin());
        tailIndex = std::distance(newBuffer.begin(), newEnd);
    };

    auto bufferShapeB = [this, &newBuffer, &tailIndex]() noexcept { // [---tail...head---]
        auto halfEnd = std::move(head_, buffer_.end(), newBuffer.begin());
        auto newEnd = std::move(buffer_.begin(), tail_, halfEnd);
        tailIndex = std::distance(newBuffer.begin(), newEnd);
    };

    if(head_ < tail_)
        bufferShapeA();
    else if (tail_ < head_)
        bufferShapeB();
    else if (is_full())
    {
        if(head_ == buffer_.begin())
            bufferShapeA();
        else
            bufferShapeB();
    }

    buffer_ = std::move(newBuffer);
    head_ = buffer_.begin();
    tail_ = std::next(buffer_.begin(), tailIndex);
    capacity_ = newCapacity;
    full_ = false;
}

#include "DynamicRingBufferIterator.inl"


#endif //BLUNDERBUSS_DYNAMICRINGBUFFER_HPP

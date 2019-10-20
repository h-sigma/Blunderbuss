
/*
 * ITERATOR IMPLEMENTATIONS
 */


template<typename T, class C>
DynamicRingBuffer<T, C>::iterator::iterator(const DynamicRingBuffer::iterator & other) {
    iter_ = other.iter_;
    container_ = other.container_;
    is_begin_ = other.is_begin_;
}

template<typename T, class C>
typename DynamicRingBuffer<T, C>::iterator &DynamicRingBuffer<T, C>::iterator::operator=(const DynamicRingBuffer::iterator & other) {
    iter_ = other.iter_;
    container_ = other.container_;
    is_begin_ = other.is_begin_;
    return *this;
}

template<typename T, class C>
bool DynamicRingBuffer<T, C>::iterator::operator==(const DynamicRingBuffer::iterator & other) const {
    return iter_ == other.iter_ && (is_begin_ == other.is_begin_ || (container_->is_empty() && other.container_->is_empty())) ;
}

template<typename T, class C>
bool DynamicRingBuffer<T, C>::iterator::operator!=(const DynamicRingBuffer::iterator & other) const {
    return !(*this == other);
}

template<typename T, class C>
typename DynamicRingBuffer<T, C>::iterator &DynamicRingBuffer<T, C>::iterator::operator++() {
    if(iter_ != container_->tail_ || is_begin_)
        iter_++;
    if(iter_ == container_->buffer_.end())
        iter_ = container_->buffer_.begin();
    is_begin_ = false;
    return *this;
}

template<typename T, class C>
typename DynamicRingBuffer<T, C>::iterator::reference DynamicRingBuffer<T, C>::iterator::operator*() const {
    return *iter_;
}

template<typename T, class C>
typename DynamicRingBuffer<T, C>::iterator::pointer DynamicRingBuffer<T, C>::iterator::operator->() const {
    return iter_;
}

//const iterators

template<typename T, class C>
DynamicRingBuffer<T, C>::const_iterator::const_iterator(const DynamicRingBuffer::const_iterator & other) {
    iter_ = other.iter_;
    container_ = other.container_;
    is_begin_ = other.is_begin_;
}

template<typename T, class C>
DynamicRingBuffer<T, C>::const_iterator::const_iterator(const DynamicRingBuffer::iterator & other) {
    iter_ = other.iter_;
    container_ = other.container_;
    is_begin_ = other.is_begin_;
}

template<typename T, class C>
typename DynamicRingBuffer<T, C>::const_iterator &
DynamicRingBuffer<T, C>::const_iterator::operator=(const DynamicRingBuffer::const_iterator & other) {
    iter_ = other.iter_;
    container_ = other.container_;
    is_begin_ = other.is_begin_;
    return *this;
}

template<typename T, class C>
bool DynamicRingBuffer<T, C>::const_iterator::operator==(const DynamicRingBuffer::const_iterator & other) const {
    return iter_ == other.iter_ && (is_begin_ == other.is_begin_ || (container_->is_empty() && other.container_->is_empty()));
}

template<typename T, class C>
bool DynamicRingBuffer<T, C>::const_iterator::operator!=(const DynamicRingBuffer::const_iterator & other) const {
    return !(*this == other);
}

template<typename T, class C>
typename DynamicRingBuffer<T, C>::const_iterator &DynamicRingBuffer<T, C>::const_iterator::operator++() {
    if(iter_ != container_->tail_ || is_begin_)
        iter_++;
    if(iter_ == container_->buffer_.end())
        iter_ = container_->buffer_.begin();
    is_begin_ = false;
    return *this;
}

template<typename T, class C>
typename DynamicRingBuffer<T, C>::const_iterator::reference DynamicRingBuffer<T, C>::const_iterator::operator*() const {
    return *iter_;
}

template<typename T, class C>
typename DynamicRingBuffer<T, C>::const_iterator::pointer DynamicRingBuffer<T, C>::const_iterator::operator->() const {
    return iter_;
}

/*
 * ITERATOR RETURN IMPLEMENTATIONS
 */


template<typename T, class C>
typename DynamicRingBuffer<T, C>::iterator DynamicRingBuffer<T, C>::begin() {
    DynamicRingBuffer::iterator result;
    result.iter_ = head_;
    result.container_ = this;
    result.is_begin_ = true;
    return result;
}

template<typename T, class C>
typename DynamicRingBuffer<T, C>::const_iterator DynamicRingBuffer<T, C>::begin() const {
    DynamicRingBuffer::const_iterator result;
    result.iter_ = head_;
    result.container_ = this;
    result.is_begin_ = true;
    return result;
}

template<typename T, class C>
typename DynamicRingBuffer<T, C>::const_iterator DynamicRingBuffer<T, C>::cbegin() const {
    return begin();
}

template<typename T, class C>
typename DynamicRingBuffer<T, C>::iterator DynamicRingBuffer<T, C>::end() {
    DynamicRingBuffer::iterator result;
    result.iter_ = tail_;
    result.container_ = this;
    result.is_begin_ = false;
    return result;
}

template<typename T, class C>
typename DynamicRingBuffer<T, C>::const_iterator DynamicRingBuffer<T, C>::end() const {
    DynamicRingBuffer::const_iterator result;
    result.iter_ = tail_;
    result.container_ = this;
    result.is_begin_ = false;
    return result;
}

template<typename T, class C>
typename DynamicRingBuffer<T, C>::const_iterator DynamicRingBuffer<T, C>::cend() const {
    return end();
}

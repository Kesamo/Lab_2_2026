#pragma once
#include "IEnumerator.hpp"
#include "Exceptions.hpp"

template <class T>
class ArrayIterator: public IEnumerator<T> {
private:
    const T* data_;
    size_t index_;
    size_t size_;
    size_t start_
public:
    ArrayIterator(const T* data, size_t size, size_t startIndex) : data_(data), index_(startIndex), size_(size), start_(startIndex) {}
    T& Current() const override {
        if (index_ >= size_) {
            throw IteratorPointerException(index_);
        }
        return const_cast<T&>(data_[index_]);
    }

    bool MoveNext() override {
        if(index_ >= size_){
            return false;
        }
        ++index_;
        return index_ < size_;
    }

    void Reset() override {
        index_ = start_;
    }

    T operator*() const{
        return Current();
    }

    ArrayIterator& operator++(){
        MoveNext();
        return *this;
    }

    bool operator!=(const ArrayIterator& other) const {
        return index_ != other.index_;
    }

    bool operator==(const ArrayIterator& other) const {
        return index_ == other.index_;
    }
};
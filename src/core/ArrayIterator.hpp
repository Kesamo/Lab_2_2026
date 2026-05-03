#pragma once
#include "../utils/IEnumerator.hpp"

template <class T>
class ArrayIterator: public IEnumerator<T> {
private:
    const T* data_;
    int index_;
    int size_;
public:
    ArrayIterator(const T* data, int size, int startIndex) : data_(data), index_(startIndex), size_(size) {}
    T& Current() const override {
        if (index_ < 0 || index_ >= size_) {
            throw std::out_of_range("ArrayIterator: Current() out of bounds");
        }
        return const_cast<T&>(data_[index_]);
    }

    bool MoveNext() override {
        ++index_;
        return index_ < size_;
    }

    void Reset() override {
        index_ = -1;
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
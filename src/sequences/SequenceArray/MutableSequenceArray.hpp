#pragma once
#include "SequenceArray.hpp"

template <class T>
class MutableSequenceArray : public SequenceArray<T> {
    public:
    using SequenceArray<T>::SequenceArray;
    ~MutableSequenceArray() = default;

    SequenceArray<T>* Instance() override {
        return this;
    }
    SequenceArray<T>* Clone() const override {
        return new MutableSequenceArray<T>(*this);
    }
    SequenceArray<T>* Construct() const override {
        return new MutableSequenceArray<T>();
    }
};
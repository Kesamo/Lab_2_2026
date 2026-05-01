#pragma once
#include "SequenceArray.hpp"

template <class T>
class ImmutableSequenceArray : public SequenceArray<T> {
    public:
    using SequenceArray<T>::SequenceArray;
    ~ImmutableSequenceArray() = default;

    SequenceArray<T>* Instance() override {
        return this->Clone();
    }
    SequenceArray<T>* Clone() const override {
        return new ImmutableSequenceArray<T>(*this);
    }
    SequenceArray<T>* Construct() const override {
        return new ImmutableSequenceArray<T>();
    }
};

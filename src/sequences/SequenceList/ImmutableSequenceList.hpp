#pragma once
#include "SequenceList.hpp"

template <class T>
class ImmutableSequenceList : public SequenceList<T> {
public:
    using SequenceList<T>::SequenceList;
    ~ImmutableSequenceList() = default;

    SequenceList<T>* Instance() override {
        return this->Clone();
    }
    SequenceList<T>* Clone() const override {
        return new ImmutableSequenceList<T>(*this);
    }
    SequenceList<T>* Construct() const override {
        return new ImmutableSequenceList<T>();
    }
};

#pragma once
#include "SequenceList.hpp"

template <class T>
class MutableSequenceList : public SequenceList<T> {
public:
    using SequenceList<T>::SequenceList;
    ~MutableSequenceList() = default;

    SequenceList<T>* Instance() override {
        return this->Clone();
    }
    SequenceList<T>* Clone() const override {
        return new MutableSequenceList<T>(*this);
    }
    SequenceList<T>* Construct() const override {
        return new MutableSequenceList<T>();
    }
};
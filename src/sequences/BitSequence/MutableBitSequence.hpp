#pragma once
#include "BitSequence.hpp"

template <std::integral T>
class MutableBitSequence : public BitSequence<T>{
    public:
    using BitSequence<T>::BitSequence;
    ~MutableBitSequence() = default;

    BitSequence<T>* Instance() override {
        return this;
    }
    BitSequence<T>* Clone() const override {
        return new MutableBitSequence<T>(*this);
    }
    BitSequence<T>* Construct() const override {
        return new MutableBitSequence<T>();
    }
};
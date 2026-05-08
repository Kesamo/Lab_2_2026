#pragma once
#include "BitSequence.hpp"

template <std::integral T>
class ImmutableBitSequence : public BitSequence<T>{
    public:
    using BitSequence<T>::BitSequence;
    ~ImmutableBitSequence() = default;

    BitSequence<T>* Instance() override {
        return this->Clone();
    }
    BitSequence<T>* Clone() const override {
        return new ImmutableBitSequence<T>(*this);
    }
    BitSequence<T>* Construct() const override {
        return new ImmutableBitSequence<T>();
    }
};
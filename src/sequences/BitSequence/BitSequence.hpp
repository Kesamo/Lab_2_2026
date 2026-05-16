#pragma once
#include <Sequence.hpp>
#include "BitProxy.hpp"
#include "DynamicArray.hpp"
#include "IEnumerator.hpp"

template <std::integral T>
class BitSequence : public Sequence<Bit<T>>{
private:
    DynamicArray<Bit<T>> array;

    BitSequence<T>* appendInternal(Bit<T> item);
    BitSequence<T>* prependInternal(Bit<T> item);
    BitSequence<T>* insertAtInternal(Bit<T> item, int index);
    
    
    public:

    BitSequence();
    BitSequence(Bit<T>* item, size_t count);
    BitSequence(const BitSequence<T> & other);

    ArrayIterator<T> begin() const ;
    ArrayIterator<T> end() const ;

    virtual BitSequence<T>* Instance() = 0;
    virtual BitSequence<T>* Clone() const = 0;
    virtual BitSequence<T>* Construct() const = 0;

    Bit<T> GetFirst() const override;
    Bit<T> GetLast() const override;
    Bit<T> Get(int index) const override;
    size_t GetLength() const override;
    Sequence<Bit<T>>* GetSubsequence(int startIndex, int endIndex) const override;
    
    IEnumerator<Bit<T>>* GetEnumerator() const override;

    Sequence<Bit<T>>* append(Bit<T> value) override;
    Sequence<Bit<T>>* prepend(Bit<T> value) override;
    Sequence<Bit<T>>* insertAt(Bit<T> item, int index) override;
    Sequence<Bit<T>>* Concat(Sequence<Bit<T>> *list) const override;


    auto operator[](size_t idx);
    auto operator[](size_t idx) const;
};

#include "BitSequence.tpp"
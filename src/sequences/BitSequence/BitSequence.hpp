#pragma once
#include <Sequence.hpp>
#include "BitProxy.hpp"
#include "DynamicArray.hpp"
#include "IEnumerator.hpp"

template <std::integral T>
class BitSequence : public Sequence<T>{
private:
    DynamicArray<T> array;

    BitSequence<T>* appendInternal(T item);
    BitSequence<T>* prependInternal(T item);
    BitSequence<T>* insertAtInternal(T item, int index);
    
    
    public:

    BitSequence();
    BitSequence(T* item, size_t count);
    BitSequence(const BitSequence<T> & other);

    ArrayIterator<T> begin() const ;
    ArrayIterator<T> end() const ;

    virtual BitSequence<T>* Instance() = 0;
    virtual BitSequence<T>* Clone() const = 0;
    virtual BitSequence<T>* Construct() const = 0;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    size_t GetLength() const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    
    IEnumerator<T>* GetEnumerator() const override;

    Sequence<T>* append(T value) override;
    Sequence<T>* prepend(T value) override;
    Sequence<T>* insertAt(T item, int index) override;
    Sequence<T>* Concat(Sequence<T> *list) const override;


    auto operator[](size_t idx);
    auto operator[](size_t idx) const;
};

#include "BitSequence.tpp"
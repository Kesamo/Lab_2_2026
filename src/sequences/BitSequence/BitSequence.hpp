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
    BitSequence<T>* insertAtInternal(Bit<T> item, size_t index);
    BitSequence<T>* RemoveLastInternal();
    
    
    public:

    BitSequence();
    BitSequence(Bit<T>* item, size_t count);
    BitSequence(const BitSequence<T> & other);

    ArrayIterator<Bit<T>> begin() const ;
    ArrayIterator<Bit<T>> end() const ;

    virtual BitSequence<T>* Instance() = 0;
    virtual BitSequence<T>* Clone() const = 0;
    virtual BitSequence<T>* Construct() const = 0;

    Bit<T> GetFirst() const override;
    Bit<T> GetLast() const override;
    Bit<T> Get(size_t index) const override;
    size_t GetLength() const override;
    Sequence<Bit<T>>* GetSubsequence(size_t startIndex, size_t endIndex) const override;
    
    IEnumerator<Bit<T>>* GetEnumerator() const override;

    Sequence<Bit<T>>* append(Bit<T> value) override;
    Sequence<Bit<T>>* prepend(Bit<T> value) override;
    Sequence<Bit<T>>* insertAt(Bit<T> item, size_t index) override;
    Sequence<Bit<T>>* Concat(Sequence<Bit<T>> *list) const override;
    Sequence<Bit<T>>* RemoveLast() override;

    T GetAsInteger(size_t index) const;

    Bit<T>& GetMutable(size_t index){
        return array[index];
    }

    auto operator[](size_t idx);
    auto operator[](size_t idx) const;

    Sequence<Bit<T>>* Map(Bit<T> (*func)(Bit<T>)) override;
    Sequence<Bit<T>>* Where(bool (*predicate)(Bit<T>)) override;
    Sequence<Bit<T>>* Reduce(Bit<T> (*func)(Bit<T>, Bit<T>), Bit<T> starter) override;
};

#include "BitSequence.tpp"
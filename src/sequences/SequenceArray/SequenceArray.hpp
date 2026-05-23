#pragma once
#include "DynamicArray.hpp"
#include "Sequence.hpp"
#include "Exceptions.hpp"
#include "ArrayIterator.hpp"

template <class T>
class SequenceArray : public Sequence<T>{
    protected:
    DynamicArray<T> array;
    
    SequenceArray<T>* appendInternal(T item);
    SequenceArray<T>* prependInternal(T item);
    SequenceArray<T>* insertAtInternal(T item, size_t index);
    SequenceArray<T>* RemoveLastInternal();
    
    public:

    SequenceArray();
    SequenceArray(T* item, size_t count);
    SequenceArray(const SequenceArray<T>& other);
    
    virtual SequenceArray<T>* Instance() = 0;
    virtual SequenceArray<T>* Clone() const = 0;
    virtual SequenceArray<T>* Construct() const = 0;

    IEnumerator<T>* GetEnumerator() const override;

    ArrayIterator<T> begin() const;
    ArrayIterator<T> end() const;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(size_t index) const override;
    size_t GetLength() const override;
    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override;
    
    Sequence<T>* append(T value) override;
    Sequence<T>* prepend(T value) override;
    Sequence<T>* insertAt(T item, size_t index) override;
    Sequence<T>* Concat(Sequence<T> *list) const override;
    Sequence<T>* RemoveLast() override;

    Sequence<T>* Map(T (*func)(T)) override;
    Sequence<T>* Where(bool (*predicate)(T)) override;
    Sequence<T>* Reduce(T (*func)(T, T), T starter) override;
};

#include "SequenceArray.tpp"

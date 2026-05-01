#pragma once
#include "DynamicArray.hpp"
#include "Sequence.hpp"
#include "EnumeratorSequence.hpp"

template <class T>
class SequenceArray : public Sequence<T>{
    protected:
    DynamicArray<T>* array;
    
    SequenceArray<T>* appendInternal(T item);
    SequenceArray<T>* prependInternal(T item);
    SequenceArray<T>* insertAtInternal(T item, int index);
    
    public:

    SequenceArray();
    SequenceArray(T* item, int count);
    SequenceArray(const SequenceArray<T>& other);

    ~SequenceArray();
    
    virtual SequenceArray<T>* Instance() = 0;
    virtual SequenceArray<T>* Clone() const = 0;
    virtual SequenceArray<T>* Construct() const = 0;

    IEnumerator<T>* GetEnumerator() const override;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    int GetLength() const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    
    Sequence<T>* append(T value) override;
    Sequence<T>* prepend(T value) override;
    Sequence<T>* insertAt(T item, int index) override;
    Sequence<T>* Concat(Sequence<T> *list) const override;
};

#include "SequenceArray.tpp"


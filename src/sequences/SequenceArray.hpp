#pragma once
#include "DynamicArray.hpp"
#include "Sequence.hpp"

template <class T>
class SequenceArray : public Sequence<T>{
    private:
    DynamicArray<T>* array;

    public:
    SequenceArray();
    SequenceArray(T* item, int count);
    SequenceArray(const SequenceArray<T>& other);
    ~SequenceArray();

    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    int GetLength() const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    
    Sequence<T>* append(T value) override;
    Sequence<T>* prepend(T value) override;
    Sequence<T>* insertAt(T item, int index) override;
    Sequence<T>* Concat(Sequence <T> *list) override;
};

#include "SequenceArray.tpp"
#pragma once
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include "ListIterator.hpp"

template <class T>
class SequenceList : public Sequence<T>{
    protected:
    LinkedList<T> list;

    SequenceList<T>* appendInternal(T item);
    SequenceList<T>* prependInternal(T item);
    SequenceList<T>* insertAtInternal(T item, size_t index);

    
    public:
    SequenceList();
    SequenceList(T* items, size_t count);
    SequenceList(const SequenceList<T>& other);

    virtual SequenceList<T>* Instance() = 0;
    virtual SequenceList<T>* Clone() const = 0;
    virtual SequenceList<T>* Construct() const = 0;
    
    IEnumerator<T>* GetEnumerator() const override;

    ListIterator<T> begin() const ;
    ListIterator<T> end() const ;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(size_t index) const override;
    size_t GetLength() const override;
    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override;
    
    Sequence<T>* append(T value) override;
    Sequence<T>* prepend(T value) override;
    Sequence<T>* insertAt(T item, size_t index) override;
    Sequence<T>* Concat(Sequence<T> *seq) const override;
};

#include "SequenceList.tpp"
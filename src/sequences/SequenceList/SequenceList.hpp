#pragma once
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include "ListIterator.hpp"

template <class T>
class SequenceList : public Sequence<T>{
    protected:
    LinkedList<T>* list = nullptr;

    SequenceList<T>* appendInternal(T item);
    SequenceList<T>* prependInternal(T item);
    SequenceList<T>* insertAtInternal(T item, int index);

    
    public:
    SequenceList();
    SequenceList(T* items, int count);
    SequenceList(const SequenceList<T>& other);

    ~SequenceList();

    virtual SequenceList<T>* Instance() = 0;
    virtual SequenceList<T>* Clone() const = 0;
    virtual SequenceList<T>* Construct() const = 0;
    
    IEnumerator<T>* GetEnumerator() const override;

    ListIterator<T> begin() const ;
    ListIterator<T> end() const ;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    size_t GetLength() const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    
    Sequence<T>* append(T value) override;
    Sequence<T>* prepend(T value) override;
    Sequence<T>* insertAt(T item, int index) override;
    Sequence<T>* Concat(Sequence<T> *seq) const override;
};

#include "SequenceList.tpp"
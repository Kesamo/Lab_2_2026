#pragma once
#include "LinkedList.hpp"
#include "Sequence.hpp"

template <class T>
class SequenceList : public Sequence<T>{
    protected:
    LinkedList<T>* list;

    SequenceList();
    SequenceList(T* items, int count);
    SequenceList(const SequenceList<T>& other);

    ~SequenceList();

    public:

    IEnumerator<T>* GetEnumerator() override;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    int GetLength() const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    
    Sequence<T>* append(T value) override;
    Sequence<T>* prepend(T value) override;
    Sequence<T>* insertAt(T item, int index) override;
    Sequence<T>* Concat(Sequence<T> *seq) override;
};

#include "SequenceList.tpp"
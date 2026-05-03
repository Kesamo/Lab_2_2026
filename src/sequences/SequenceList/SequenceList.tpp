#pragma once
#include "SequenceList.hpp"

template <class T>
SequenceList<T>::SequenceList() : list(new LinkedList<T>()) {}

template <class T>
SequenceList<T>::SequenceList(T* items, int count) : list(new LinkedList( items, count)) {}

template <class T>
SequenceList<T>::SequenceList(const SequenceList<T>& other) : list(new LinkedList<T>(*other.list)) {}

template <class T>
SequenceList<T>::~SequenceList() {delete list;}

template <class T>
T SequenceList<T>::GetFirst() const {
    return list->GetFirst();
}

template <class T>
T SequenceList<T>::GetLast() const {
    return list->GetLast();
}

template <class T>
T SequenceList<T>::Get(int index) const {
    return list->Get(index);
}

template <class T>
int SequenceList<T>::GetLength() const {
    return list->GetLength();
}

template <class T>
Sequence<T>* SequenceList<T>::GetSubsequence(int startIndex, int endIndex) const {
    SequenceList<T>* res = SequenceList<T>();
    for (int i = startIndex; i <= endIndex; ++i){
            res->append(list->Get(i));
    }
    return res;
}

template <class T>
Sequence<T>* SequenceList<T>::append(T value){
    list->append(value);
    return this;
}

template <class T>
Sequence<T>* SequenceList<T>::prepend(T value){
    list->prepend(value);
    return this;
}

template <class T>
Sequence<T>* SequenceList<T>::insertAt(T item, int index){
    list->insertAt(item, index);
    return this;
}

template <class T>
IEnumerator<T>* SequenceList<T>::GetEnumerator(){
    return new EnumeratorSequence<T>(this);
}

template <class T>
Sequence<T>* SequenceList<T>::Concat(Sequence<T>* seq){
    SequenceList<T>* res = SequenceList<T>(*this);
    for (int i = 0; i < seq->GetLength(); ++i){
        res->list->append(seq->Get(i));
    }
    return res;
}
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
SequenceList<T>* SequenceList<T>::appendInternal(T item){
    list->append(item);
    return this;
}

template <class T>
SequenceList<T>* SequenceList<T>::prependInternal(T item){
    list->prepend(item);
    return this;
}

template <class T>
SequenceList<T>* SequenceList<T>::insertAtInternal(T item, int index){
    list->insertAt(item, index);
    return this;
}

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
    SequenceList<T>* res = Construct();
    for (int i = startIndex; i <= endIndex; ++i){
            res->appendInternal(list->Get(i));
    }
    return res;
}

template <class T>
Sequence<T>* SequenceList<T>::append(T value){
    return Instance()->appendInternal(value);
}

template <class T>
Sequence<T>* SequenceList<T>::prepend(T value){
    return Instance()->prependInternal(value);
}

template <class T>
Sequence<T>* SequenceList<T>::insertAt(T item, int index){
    return Instance()->insertAtInternal(item, index);
}

template <class T>
IEnumerator<T>* SequenceList<T>::GetEnumerator(){
    return new EnumeratorSequence<T>(this);
}

template <class T>
Sequence<T>* SequenceList<T>::Concat(Sequence<T>* seq){
    SequenceList<T>* res = Construct();
    for (int i = 0; i < GetLength(); ++i){
        res->appendInternal(Get(i));
    }
    for (int i = 0; i < seq->GetLength(); ++i){
        res->appendInternal(seq->Get(i));
    }
    return res;
}
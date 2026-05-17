#pragma once
#include "SequenceList.hpp"
#include "IEnumerator.hpp"

template <class T>
SequenceList<T>::SequenceList() : list(LinkedList<T>()) {}

template <class T>
SequenceList<T>::SequenceList(T* items, size_t count) : list(LinkedList( items, count)) {}

template <class T>
SequenceList<T>::SequenceList(const SequenceList<T>& other) : list(LinkedList<T>(other.list)) {}

template <class T>
SequenceList<T>* SequenceList<T>::appendInternal(T item){
    list.append(item);
    return this;
}

template <class T>
SequenceList<T>* SequenceList<T>::prependInternal(T item){
    list.prepend(item);
    return this;
}

template <class T>
SequenceList<T>* SequenceList<T>::insertAtInternal(T item, size_t index){
    list.insertAt(item, index);
    return this;
}

template <class T>
T SequenceList<T>::GetFirst() const {
    return list.GetFirst();
}

template <class T>
T SequenceList<T>::GetLast() const {
    return list.GetLast();
}

template <class T>
T SequenceList<T>::Get(size_t index) const {
    return list.Get(index);
}

template <class T>
size_t SequenceList<T>::GetLength() const {
    return list.GetLength();
}

template <class T>
Sequence<T>* SequenceList<T>::GetSubsequence(size_t startIndex, size_t endIndex) const {
    SequenceList<T>* res = Construct();
    size_t size = GetLength();
    if (startIndex > endIndex || endIndex > size){
        throw InvalidRangeException(startIndex, endIndex);
    }
    for (size_t i = startIndex; i <= endIndex; ++i){
            res->appendInternal(list.Get(i));
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
Sequence<T>* SequenceList<T>::insertAt(T item, size_t index){
    return Instance()->insertAtInternal(item, index);
}

template <class T>
IEnumerator<T>* SequenceList<T>::GetEnumerator() const{
    return list.GetEnumerator();
}

template <class T>
Sequence<T>* SequenceList<T>::Concat(Sequence<T>* seq) const{
    SequenceList<T>* res = Construct();
    if (seq == nullptr){
        throw EmptyListException();
    }
    for (auto item : *this){
        res->appendInternal(item);
    }
    for (size_t i = 0; i < seq->GetLength(); ++i){
        res->appendInternal(seq->Get(i));
    }
    return res;
}

template <class T>
ListIterator<T> SequenceList<T>::begin() const {
    return list.begin();
}

template <class T>
ListIterator<T> SequenceList<T>::end() const {
    return list.end();
}
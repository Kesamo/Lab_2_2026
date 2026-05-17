#include <cstddef>
#include <stdexcept>
#include "SequenceArray.hpp"

template <class T>
SequenceArray<T>::SequenceArray() : array(DynamicArray<T>()) {}

template <class T>
SequenceArray<T>::SequenceArray(T* item, size_t count) : array(DynamicArray<T>(item, count)) {}

template <class T>
SequenceArray<T>::SequenceArray(const SequenceArray<T>& other) : array(DynamicArray<T>(other.array)){}


template <class T>
T SequenceArray<T>::GetFirst() const {
     return array.Get(0);
}

template <class T>
T SequenceArray<T>::GetLast() const {
    return array.Get(array.GetSize() - 1);
}

template <class T>
T SequenceArray<T>::Get(size_t index) const {
    return array.Get(index);
}

template <class T>
size_t SequenceArray<T>::GetLength() const {
    return array.GetSize();
}

template <class T>
SequenceArray<T>* SequenceArray<T>::appendInternal(T value){
    size_t size = array.GetSize();
    array.Resize(size + 1);
    array.Set(size,value);
    return this;
}

template <class T>
SequenceArray<T>* SequenceArray<T>::prependInternal(T value){
    size_t size = array.GetSize();
    array.Resize(size + 1);
    for (size_t i = size; i > 0; --i){
        array.Set(i, array.Get(i - 1));
    }
    array.Set(0,value);
    return this;
}

template <class T>
SequenceArray<T>* SequenceArray<T>::insertAtInternal(T item, size_t index){
    size_t size = array.GetSize();
    if (index > size) {
        throw IndexOutOfRangeException(index, size);
    }
    array.Resize(size + 1);
    for (size_t i = size; i > index; --i){
        array.Set(i, array.Get(i - 1));
    }
    array.Set(index, item);
    return this;
}

template <class T>
Sequence<T>* SequenceArray<T>::Concat(Sequence<T>* list) const{
    SequenceArray<T>* res = Construct();
    if (seq == nullptr){
        throw NullPointerException;
    }
    for (size_t){
        res->appendInternal(this->Get(i));
    }
    for (size_t i = 0; i < list->GetLength(); ++i){
        res->appendInternal(list->Get(i));
    }
    return res;
}

template <class T>
Sequence<T>* SequenceArray<T>::append(T item){
    return Instance()->appendInternal(item);
}

template <class T>
Sequence<T>* SequenceArray<T>::prepend(T item){
    return Instance()->prependInternal(item);
}

template <class T>
Sequence<T>* SequenceArray<T>::insertAt(T item, size_t index){
    return Instance()->insertAtInternal(item, index);
}

template <class T>
IEnumerator<T>* SequenceArray<T>::GetEnumerator() const{
    return array.GetEnumerator();
}

template <class T>
ArrayIterator<T> SequenceArray<T>::begin() const {
    return array.begin();
}

template <class T>
ArrayIterator<T> SequenceArray<T>::end() const {
    return array.end();
}


template <class T>
Sequence<T>* SequenceArray<T>::GetSubsequence(size_t startIndex, size_t endIndex) const {
    SequenceArray<T>* res = Construct();
    if (startIndex > endIndex || endIndex >= size){
        throw IndexOutOfRangeException(startIndex, endIndex);
    }

    for (size_t i = startIndex; i <= endIndex; ++i) {
        res->appendInternal(this->Get(i));
    }
    
    return res;
}
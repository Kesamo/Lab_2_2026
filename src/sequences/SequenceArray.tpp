#include <cstddef>
#include <stdexcept> 
#include "SequenceArray.hpp"

template <class T>
SequenceArray<T>::SequenceArray() : array(new DynamicArray<T>()) {}

template <class T>
SequenceArray<T>::SequenceArray(T* item, int count) : array(new DynamicArray<T>(item, count)) {}

template <class T>
SequenceArray<T>::SequenceArray(const SequenceArray<T>& other) : array(new DynamicArray<t>(*other.array)){}

template <class T>
SequenceArray<T>::~SequenceArray() { delete array; }

template <class T>
T SequenceArray<T>::GetFirst() const {
     return array->Get(0);
}

template <class T>
T SequenceArray<T>::GetLast() const {
    return array->Get(array->GetSize() - 1);
}

template <class T>
T SequenceArray<T>::Get(int index) const {
    return array->Get(index);
}

template <class T>
int SequenceArray<T>::GetLength() const {
    return array->GetSize();
}

template <class T>
Sequence<T>* SequenceArray<T>::append(T value) {
    int size = array->GetSize();
    array->Resize(size + 1);
    array->Set(size,value);
    return this;
}

template <class T>
Sequence<T>* SequenceArray<T>::prepend(T value) {
    int size = array->GetSize();
    array->Resize(size + 1);
    for (int i = size, i > 0, --i){
        array->Set(i, array->Get(i - 1));
    }
    array->Set(0,value);
    return this;
}

template <class T>
Sequence<T>* SequenceArray<T>::insertAt(T item, int index){
    int size = array->GetSize();
    array->Resize(size + 1);
    for (int i = size, i > index; --i){
        array->Set(i, array->Get(i - 1));
    }
    array->Set(index, item);
    return this;
}

template <class T>
Sequence<T>* SequenceArray<T>::Concat(Sequence<T>* list){
    int len1 = GetLength();
    int len2 = list->GetLength();
    T* buffer = new T[len1 + len2];
    for (int i = 0; i < len1; ++i){
        buffer[i] = array->Get(i);
    }
    for (int i = 0; i < len2; ++i){
        buffer[i + len1] = list->Get(i);
    }

    return new SequenceArray<T>(buffer, len1 + len2);
}
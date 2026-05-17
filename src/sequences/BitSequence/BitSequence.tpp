#include <cstddef>
#include <stdexcept> 
#include "BitSequence.hpp"

template <std::integral T>
BitSequence<T>::BitSequence() : array(DynamicArray<Bit<T>>(0)) {}

template <std::integral T>
BitSequence<T>::BitSequence(Bit<T>* item, size_t count) : array(DynamicArray<Bit<T>>(item, count)) {}

template <std::integral T>
BitSequence<T>::BitSequence(const BitSequence<T>& other) : array(DynamicArray<Bit<T>>(other.array)) {}


template <std::integral T>
BitSequence<T>* BitSequence<T>::appendInternal(Bit<T> value) {
    size_t size = array.GetSize();
    array.Resize(size + 1);
    array.Set(size, value);
    return this;
}

template <std::integral T>
BitSequence<T>* BitSequence<T>::prependInternal(Bit<T> value) {
    size_t size = array.GetSize();
    array.Resize(size + 1);
    for (size_t i = size; i > 0; --i){
        array.Set(i, array.Get(i - 1));
    }
    array.Set(0, value);
    return this;
}

template <std::integral T>
BitSequence<T>* BitSequence<T>::insertAtInternal(Bit<T> item, size_t index) {
    size_t size = array.GetSize();
    if (index > size) {
        throw IndexOutOfRangeException(index, size);
    }
    array.Resize(size + 1);
    for( size_t i = size ; i > index; --i){
        array.Set(i,Get(i - 1));
    }
    array.Set(index, item);
    return this;
}

template <std::integral T>
Sequence<Bit<T>>* BitSequence<T>::GetSubsequence(size_t startIndex, size_t endIndex) const {
    BitSequence<T>* res = Construct();
    size_t size = array.GetSize();
    if (startIndex > endIndex || endIndex >= size){
        throw InvalidRangeException(startIndex, endIndex);
    }

    for (size_t i = startIndex; i <= endIndex; ++i) {
        res->appendInternal(this->Get(i));
    }
    
    return res;
}

template <std::integral T>
auto BitSequence<T>::Concat(Sequence<Bit<T>> * list) const -> Sequence<Bit<T>>* {
    BitSequence<T>* res = Construct();
    if (list == nullptr){
        throw NullPointerException();
    }
    for (auto item : *this) {
        res->appendInternal(item);
    }
    for( size_t i = 0; i < list->GetLength(); ++i){
        res->appendInternal(list->Get(i));
    }
    return res;
}

template <std::integral T>
auto BitSequence<T>::append(Bit<T> value) -> Sequence<Bit<T>>* {
    return Instance()->appendInternal(value);
}

template <std::integral T>
Sequence<Bit<T>>* BitSequence<T>::prepend(Bit<T> value) {
    return Instance()->prependInternal(value);
}

template <std::integral T>
Sequence<Bit<T>>* BitSequence<T>::insertAt(Bit<T> value, size_t index) {
    return Instance()->insertAtInternal(value, index);
}

template <std::integral T>
Bit<T> BitSequence<T>::GetFirst() const {
    return array.Get(0);
}

template <std::integral T>
Bit<T> BitSequence<T>::Get(size_t index) const {
    return array.Get(index);
}

template <std::integral T>
Bit<T> BitSequence<T>::GetLast() const {
    size_t size = array.GetSize();
    return array.Get(size - 1);
}

template <std::integral T>
size_t BitSequence<T>::GetLength() const {
    return array.GetSize();
}

template <std::integral T>
auto BitSequence<T>::operator[](size_t idx) {
    return array[idx / (sizeof(T) * 8)][idx % (sizeof(T) * 8)];
}

template <std::integral T>
auto BitSequence<T>::operator[](size_t idx) const {
    return array[idx / (sizeof(T) * 8)][idx % (sizeof(T) * 8)];
}

// template <std::integral T>
// auto BitSequence<T>::operator[](size_t idx) {
//     return array[idx / (sizeof(T) * 8)][idx % (sizeof(T) * 8)];
// }

// template <std::integral T>
// auto BitSequence<T>::operator[](size_t idx) const {
//     return array[idx / (sizeof(T) * 8)][idx % (sizeof(T) * 8)];
// }

template <std::integral T>
IEnumerator<Bit<T>>* BitSequence<T>::GetEnumerator() const{
    return array.GetEnumerator();
}

template <std::integral T>
ArrayIterator<Bit<T>> BitSequence<T>::begin() const {
    return array.begin();
}

template <std::integral T>
ArrayIterator<Bit<T>> BitSequence<T>::end() const {
    return array.end();
}
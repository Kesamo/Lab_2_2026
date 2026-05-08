#include <cstddef>
#include <stdexcept> 
#include "BitSequence.hpp"

template <std::integral T>
BitSequence<T>::BitSequence() : array(DynamicArray<T>(0)) {}

template <std::integral T>
BitSequence<T>::BitSequence(T* item, size_t count) : array(DynamicArray<T>(item, count)) {}

template <std::integral T>
BitSequence<T>::BitSequence(const BitSequence<T>& other) : array(DynamicArray<T>(other.array)) {}


template <std::integral T>
BitSequence<T>* BitSequence<T>::appendInternal(T value) {
    size_t size = array.GetSize();
    array.Resize(size + 1);
    array.Set(size, value);
    return this;
}

template <std::integral T>
BitSequence<T>* BitSequence<T>::prependInternal(T value) {
    size_t size = array.GetSize();
    array.Resize(size + 1);
    for (size_t i = size; i > 0; --i){
        array.Set(i, array.Get(i - 1));
    }
    array.Set(0, value);
    return this;
}

template <std::integral T>
BitSequence<T>* BitSequence<T>::insertAtInternal(T item, int index) {
    size_t size = array.GetSize();
    array.Resize(size + 1);
    for( size_t i = size ; i > index; --i){
        array.Set(i,Get(i - 1));
    }
    array.Set(index, item);
    return this;
}

template <std::integral T>
Sequence<T>* BitSequence<T>::GetSubsequence(int startIndex, int endIndex) const {

    Sequence<T>* res = Construct();
    for (int i = startIndex; i <= endIndex; ++i) {
        res->append(Get(i));
    }
    return res;
}

template <std::integral T>
auto BitSequence<T>::Concat(Sequence<T> * list) const -> Sequence<T>* {
    BitSequence<T>* res = Construct();
    for( size_t i = 0; i < this->GetLength(); ++i){
        res->append(this->Get(i));
    }
    for( size_t i = 0; i < list->GetLength(); ++i){
        res->append(list->Get(i));
    }
    return res;
}

template <std::integral T>
auto BitSequence<T>::append(T value) -> Sequence<T>* {
    return Instance()->appendInternal(value);
}

template <std::integral T>
Sequence<T>* BitSequence<T>::prepend(T value) {
    return Instance()->prependInternal(value);
}

template <std::integral T>
Sequence<T>* BitSequence<T>::insertAt(T value, int index) {
    return Instance()->insertAtInternal(value, index);
}

template <std::integral T>
auto BitSequence<T>::GetFirst() const {
    return array.Get(0);
}

template <std::integral T>
T BitSequence<T>::Get(int index) const {
    return array.Get(index);
}

template <std::integral T>
T BitSequence<T>::GetLast() const {
    size_t size = array.GetSize();
    return array.Get(size - 1);
}

template <std::integral T>
size_t BitSequence<T>::GetLength() const {
    return array.GetSize();
}

template <std::integral T>
auto BitSequence<T>::operator[](size_t idx) -> Bit<T>{
    // [0000 0010][0011 0010][0000 0000]
// 10/8 = 1
// 10%8 = 2


    return Bit<T>( Bit<T>(array[idx / (sizeof(T) * 8)])[idx % (sizeof(T) * 8)] );
}

template <std::integral T>
IEnumerator<T>* BitSequence<T>::GetEnumerator() const{
    return array.GetEnumerator();
}

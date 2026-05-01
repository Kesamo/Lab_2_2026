#include <cstddef>
#include <stdexcept>
#include "SequenceArray.hpp"

template <class T>
SequenceArray<T>::SequenceArray() : array(new DynamicArray<T>()) {}

template <class T>
SequenceArray<T>::SequenceArray(T* item, int count) : array(new DynamicArray<T>(item, count)) {}

template <class T>
SequenceArray<T>::SequenceArray(const SequenceArray<T>& other) : array(new DynamicArray<T>(*other.array)){}

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
SequenceArray<T>* SequenceArray<T>::appendInternal(T value){
    int size = array->GetSize();
    array->Resize(size + 1);
    array->Set(size,value);
    return this;
}

template <class T>
SequenceArray<T>* SequenceArray<T>::prependInternal(T value){
    int size = array->GetSize();
    array->Resize(size + 1);
    for (int i = size; i > 0; --i){
        array->Set(i, array->Get(i - 1));
    }
    array->Set(0,value);
    return this;
}

template <class T>
SequenceArray<T>* SequenceArray<T>::insertAtInternal(T item, int index){
    int size = array->GetSize();
    array->Resize(size + 1);
    for (int i = size; i > index; --i){
        array->Set(i, array->Get(i - 1));
    }
    array->Set(index, item);
    return this;
}

template <class T>
Sequence<T>* SequenceArray<T>::Concat(Sequence<T>* list) const{
    SequenceArray<T>* res = Construct();
    for (int i = 0; i < this->GetLength(); ++i){
        res->append(this->Get(i));
    }
    for (int i = 0; i < list->GetLength(); ++i){
        res->append(list->Get(i));
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
Sequence<T>* SequenceArray<T>::insertAt(T item, int index){
    return Instance()->insertAtInternal(item, index);
}

template <class T>
IEnumerator<T>* SequenceArray<T>::GetEnumerator() const{
    return new EnumeratorSequence<T>(this);
}

template <class T>
Sequence<T>* SequenceArray<T>::GetSubsequence(int startIndex, int endIndex) const {
    SequenceArray<T>* res = Construct();

    for (int i = startIndex; i <= endIndex; ++i) {
        res->append(res->Get(i));
    }
    
    return res;
}
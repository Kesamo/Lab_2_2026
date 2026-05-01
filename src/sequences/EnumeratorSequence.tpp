#include "EnumeratorSequence.hpp"

template <class T>
EnumeratorSequence<T>::EnumeratorSequence(const Sequence<T>* seq) : sequence(seq), index(-1), flag(false) {}

template <class T>
bool EnumeratorSequence<T>::MoveNext(){
    ++index;
    flag = (index < sequence->GetLength()); 
    return flag;
}

template <class T>
T EnumeratorSequence<T>::Current() const{
    return sequence->Get(index);
}

template <class T>
void EnumeratorSequence<T>::Reset(){
    index = -1;
    flag = false;
}
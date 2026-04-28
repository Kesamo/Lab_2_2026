#pragma once
#include <functional>
#include <stdexcept>

template <class T>
class Sequence{
    public:
        virtual ~Sequence() = default;

        virtual T GetFirst() const = 0;
        virtual T GetLast() const = 0;
        virtual T Get(int index) const = 0;
        virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0; 
        virtual int GetLength() const = 0;

        virtual Sequence<T>* append(T item) = 0; 
        virtual Sequence<T>* prepend(T item) = 0; 
        virtual Sequence<T>* insertAt(T item, int index) = 0;
        virtual Sequence<T>* Concat(Sequence <T> *list) const = 0;

        // virtual Sequence<T>* Map(T2 (*)(T)) const = 0; 
        // virtual Sequence<T>* Where(bool (*)(T)) const = 0;
        // virtual Sequence<T>* Reduce(T2 (*)(T2,T)) const = 0;

};
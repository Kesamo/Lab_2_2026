#pragma once
#include <functional>
#include <stdexcept>
#include "../utils/IEnumerator.hpp"

template <class T>
class Sequence{
    public:
        virtual ~Sequence() = default;

        virtual T GetFirst() const = 0;
        virtual T GetLast() const = 0;
        virtual T Get(size_t index) const = 0;
        virtual Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const = 0; 
        virtual size_t GetLength() const = 0;

        virtual Sequence<T>* append(T item) = 0; 
        virtual Sequence<T>* prepend(T item) = 0; 
        virtual Sequence<T>* insertAt(T item, size_t index) = 0;
        virtual Sequence<T>* Concat(Sequence <T> *list) const = 0;

        virtual IEnumerator<T>* GetEnumerator() const= 0;

        virtual Sequence<T>* Map(T (*func)(T)) = 0; 
        virtual Sequence<T>* Where(bool (*predicate)(T)) = 0;
        virtual Sequence<T>* Reduce(T (*func)(T,T), T starter) = 0;
};
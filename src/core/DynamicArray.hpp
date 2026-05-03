#pragma once
#include <stdexcept>
#include <cstddef>
#include "ArrayIterator.hpp"

template<class T>
class DynamicArray : public IEnumerable<T>{
    private:
        int array_size = 0;
        T* data = nullptr;

    public:
        DynamicArray();
        DynamicArray(T* items, int count);
        DynamicArray(int size);
        DynamicArray(const DynamicArray<T> & dynamicArray);

        ~DynamicArray();

        IEnumerator<T>* GetEnumerator() const override;

        ArrayIterator<T> begin();
        ArrayIterator<T> end();

        ArrayIterator<T> begin() const;
        ArrayIterator<T> end() const;

        T Get(int index) const;
        int GetSize() const;
        void Set(int index, T value);
        void Resize(int newSize);

        T& operator [](int index);
        const T& operator[](int index) const;
};

#include "DynamicArray.tpp"
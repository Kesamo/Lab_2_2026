#pragma once
#include <stdexcept>
#include <cstddef>

template<class T>
class DynamicArray{
    private:
        int array_size;
        T* data;

    public:
        DynamicArray();
        DynamicArray(T* items, int count);
        DynamicArray(int size);
        DynamicArray(const DynamicArray<T> & dynamicArray);

        ~DynamicArray();

        T Get(int index);
        int GetSize();
        void Set(int index, T value);
        void Resize(int newSize);
};

#include "DynamicArray.tpp"
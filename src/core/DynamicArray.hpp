#pragma once
#include <stdexcept>
#include <cstddef>

template<class T>
class DynamicArray{
    private:
        int array_size = 0;
        T* data = nullptr;

    public:
        DynamicArray();
        DynamicArray(T* items, int count);
        DynamicArray(int size);
        DynamicArray(const DynamicArray<T> & dynamicArray);

        ~DynamicArray();

        T Get(int index) const;
        int GetSize() const;
        void Set(int index, T value);
        void Resize(int newSize);

        T& operator [](int index);
        const T& operator[](int index) const;
};

#include "DynamicArray.tpp"
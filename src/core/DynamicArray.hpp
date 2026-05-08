#pragma once
#include <stdexcept>
#include <cstddef>
#include "ArrayIterator.hpp"
#include "Exceptions.hpp"

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
        size_t GetSize() const;
        void Set(int index, T value);
        void Resize(int newSize);

        T& operator [](size_t index);
        const T& operator[](size_t index) const;
};

#include "DynamicArray.tpp"
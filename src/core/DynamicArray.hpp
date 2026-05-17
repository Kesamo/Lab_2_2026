#pragma once
#include <stdexcept>
#include <cstddef>
#include "ArrayIterator.hpp"
#include "Exceptions.hpp"

template<class T>
class DynamicArray : public IEnumerable<T>{
    private:
        size_t array_size = 0;
        T* data = nullptr;

    public:
        DynamicArray();
        DynamicArray(T* items, size_t count);
        DynamicArray(size_t size);
        DynamicArray(const DynamicArray<T> & dynamicArray);

        ~DynamicArray();

        IEnumerator<T>* GetEnumerator() const override;

        ArrayIterator<T> begin();
        ArrayIterator<T> end();

        ArrayIterator<T> begin() const;
        ArrayIterator<T> end() const;

        T Get(size_t index) const;
        size_t GetSize() const;
        void Set(size_t index, T value);
        void Resize(size_t newSize);

        T& operator [](size_t index);
        const T& operator[](size_t index) const;
};

#include "DynamicArray.tpp"
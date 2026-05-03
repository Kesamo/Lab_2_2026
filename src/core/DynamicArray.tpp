#include <cstddef>
#include <stdexcept> 
#include "DynamicArray.hpp"


template <class T> 
DynamicArray<T>::DynamicArray() : array_size(0), data(nullptr) {}

template <class T>
DynamicArray<T>::DynamicArray(T* items, int count) : array_size(count) {
    
    if (count == 0) {
        data = nullptr;
        array_size = 0;
        return;
    }
    
    data = new T[count];
    for (int i = 0; i < count; i++) {
        data[i] = items[i];
    }
}

template <class T>
DynamicArray<T>::DynamicArray(int size) : array_size(size){
    array_size = size;

    if (array_size == 0) {
        data = nullptr;
        return;
    }

    data = new T[size]();
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray) : array_size(dynamicArray.array_size){
    if (array_size == 0){
        data = nullptr;
        return;
    }

    data = new T[array_size];
    for (int i = 0; i < array_size; ++i) {
        data[i] = dynamicArray.data[i];
    }
}

template <class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <class T>
T DynamicArray<T>::Get(int index) const {
    if (index < 0 || index >= array_size){
        THROW(IndexOutOfRangeException,("Индекс " + std::to_string(index) + " выходит за границы массива : " + std::to_string(array_size)).c_str());
    }
    return data[index];
}

template <class T>
int DynamicArray<T>::GetSize() const {
    return array_size;
}

template <class T>
void DynamicArray<T>::Set(int index, T value){
    if (index < 0 || index >= array_size){
        THROW(IndexOutOfRangeException,("Индекс " + std::to_string(index) + " выходит за границы массива : " + std::to_string(array_size)).c_str());
    }
    data[index] = value;
}

template <class T>
void DynamicArray<T>::Resize(int newSize) {
    if (newSize < 0) {
        THROW(InvalidArgumentException, "Нельзя изменить размер на отрицательное значение");
    }
    T* newData = new T[newSize];
    int count = (newSize < array_size) ? newSize : array_size;
    for (int i = 0; i < count; ++i){
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    array_size = newSize;
}

template <class T>
T& DynamicArray<T>::operator[](int index) {
    return data[index];
}

template <class T>
const T& DynamicArray<T>::operator[](int index) const {
        return data[index];
}

template <class T>
IEnumerator<T>* DynamicArray<T>::GetEnumerator() const {
    return new ArrayIterator<T>(data, array_size, -1);
}

template <class T>
ArrayIterator<T> DynamicArray<T>::begin() {
    return ArrayIterator<T>(data, array_size, 0);
}

template <class T>
ArrayIterator<T> DynamicArray<T>::begin() const {
    return ArrayIterator<T>(data, array_size, 0);
}

template <class T>
ArrayIterator<T> DynamicArray<T>::end() {
    return ArrayIterator<T>(data, array_size, array_size);
}


template <class T>
ArrayIterator<T> DynamicArray<T>::end() const {
    return ArrayIterator<T>(data, array_size, array_size);
}
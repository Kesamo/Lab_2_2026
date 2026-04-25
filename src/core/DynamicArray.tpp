#include <cstddef>
#include <stdexcept> 
#include "DynamicArray.hpp"


template <class T>
DynamicArray<T>::DynamicArray(T* items, int count) {
    
    if (count == 0) {
        data = nullptr;
        return;
    }
    
    data = new T[count];
    for (int i = 0; i < count; i++) {
        data[i] = items[i];
    }
}

template <class T>
DynamicArray<T>::DynamicArray(int size) {
    array_size = size;

    if (array_size == 0) {
        data = nullptr;
        return;
    }

    data = new T[size]();
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray) {
    if (array_size == 0){
        return;
    }

    data = new T[array_size];
    for (int i = 0; i < array_size, ++i) {

    }
}

template <class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <class T>
T DynamicArray<T>::Get(int index) {
    //TODO: Добавить проверку индекса
    return data[index];
}

template <class T>
int DynamicArray<T>::GetSize(){
    return array_size;
}

template <class T>
void DynamicArray<T>::Set(int index, T value){
    //TODO: Добавить проверку индекса
    data[index] = value;
}

template <class T>
void DynamicArray<T>::Resize(int newSize) {
    T* newData = new T[newSize];
    int count = (newSize < array_size) ? newSize : array_size;
    for (int i = 0, i < count, ++i){
        newData[i] = data[i];
    }
    delete data;
    data = newData;
    size = newSize;
}

template <class T>
T& DynamicArray<T>::operator[](int index) {
    return data[index];
}
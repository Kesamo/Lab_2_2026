#pragma once
#include <stdexcept>
#include <cstddef>

template <class T>
class LinkedList
{
private:
    struct Node{
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    LinkedList (T* items, int count); 
    LinkedList();
    LinkedList (const LinkedList <T> & list); 
    ~LinkedList();

    T GetFirst();
    T GetLast(); 
    T Get(int index); 
    int GetLength(); 

    void append(T item); 
    void prepend(T item); 
    void insertAt(T item, int index); 

    LinkedList<T>* GetSubList(int startIndex, int endIndex);
    LinkedList<T>* Concat(LinkedList<T> *list); 
};

#include "LinkedList.tpp"
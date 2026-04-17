#pragma once
#include <stdexcept>
#include <cstddef>

template <class T>
class LinkedList
{
private:
    struct Node{
        T data;
        struct Node* next;
        struct Node* prev;
    };
public:
    LinkedList (T* items, int count); 
    LinkedList();
    LinkedList (LinkedList <T> & list const); 

    ~LinkedList();

    T GetFirst();
    T GetLast(); 
    T Get(int index);
    LinkedList<T>* GetSubList(int startIndex, int endIndex); 
    int GetLength(); 

    void Append(T item); 
    void Prepend(T item); 
    void InsertAt(T item, int index); 
    LinkedList<T>* Concat(LinkedList<T> *list); 
};



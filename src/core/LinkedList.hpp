#pragma once
#include <stdexcept>
#include <cstddef>
#include "ListIterator.hpp"
#include "IEnumerator.hpp"

template <class T>
class LinkedList : public IEnumerable<T>{
    friend class ListIterator<T>;
private:
    struct Node{
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
public:
    LinkedList (T* items, int count); 
    LinkedList();
    LinkedList (const LinkedList <T>& list); 
    ~LinkedList();

    IEnumerator<T>* GetEnumerator() const override;

    ListIterator<T> begin();
    ListIterator<T> end();

    ListIterator<T> begin() const;
    ListIterator<T> end() const;

    Node* GetNode(int index);
    T GetFirst();
    T GetLast(); 
    T Get(int index); 
    size_t GetLength(); 

    void append(T item); 
    void prepend(T item); 
    void insertAt(T item, int index); 

    LinkedList<T>* GetSubList(int startIndex, int endIndex);
    LinkedList<T>* Concat(LinkedList<T> *list); 
};

#include "LinkedList.tpp"
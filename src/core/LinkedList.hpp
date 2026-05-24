#pragma once
#include <stdexcept>
#include <cstddef>
#include "ListIterator.hpp"
#include "IEnumerator.hpp"
#include "Exceptions.hpp"

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
    LinkedList (T* items, size_t count); 
    LinkedList();
    LinkedList (const LinkedList <T>& list); 
    ~LinkedList();

    IEnumerator<T>* GetEnumerator() const override;

    ListIterator<T> begin();
    ListIterator<T> end();

    ListIterator<T> begin() const;
    ListIterator<T> end() const;

    Node* GetNode(size_t) const;
    T GetFirst() const;
    T GetLast() const; 
    T Get(size_t index) const; 
    size_t GetLength() const; 

    void RemoveLast();
    void RemoveFirst();

    void append(T item); 
    void prepend(T item); 
    void insertAt(T item, size_t index); 

    LinkedList<T>* GetSubList(size_t startIndex, size_t endIndex) const;
    LinkedList<T>* Concat(LinkedList<T> *list) const; 
};

#include "LinkedList.tpp"
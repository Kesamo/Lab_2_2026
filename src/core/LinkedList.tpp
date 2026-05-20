#include <cstddef>
#include <stdexcept> 
#include "LinkedList.hpp"

template <class T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tail = nullptr;
}

template <class T>
LinkedList<T>::LinkedList(T* items, size_t count) : LinkedList(){
    if(items == nullptr){
        throw NullPointerException();
    }
    for(size_t i = 0; i < count; ++i){
        append(items[i]);
    }
}

template <class T>
LinkedList<T>::LinkedList (const LinkedList <T> & list) : LinkedList(){
    Node* current = list.head;
    while(current != nullptr){
        append(current->data);
        current = current->next;
    }
}

template <class T>
LinkedList<T>::~LinkedList(){
    Node* current = head;
    while(current != nullptr){
        Node* next = current->next;
        delete current;
        current = next;
    }
}

template <class T>
T LinkedList<T>::GetFirst() const{
    size_t size = GetLength();
    
    if (size == 0 || head == nullptr) {
        throw IndexOutOfRangeException();
    }
    return head->data;
}

template <class T>
T LinkedList<T>::GetLast() const{
    if (tail == nullptr) {
        throw NullPointerException();
    }
    return tail->data;
}

template <class T>
size_t LinkedList<T>::GetLength() const{
    size_t count = 0;
    Node* current = head;
    while (current != nullptr) {
        ++count;
        current = current->next;
    }
    return count;
}

template <class T>
T LinkedList<T>::Get(size_t index) const{
    size_t size = GetLength();
    if (index >= size) {
        throw IndexOutOfRangeException(index, size);
    }

    return GetNode(index)->data;
}

template <class T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(size_t index) const{
    size_t size = GetLength();   
    if (index >= size) {
        throw IndexOutOfRangeException(index, size);
    }

    Node* current;
    if (index < size / 2) {
        current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
    } else {
        current = tail;
        for (size_t i = size - 1; i > index; --i){
            current = current->prev;
        }
    }
    return current;
}

template <class T>
void LinkedList<T>::append(T item){
    Node* new_node = new Node(item);
    if(head == nullptr){
        head = new_node;
        tail = new_node;
    }
    else{
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
}

template <class T>
void LinkedList<T>::prepend(T item){
    Node* new_node = new Node(item);
    if(head == nullptr){
        head = new_node;
        tail = new_node;
    }
    else{
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
}

template <class T>
void LinkedList<T>::insertAt(T item, size_t index){
    size_t size = GetLength();

    if (index > size) {
        throw IndexOutOfRangeException(index, size);
    }

    if(index == 0){
        prepend(item);
        return;
    }

    if(index == size){
        append(item);
        return;
    }

    Node* new_node = new Node(item);
    Node* current = GetNode(index);

    new_node->prev = current->prev;
    new_node->next = current;
    current->prev->next = new_node;
    current->prev = new_node;
}

template <class T>
LinkedList<T>* LinkedList<T>::GetSubList(size_t startIndex, size_t endIndex) const{
    size_t size = GetLength();
    if (startIndex > endIndex || endIndex >= size){
        throw InvalidRangeException(startIndex, endIndex);
    }
    LinkedList<T>* SubList = new LinkedList<T>();
    Node* current = GetNode(startIndex);

    for(size_t i = startIndex; i <= endIndex; ++i){
        SubList->append(current->data);
        current = current->next;
    }

    return SubList;
}

template <class T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T> *list) const{
    if (list == nullptr){
        throw EmptyListException();
    }
    LinkedList<T>* new_list = new LinkedList<T>(*this);
    for(auto item : *list){
        new_list->append(item);
    }
    return new_list;
}

template <class T>
IEnumerator<T>* LinkedList<T>::GetEnumerator() const{
    return new ListIterator<T>(head);
}

template <class T>
ListIterator<T> LinkedList<T>::begin(){
    return ListIterator<T>(head);
}

template <class T>
ListIterator<T> LinkedList<T>::end(){
    return ListIterator<T>(nullptr);
}

template <class T>
ListIterator<T> LinkedList<T>::begin() const{
    return ListIterator<T>(head);
}

template <class T>
ListIterator<T> LinkedList<T>::end() const{
    return ListIterator<T>(nullptr);
}

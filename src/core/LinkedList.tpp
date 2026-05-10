#include <cstddef>
#include <stdexcept> 
#include "LinkedList.hpp"

template <class T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tail = nullptr;
}

template <class T>
LinkedList<T>::LinkedList(T* items, int count) : LinkedList(){
    //TODO: Проверка размера
    for(int i = 0; i < count; ++i){
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
        THROW(IndexOutOfRangeException,("GetFirst: список пуст"));
    }
    return head->data;
}

template <class T>
T LinkedList<T>::GetLast() const{
    size_t size = GetLength();

    if (size == 0 || tail == nullptr) {
        THROW(IndexOutOfRangeException,("GetLast: список пуст"));
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
T LinkedList<T>::Get(int index) const{
    size_t size = GetLength();
    
    if (index < 0 || index >= size) {
        THROW(IndexOutOfRangeException, ("Get: индекс вне диапазона"));
    }

    return GetNode(index)->data;
}

template <class T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(int index) const{
    size_t size = GetLength();
    
    if (index < 0 || index > size) {
        THROW(IndexOutOfRangeException, ("GetNode: индекс вне диапазона"));
    }

    Node* current;
    if (index < size / 2) {
        current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
    } else {
        current = tail;
        for (int i = size - 1; i > index; --i){
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
void LinkedList<T>::insertAt(T item, int index){
    size_t size = GetLength();

    if (index < 0 || index > size) {
        THROW(IndexOutOfRangeException, ("Позиция вставки " + std::to_string(index) + " недопустима. Допустимый диапазон: " + std::to_string(size)).c_str());
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
LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex) const{
    //TODO: Проверка
    LinkedList<T>* SubList = new LinkedList<T>();
    Node* current = GetNode(startIndex);

    for(int i = startIndex; i <= endIndex; ++i){
        SubList->append(current->data);
        current = current->next;
    }

    return SubList;
}

template <class T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T> *list) const{
    //TODO: Проверка на nullptr
    LinkedList<T>* new_list = new LinkedList<T>(*this);
    Node* current = list->head;

    while(current != nullptr){
        new_list->append(current->data);
        current = current->next;
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

#pragma once
#include "IEnumerator.hpp"
#include "LinkedList.hpp"
#include <Exceptions.hpp>

template <class T> class LinkedList;

template <class T>
class ListIterator : public IEnumerator<T> {
private:
    typename LinkedList<T>::Node* current_;
    typename LinkedList<T>::Node* head_;
public:
    explicit ListIterator(typename LinkedList<T>::Node* head) : current_(head), head_(head){}

    T& Current() const override {
        if(current_ == nullptr){
            return throw IteratorPointerException;
        }
        return current_->data;
    }

    bool MoveNext() override {
        if(current_){
            current_ = current_->next;
        }
        return current_ != nullptr;
    }

    void Reset() override {
        current_ = head_;
    }

    T operator*() const{
        return Current();
    }

    ListIterator& operator++(){
        MoveNext();
        return *this;
    }

    bool operator!=(const ListIterator& other) const {
        return current_ != other.current_;
    }

    bool operator==(const ListIterator& other) const {
        return current_ == other.current_;
    }
};
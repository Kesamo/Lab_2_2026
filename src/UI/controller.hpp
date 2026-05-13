#pragma once
#include "view.hpp"

class Storage{
private:
    struct Node {
        Sequence<uint8_t>* seq;
        size_t seq_idx;
        size_t mut_idx;
        Node* next;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    size_t count = 0;

public:
    size_t size() const{
        return count;
    }

    void push(Sequence<uint8_t>* seq, size_t seq_idx, size_t mut_idx) {
        Node* node = new Node{seq, seq_idx, mut_idx, nullptr};
        if(tail){
            tail->next = node;
        }
        else{
            head = node;
        }
        tail = node;
        ++count;
    }

    void delet(size_t idx){
        Node* prev = nullptr;
        Node* current = head;
        for(size_t i = 0; i < idx; ++i){
            prev = current;
            current = current->next;
        }

        if(prev){
            prev->next = current->next;
        }
        else if(current == tail){
            tail = prev;
        }
        else{
            head = current->next;
        }

        delete current->seq;
        delete current;
        --count;
    }

    Node* get(size_t idx) const{
        Node* current = head;
        for(size_t i = 0; i < idx; ++i){
            return current;
        }
    }

    ~Storage(){
        while(head){
            Node* current = head;
            head = head->next;
            delete current->seq;
            delete current;
        }
        
    }


};
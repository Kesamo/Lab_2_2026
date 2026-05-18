#pragma once
#include "Sequence.hpp"
#include "MutableSequenceArray.hpp"
#include "ImmutableSequenceArray.hpp"
#include "MutableSequenceList.hpp"
#include "ImmutableSequenceList.hpp"
#include "../BitSequence/ImmutableBitSequence.hpp"
#include "../BitSequence/MutableBitSequence.hpp"

class Storage{
private:
    struct Node {
        Sequence<int>* seq;
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

    void push(Sequence<int>* seq, size_t seq_idx, size_t mut_idx) {
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
        else{
            head = current->next;
        }
        if(current == tail){
            tail = prev;
        }
        delete current->seq;
        delete current;
        --count;
    }

    Node* get(size_t idx) const {
        if (idx > count){
            return nullptr;
        }
        Node* current = head;
        for (size_t i = 0; i < idx; ++i){
            current = current->next;
        }
        return current;
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


class Manager{
private:
    Storage stor;
public:

    void create(size_t seq_idx, size_t mut_idx) {
        Sequence<int>* seq;
        switch (seq_idx) {
            case 0:
                if(mut_idx == 0){
                    seq = new MutableSequenceArray<int>();
                }
                else{
                    seq = new ImmutableSequenceArray<int>();
                }
                break;
            case 1: 
                if(mut_idx == 0){
                    seq = new MutableSequenceList<int>();
                }
                else{
                    seq = new ImmutableSequenceList<int>();
                }
                break;
            default:
                return;
        }

        stor.push(seq, seq_idx, mut_idx);
    }


    void remove(size_t idx){
        stor.delet(idx);
    }

    Sequence<int>* get(size_t idx) {
        auto node = stor.get(idx);
        if(node){
            return node->seq;
        }
        else{
            return nullptr;
        }
    }

    void push(Sequence<int>* seq, size_t seq_idx, size_t mut_idx){
        stor.push(seq, seq_idx, mut_idx);
    }

    size_t size() const{
        return stor.size();
    }

    std::string getName(size_t idx) const {
        auto node = stor.get(idx);
        if (!node){
            return "";
        }
        const char* t[] = { "Array", "List", "Bit" };
        const char* m[] = { "Mutable", "Immutable"};
        return std::format("{}){}_{}",idx + 1, t[node->seq_idx], m[node->mut_idx]);
    }

    std::string PrintNode(size_t idx) {
        auto node = stor.get(idx);
        if (!node) {
            return "[]";
        }
        auto seq = node->seq;
        size_t len = seq->GetLength();
        if (len == 0) {
            return "[]";
        }
        std::string res = "[";
        for (size_t i = 0; i < len - 1; ++i) {
            res += std::to_string(seq->Get(i));
            res += ",";
        }
        res += std::to_string(seq->GetLast());
        res += "]";
        return res;
    }

    void addAppend(size_t current, int value){
        auto node = stor.get(current);
        if(node){
            if(node->mut_idx == 0){
                node->seq->append(value);
            }
            else{
                Sequence<int>* newSeq = node->seq->append(value);
                stor.push(newSeq, node->seq_idx, node->mut_idx);
            }
        }
    }

    void addPrepend(size_t current, int value){
        auto node = stor.get(current);
        if(node){
            if(node->mut_idx == 0){
                node->seq->prepend(value);
            }
            else{
                Sequence<int>* newSeq = node->seq->prepend(value);
                stor.push(newSeq, node->seq_idx, node->mut_idx);
            }
        }
    }

    void addInsertAt(size_t current, int value, size_t idx){
        auto node = stor.get(current);
        if(node){
            if(node->mut_idx == 0){
                node->seq->insertAt(value,idx);
            }
            else{
                Sequence<int>* newSeq = node->seq->insertAt(value,idx);
                stor.push(newSeq, node->seq_idx, node->mut_idx);
            }
        }
    }

    void addConcat(size_t current, size_t idx) {
        auto node_curr = stor.get(current);
        auto node_idx = stor.get(idx);
        if (node_curr && node_idx){
            Sequence<int>* seq1 = node_curr->seq;
            Sequence<int>* seq2 = node_idx->seq;
            Sequence<int>* result = seq1->Concat(seq2);
    
            stor.push(result, node_curr->seq_idx, node_curr->mut_idx);
        }
    }

    void addGetSubsequence(size_t current, size_t start, size_t end){
        auto node = stor.get(current);
        if(node && start <= end && end < node->seq->GetLength()){
            Sequence<int>* sub = node->seq->GetSubsequence(start, end);
            stor.push(sub, node->seq_idx, node->mut_idx);
        }
    }
};

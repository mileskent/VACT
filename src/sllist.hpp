#include <iostream>
#include "word.hpp"

#ifndef SLLIST_HPP
#define SLLIST_HPP

struct Node {
    Word word;
    Node* next;
};

class SLList {
public:
    SLList () {
        head = nullptr;
        tail = nullptr;
    }

    ~SLList () {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
//            std::cout << "Deleted " << current->word.getdefinition() << std::endl;
            delete current;
            current = next;
        }
    }

    Node* get_head () { return head; }

    // You use this by going until 
    // Node->next is the thing you want to delete
    void delete_node (Node* prevNode) {
        Node* todelete;
        todelete = prevNode->next;
        prevNode->next = todelete->next;
        delete todelete;
    }

    bool contains (Word word) {
        Node* current = head;
        while (current != nullptr) {
            if (current->word == word) return true; 
            current = current->next;
        }
        return false;
    }

    void push_back_node (Word word)
    {
        Node* topushback = new Node;
        topushback->word = word;
        topushback->next = nullptr;

        if (head == nullptr) {
            head = topushback;
            tail = topushback;
        }
        else {
            tail->next = topushback;
            tail = tail->next;
        }
    }

    static void showlist (Node* head) {
        if (head == nullptr) {
            std::cout << "Empty Node" << std::endl;
        }
        else {
            std::cout << head->word << std::endl;
            showlist (head->next);
        }
    }

private:
   Node* head;
   Node* tail;
};

#endif


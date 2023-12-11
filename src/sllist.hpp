#include <iostream>

#ifndef SLLIST_HPP
#define SLLIST_HPP

template <typename T>
struct Node {
    T data;
    Node* next;
};

template <typename T>
class SLList {
public:
    SLList() : head(nullptr), tail(nullptr) {}

    ~SLList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    Node<T>* get_head() { return head; }

    void delete_node(Node<T>* prevNode) {
        Node<T>* todelete = prevNode->next;
        prevNode->next = todelete->next;
        delete todelete;
    }

    bool contains(T data) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == data) return true;
            current = current->next;
        }
        return false;
    }

    void push_back_node(T data) {
        Node<T>* topushback = new Node<T>;
        topushback->data = data;
        topushback->next = nullptr;

        if (head == nullptr) {
            head = topushback;
            tail = topushback;
        } else {
            tail->next = topushback;
            tail = tail->next;
        }
    }

    static void showlist(Node<T>* head) {
        if (head == nullptr) {
            std::cout << "Empty Node" << std::endl;
        } else {
            std::cout << head->data << std::endl;
            showlist(head->next);
        }
    }

private:
    Node<T>* head;
    Node<T>* tail;
};

#endif


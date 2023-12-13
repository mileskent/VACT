#include <iostream>
#include <vector>

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

    void orderedinsert(T data) {
        Node<T>* nodetoinsert = new Node<T>;
        nodetoinsert->data = data;
        nodetoinsert->next = nullptr;

        if (head == nullptr) {
            head = nodetoinsert;
            tail = nodetoinsert;
        } 
        else if (data < head->data) {
            nodetoinsert->next = head;
            head = nodetoinsert;
        }
        else {
            Node<T>* current = head;
            Node<T>* prev = nullptr;

            while (current != nullptr && data > current->data) {
                prev = current;
                current = current->next;
            }

            if (prev != nullptr) {
                prev->next = nodetoinsert;
            }
            else {
                head = nodetoinsert;
            }

            nodetoinsert->next = current;

            if (current == nullptr) {
                tail = nodetoinsert;
            }
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

    std::vector<T> tovector() {
        std::vector<T> toreturn;
        Node<T>* current = head;
        while (current != nullptr) {
            toreturn.push_back(current->data);
            current = current->next;
        }
        return toreturn;
    }

private:
    Node<T>* head;
    Node<T>* tail;
};

#endif


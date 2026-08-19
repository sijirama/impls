#include <iostream>
#include <utility>

using namespace std;

struct Node {
    pair<int, int> data;
    Node *next;
};

class MyHashMap {
    Node *head;

  public:
    MyHashMap() { head = nullptr; }

    void put(int key, int value) {
        Node *temp = this->head;
        Node *prev = nullptr;

        while (temp != nullptr) {
            if (temp->data.first == key) {
                temp->data.second = value;
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        Node *node = new Node();
        node->data = {key, value};
        node->next = nullptr;

        if (prev == nullptr) {
            this->head = node;
        } else {
            prev->next = node;
        }
    }

    void print() {
        Node *temp = this->head;
        while (temp != nullptr) {
            cout << "(" << temp->data.first << ":" << temp->data.second << ")";
            temp = temp->next;
        }
        cout << endl;
    }

    int get(int key) {
        Node *temp = this->head;
        while (temp != nullptr) {
            if (temp->data.first == key) {
                return temp->data.second;
            }
            temp = temp->next;
        }
        return -1;
    }

    void remove(int key) {
        Node *temp = this->head;
        Node *prev = nullptr;
        while (temp != nullptr) {
            if (temp->data.first == key) {
                if (prev == nullptr) {
                    this->head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }
};

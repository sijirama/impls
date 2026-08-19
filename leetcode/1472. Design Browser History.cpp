#include <iostream>
#include <string>
using namespace std;

struct Node {
    string data;
    Node *next;
    Node *prev;
    Node(string data) {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

class BrowserHistory {
    Node *head = nullptr;
    Node *top = nullptr;

  public:
    BrowserHistory(string homepage) {
        Node *node = new Node(homepage);
        head = node;
        top = head;
    }
    void visit(string url) {
        Node *node = new Node(url);
        Node *temp = this->head;
        while (temp != this->top) {
            temp = temp->next;
        }
        node->prev = temp;
        temp->next = node;
        this->top = node;
    }

    string back(int steps) {
        Node *temp = top;
        while (temp->prev != nullptr) {
            if (steps == 0) {
                this->top = temp;
                return temp->data;
            };
            steps--;
            temp = temp->prev;
        }
        this->top = temp;
        return temp->data;
    }

    string forward(int steps) {
        Node *temp = top;
        while (temp->next != nullptr) {
            if (steps == 0) {
                this->top = temp;
                return temp->data;
            };
            steps--;
            temp = temp->next;
        }
        this->top = temp;
        return temp->data;
    }
};

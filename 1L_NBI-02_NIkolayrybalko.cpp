#include <iostream>

struct Node {
    double value;
    Node* nextNode;

    Node(double val = 0.0, Node* next = nullptr) : value(val), nextNode(next) {}
};

class SimpleLinkedList {
private:
    Node* firstNode;
    Node* lastNode;

public:
    SimpleLinkedList() : firstNode(nullptr), lastNode(nullptr) {}

    void append(double val) {
        Node* newNode = new Node(val);
        if (!firstNode) {
            firstNode = lastNode = newNode;
        } else {
            lastNode->nextNode = newNode;
            lastNode = newNode;
        }
    }

    void prepend(double val) {
        Node* newNode = new Node(val, firstNode);
        firstNode = newNode;
        if (!lastNode) {
            lastNode = firstNode;
        }
    }

    void deleteFrontOrBack(bool isFront) {
        if (!firstNode) {
            std::cout << "The list is empty\n";
            return;
        }
        if (isFront) {
            Node* temp = firstNode;
            firstNode = firstNode->nextNode;
            if (firstNode == nullptr) lastNode = nullptr;
            delete temp;
        } else {
            if (firstNode == lastNode) {
                delete firstNode;
                firstNode = lastNode = nullptr;
            } else {
                Node* current = firstNode;
                while (current->nextNode != lastNode) {
                    current = current->nextNode;
                }
                delete lastNode;
                lastNode = current;
                lastNode->nextNode = nullptr;
            }
        }
    }

    void show() {
        Node* current = firstNode;
        int position = 0;
        while (current) {
            std::cout << "Node " << position++ << ": " << current->value << std::endl;
            current = current->nextNode;
        }
    }
};

int main() {
    SimpleLinkedList myList;
    myList.append(11);
    myList.prepend(22);
    myList.append(31);
    myList.show();

    std::cout << "\nDeleting from the front...\n\n";
    myList.deleteFrontOrBack(true); // Удаляем первый элемент
    myList.show();

    std::cout << "\nDeleting from the back...\n\n";
    myList.deleteFrontOrBack(false); // Удаляем последний элемент
    myList.show();

    
    return 0;
}

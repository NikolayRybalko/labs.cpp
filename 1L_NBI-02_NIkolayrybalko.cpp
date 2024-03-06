#include <iostream>

struct Element {
    double data;
    Element* next;

    Element(double d = 0.0, Element* n = nullptr) : data(d), next(n) {}
};

class LinkedList {
private:
    Element* head;
    Element* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void addAtEnd(double data) {
        Element* newElement = new Element(data);
        if (!head) {
            head = tail = newElement;
        } else {
            tail->next = newElement;
            tail = newElement;
        }
    }

    void addAtStart(double data) {
        Element* newElement = new Element(data, head);
        head = newElement;
        if (!tail) {
            tail = head;
        }
    }

    void removeElement(bool first) {
        if (!head) {
            std::cout << "List is empty\n";
            return;
        }
        if (first) {
            Element* temp = head;
            head = head->next;
            if (head == nullptr) tail = nullptr;
            delete temp;
        } else {
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            } else {
                Element* current = head;
                while (current->next != tail) {
                    current = current->next;
                }
                delete tail;
                tail = current;
                tail->next = nullptr;
            }
        }
    }

    void display() {
        Element* current = head;
        int index = 0;
        while (current) {
            std::cout << "Element " << index++ << ": " << current->data << std::endl;
            current = current->next;
        }
    }

    // Оставляем методы insertAtIndex, removeAt, findByIndex, findByValue и updateAt без изменений для краткости.
};

int main() {
    LinkedList myList;
    myList.addAtEnd(10);
    myList.addAtStart(20);
    myList.addAtEnd(30);
    myList.display();

    std::cout << "\nRemoving first...\n\n";
    myList.removeElement(true); // Удаляем первый элемент
    myList.display();

    std::cout << "\nRemoving last...\n\n";
    myList.removeElement(false); // Удаляем последний элемент
    myList.display();

    // Пример использования других методов...
    
    return 0;
}

    Element* elementWithValue2 = myList.findByValue(2.0);
    if (elementWithValue2) {
        std::cout << "Element with value 2.0: " << elementWithValue2->data << std::endl;

    }

    myList.updateAt(1, 25);
    myList.display();
    return 0;
}

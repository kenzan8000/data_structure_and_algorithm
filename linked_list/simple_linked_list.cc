#include <iostream>
#include <cstdlib>
#include <ctime>


// Linked List whose item navigation is forward only.


class SimpleNode {
public:
    SimpleNode *next;
    int value;

    SimpleNode(int value);
    ~SimpleNode();
};

SimpleNode::SimpleNode(int value) {
    this->next = NULL;
    this->value = value;
};

SimpleNode::~SimpleNode() {
};


class SimpleLinkedList {
public:
    SimpleNode *head;

    SimpleLinkedList();
    ~SimpleLinkedList();

    /**
     * Adds an element at the last of the list.
     * @param node SimpleNode
     **/
    void insert(SimpleNode *node);

    /**
     * Remove an element
     * @param node SimpleNode
     **/
    void remove(SimpleNode *node);

    /**
     * Displays the complete list.
     **/
    void display();

};

SimpleLinkedList::SimpleLinkedList() {
    this->head = NULL;
};

SimpleLinkedList::~SimpleLinkedList() {
    SimpleNode *current = this->head;
    while (current->next != NULL) {
        SimpleNode *next = current->next;
        delete current;
        current = next;
    }
};

void SimpleLinkedList::insert(SimpleNode *node) {
    if (this->head == NULL) {
        this->head = node;
        return;
    }

    SimpleNode *current = this->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
};

void SimpleLinkedList::remove(SimpleNode *node) {
    SimpleNode *current = this->head;
    // case removing head
    if (current == node) {
        this->head = current->next;
        delete current;
        return;
    }
    // the other case
    while (current->next != NULL) {
        SimpleNode *next = current->next;
        if (next == node) {
            current->next = next->next;
            delete next;
            break;
        }
        current = next;
    }
}

void SimpleLinkedList::display() {
    std::cout << "Simple Linked List: ";
    SimpleNode *current = this->head;
    std::cout << current->value;
    while (current->next != NULL) {
        std::cout << " -> " << current->next->value;
        current = current->next;
    }
    std::cout << std::endl;
};


int main() {
    SimpleLinkedList *linkedList = new SimpleLinkedList();

    std::srand(std::time(0));
    const int count = std::rand() % 5 + 5;

    for (int i = 0; i < count; i++) {
        SimpleNode *node = new SimpleNode(std::rand()%10+1);
        linkedList->insert(node);
    }

    std::cout << "Created: " << std::endl;
    linkedList->display();

    const int index = std::rand() % 5;
    SimpleNode *current = linkedList->head;
    for (int i = 0; i <= index; i++) {
        if (i == index) {
            linkedList->remove(current);
            break;
        }
        current = current->next;
    }
    std::cout << "Removed (index=" << index << "):" << std::endl;
    linkedList->display();

    return 0;
};

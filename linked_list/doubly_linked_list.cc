// Linked List whose items can be navigated forward and backward.


#include <iostream>
#include <cstdlib>
#include <ctime>


class DoublyNode {
public:
    DoublyNode *prev;
    DoublyNode *next;
    int value;

    DoublyNode(int value);
    ~DoublyNode();
};

DoublyNode::DoublyNode(int value) {
    this->prev = NULL;
    this->next = NULL;
    this->value = value;
};

DoublyNode::~DoublyNode() {
};


class DoublyLinkedList {
public:
    DoublyNode *head;
    DoublyNode *foot;

    DoublyLinkedList();
    ~DoublyLinkedList();

    /**
     * Adds an element at the last of the list.
     * @param node DoublyNode
     **/
    void insert(DoublyNode *node);

    /**
     * Remove an element
     * @param node DoublyNode
     **/
    void remove(DoublyNode *node);

    /**
     * Displays the complete list.
     **/
    void display();

};

DoublyLinkedList::DoublyLinkedList() {
    this->head = NULL;
    this->foot = NULL;
};

DoublyLinkedList::~DoublyLinkedList() {
    DoublyNode *current = this->head;
    while (current->next != NULL) {
        DoublyNode *next = current->next;
        delete current;
        current = next;
    }
};

void DoublyLinkedList::insert(DoublyNode *node) {
    if (this->head == NULL) {
        this->head = node;
        return;
    }
    this->foot = node;

    DoublyNode *prev = NULL;
    DoublyNode *current = this->head;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    current->prev = prev;
    current->next = node;
};

void DoublyLinkedList::remove(DoublyNode *node) {
    DoublyNode *current = this->head;
    // case removing head
    if (current == node) {
        this->head = current->next;
        this->head->prev = NULL;
        delete current;
        return;
    }
    // the other case
    while (current->next != NULL) {
        DoublyNode *next = current->next;
        if (next == node) {
            current->next = next->next;
            next->next->prev = current;
            delete next;
            break;
        }
        current = next;
    }
}

void DoublyLinkedList::display() {
    std::cout << "Doubly Linked List: ";
    DoublyNode *current = this->head;
    std::cout << "NULL <- " << current->value;
    while (current->next != NULL) {
        std::cout << " <=> " << current->next->value;
        current = current->next;
    }
    std::cout << " -> NULL" << std::endl;

    int index = 0;
    current = this->head;
    while (current->next != NULL) {
        std::cout << "index:" << index << " prev:" << ((current->prev == NULL) ? NULL : current->prev->value) << " current:" << current->value << " next:" << ((current->next == NULL) ? NULL : current->next->value) << std::endl;
        current = current->next;
        index++;
    }
    std::cout << std::endl;
};


int main() {
    DoublyLinkedList *linkedList = new DoublyLinkedList();

    std::srand(std::time(0));
    const int count = std::rand() % 5 + 5;

    for (int i = 0; i < count; i++) {
        DoublyNode *node = new DoublyNode(std::rand()%10+1);
        linkedList->insert(node);
    }

    std::cout << "Created: " << std::endl;
    linkedList->display();

    const int index = std::rand() % 5;
    DoublyNode *current = linkedList->head;
    for (int i = 0; i <= index; i++) {
        if (i == index) {
            linkedList->remove(current);
            break;
        }
        current = current->next;
    }
    std::cout << "Removed (index=" << index << "):" << std::endl;
    linkedList->display();

    delete linkedList;

    return 0;
};

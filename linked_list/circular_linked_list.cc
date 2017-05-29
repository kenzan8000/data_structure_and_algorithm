// Linked List whose last item contains link of the first element as next and the first element has a link to the last element as previous.


#include <iostream>
#include <cstdlib>
#include <ctime>


class CircularNode {
public:
    CircularNode *next;
    int value;

    CircularNode(int value);
    ~CircularNode();
};

CircularNode::CircularNode(int value) {
    this->next = NULL;
    this->value = value;
};

CircularNode::~CircularNode() {
};


class CircularLinkedList {
public:
    CircularNode *head;

    CircularLinkedList();
    ~CircularLinkedList();

    /**
     * Adds an element at the last of the list.
     * @param node CircularNode
     **/
    void insert(CircularNode *node);

    /**
     * Remove an element
     * @param node CircularNode
     **/
    void remove(CircularNode *node);

    /**
     * Displays the complete list.
     **/
    void display();

};

CircularLinkedList::CircularLinkedList() {
    this->head = NULL;
};

CircularLinkedList::~CircularLinkedList() {
    CircularNode *current = this->head;
    while (current->next != NULL) {
        CircularNode *next = current->next;
        delete current;
        current = next;
    }
};

void CircularLinkedList::insert(CircularNode *node) {
    if (this->head == NULL) {
        this->head = node;
        node->next = node;
        return;
    }

    CircularNode *current = this->head;
    while (current->next != this->head) {
        current = current->next;
    }
    current->next = node;
    node->next = this->head;
};

void CircularLinkedList::remove(CircularNode *node) {
    CircularNode *current = this->head;
    // case removing head
    if (current == node) {
        this->head = current->next;
        CircularNode *elementToRemove = current;
        while (current->next != elementToRemove) {
            current = current->next;
        }
        current->next = this->head;
        delete elementToRemove;
        return;
    }

    // the other case
    while (current->next != this->head) {
        CircularNode *next = current->next;
        if (next == node) {
            current->next = next->next;
            delete next;
        }
        current = next;
    }
    current->next = this->head;
}

void CircularLinkedList::display() {
    std::cout << "Circular Linked List: ";
    CircularNode *current = this->head;
    std::cout << current->value;
    while (current->next != this->head) {
        std::cout << " -> " << current->next->value;
        current = current->next;
    }
    std::cout << " -> " << this->head->value << "(head)";
    std::cout << std::endl;
};


int main() {
    CircularLinkedList *linkedList = new CircularLinkedList();

    std::srand(std::time(0));
    const int count = std::rand() % 5 + 5;

    for (int i = 0; i < count; i++) {
        CircularNode *node = new CircularNode(std::rand()%10+1);
        linkedList->insert(node);
    }

    std::cout << "Created: " << std::endl;
    linkedList->display();

    const int index = std::rand() % 5;
    CircularNode *current = linkedList->head;
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

// Linked List whose items can be navigated forward and backward.
// Also, Linked List whose last item contains link of the first element as next and the first element has a link to the last element as previous


#include <iostream>
#include <cstdlib>
#include <ctime>


class DoublyCircularNode {
public:
    DoublyCircularNode *prev;
    DoublyCircularNode *next;
    int value;

    DoublyCircularNode(int value);
    ~DoublyCircularNode();
};

DoublyCircularNode::DoublyCircularNode(int value) {
    this->prev = NULL;
    this->next = NULL;
    this->value = value;
};

DoublyCircularNode::~DoublyCircularNode() {
};


class DoublyCircularLinkedList {
public:
    DoublyCircularNode *head;

    DoublyCircularLinkedList();
    ~DoublyCircularLinkedList();

    /**
     * Adds an element at the last of the list.
     * @param node DoublyCircularNode
     **/
    void insert(DoublyCircularNode *node);

    /**
     * Remove an element
     * @param node DoublyCircularNode
     **/
    void remove(DoublyCircularNode *node);

    /**
     * Displays the complete list.
     **/
    void display();

};

DoublyCircularLinkedList::DoublyCircularLinkedList() {
    this->head = NULL;
};

DoublyCircularLinkedList::~DoublyCircularLinkedList() {
    DoublyCircularNode *current = this->head;
    while (current->next != this->head) {
        DoublyCircularNode *next = current->next;
        delete current;
        current = next;
    }
};

void DoublyCircularLinkedList::insert(DoublyCircularNode *node) {
    if (this->head == NULL) {
        this->head = node;
        node->next = node;
        node->prev = node;
        return;
    }

    DoublyCircularNode *prev = NULL;
    DoublyCircularNode *current = this->head;
    while (current->next != this->head) {
        prev = current;
        current = current->next;
    }
    current->next = node;
    node->next = this->head;
    this->head->prev = node;
};

void DoublyCircularLinkedList::remove(DoublyCircularNode *node) {
    DoublyCircularNode *current = this->head;
    // case removing head
    if (current == node) {
        // get foot
        DoublyCircularNode *foot = current->next;
        while (current->next != this->head) {
            current = current->next;
        }
        foot = current;
        // remove head
        DoublyCircularNode *head = this->head->next;
        delete this->head;
        // renew connection
        this->head = head;
        this->head->prev = foot;
        foot->next = head;
        return;
    }
    else {
        DoublyCircularNode *foot = current->next;
        while (current->next != this->head) {
            current = current->next;
        }
        foot = current;
        // case removing foot
        if (foot == node) {
            this->head->prev = foot->prev;
            foot->prev->next = this->head;
            delete foot;
            return;
        }
    }

    // the other case
    current = this->head;
    while (current->next != this->head) {
        DoublyCircularNode *next = current->next;
        if (next == node) {
            current->next = next->next;
            next->next->prev = current;
            delete next;
            break;
        }
        current = next;
    }
}

void DoublyCircularLinkedList::display() {
    DoublyCircularNode *current = this->head;
    DoublyCircularNode *foot = current->next;
    while (current->next != this->head) {
        current = current->next;
    }
    foot = current;

    std::cout << "Doubly Circular Linked List: ";
    current = this->head;
    std::cout << foot->value << "(foot) <- " << current->value;
    while (current->next != this->head) {
        std::cout << " <=> " << current->next->value;
        current = current->next;
    }
    std::cout << " -> " << this->head->value << "(head)" << std::endl;

    int index = 0;
    current = this->head;
    while (current->next != this->head) {
        std::cout << "index:" << index << " prev:" << ((current->prev == NULL) ? NULL : current->prev->value) << " current:" << current->value << " next:" << ((current->next == NULL) ? NULL : current->next->value) << std::endl;
        current = current->next;
        index++;
    }
    std::cout << std::endl;
};


int main() {
    DoublyCircularLinkedList *linkedList = new DoublyCircularLinkedList();

    std::srand(std::time(0));
    const int count = std::rand() % 5 + 5;

    for (int i = 0; i < count; i++) {
        DoublyCircularNode *node = new DoublyCircularNode(std::rand()%10+1);
        linkedList->insert(node);
    }

    std::cout << "Created: " << std::endl;
    linkedList->display();

    const int index = std::rand() % 5;
    DoublyCircularNode *current = linkedList->head;
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

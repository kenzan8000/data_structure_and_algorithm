#include <iostream>
#include <cstdlib>
#include <ctime>


// Stack

class Stack {
public:
    int *elements;
    int top;
    int size;

    Stack(int size);
    ~Stack();

    /**
     * Pushing (storing) an element on the stack.
     * @param element int
     **/
    void push(int element);

    /**
     * Removing (accessing) an element from the stack.
     * @return element int
     **/
    int pop();

    /**
     * Get the top data element of the stack, without removing it.
     * @return element int
     **/
     int peek();

    /**
     * Check if stack is full.
     * @return true or false Bool
     **/
    bool isFull();

    /**
     * Check if stack is empty.
     * @return true or false Bool
     **/
    bool isEmpty();

    /**
     * Displays the complete elements.
     **/
    void display();

};

Stack::Stack(int size) {
    this->elements = new int[size];
    this->top = -1;
    this->size = size;
};

Stack::~Stack() {
    delete[] this->elements;
};

void Stack::push(int element) {
    if (this->isFull()) { return; }

    this->top++;
    this->elements[this->top] = element;
};

int Stack::pop() {
    int element = this->peek();
    if (this->isEmpty()) { return element; }

    this->top--;
    return element;
};

int Stack::peek() {
    if (this->isEmpty()) { return -1; }
    return this->elements[this->top];
};

bool Stack::isFull() {
    return (this->top >= this->size - 1);
};

bool Stack::isEmpty() {
    return (this->top < 0);
};

void Stack::display() {
    std::cout << "Stack:" << std::endl;
    for (int i = this->size-1; i >= 0; i--) {
        if (i > this->top) {
            std::cout << "[   ]" << std::endl;
        }
        else {
            std::cout << "[ " << this->elements[i] << " ]" << std::endl;
        }
    }
};


int main() {
    std::srand(std::time(0));
    const int size = std::rand() % 5 + 5;
    Stack *stack = new Stack(size);

    const int operationCount = size * 3;
    for (int i = 0; i < operationCount; i++) {
        if (std::rand() % 2) {
            std::cout << "----- Pushed -----" << std::endl;
            const int element = std::rand() % 10;
            stack->push(element);
        }
        else {
            std::cout << "----- Poped -----" << std::endl;
            stack->pop();
        }
        stack->display();
    }

    delete stack;

    return 0;
};

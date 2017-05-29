#include <iostream>
#include <cstdlib>
#include <ctime>


// Stack

struct Element {
    int value;
    char op[1];
};

class Stack {
public:
    Element *elements;
    int top;
    int size;

    Stack(const int size);
    ~Stack();

    /**
     * Pushing (storing) an element on the stack.
     * @param element Element
     **/
    void push(Element element);

    /**
     * Removing (accessing) an element from the stack.
     * @return element Element
     **/
    Element pop();

    /**
     * Get the top data element of the stack, without removing it.
     * @return element Element
     **/
     Element peek();

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

Stack::Stack(const int size) {
    this->elements = new Element[size];
    this->top = -1;
    this->size = size;
};

Stack::~Stack() {
    delete[] this->elements;
};

void Stack::push(Element element) {
    if (this->isFull()) { return; }

    this->top++;
    this->elements[this->top] = element;
};

Element Stack::pop() {
    Element element = this->peek();
    this->top--;
    return element;
};

Element Stack::peek() {
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
            if (this->elements[i].op != (char *)NULL) {
                std::cout << "[ " << this->elements[i].op[0] << " ]" << std::endl;
            }
            else {
                std::cout << "[ " << this->elements[i].value << " ]" << std::endl;
            }
        }
    }
};

class ExpressionParsing: public Stack {
    public:

    ExpressionParsing(const int size);
    ~ExpressionParsing();

    /**
     * Calculate
     **/
    void calculate();
};

ExpressionParsing::ExpressionParsing(const int size) : Stack(size) {
};

ExpressionParsing::~ExpressionParsing() {
};

void ExpressionParsing::calculate() {
};


int main() {
    std::srand(std::time(0));

    const char *oprators = "+-*/";
    const int size = 3;
    Element infixNotation[size];
    ExpressionParsing *expressionParsing = new ExpressionParsing(size);
    for (int i = 0; i < size; i++) {
        Element element;
        if (i % 2 == 0) { // number
            element.value = std::rand() % 9 + 1;
        }
        else { // operator
            element.op[0] = oprators[std::rand() % 4];
        }
        infixNotation[i] = element;
    }
    expressionParsing->display();

    delete expressionParsing;

    return 0;
};

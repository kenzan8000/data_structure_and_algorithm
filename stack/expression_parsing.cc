#include <iostream>
//#include <cstdlib>
//#include <ctime>
#include <string>


// Stack

class Stack {
public:
    char *elements;
    int top;
    int size;
    std::string name;

    Stack(const int size, const std::string name);
    ~Stack();

    /**
     * Pushing (storing) an element on the stack.
     * @param element char
     **/
    void push(char element);

    /**
     * Removing (accessing) an element from the stack.
     * @return element char
     **/
    char pop();

    /**
     * Get the top data element of the stack, without removing it.
     * @return element char
     **/
     char peek();

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
    void displayStack();

};

Stack::Stack(const int size, const std::string name) {
    this->elements = new char[size];
    this->top = -1;
    this->size = size;
    this->name = name;
};

Stack::~Stack() {
    delete[] this->elements;
};

void Stack::push(char element) {
    if (this->isFull()) { return; }

    this->top++;
    this->elements[this->top] = element;
};

char Stack::pop() {
    char element = this->peek();
    this->top--;
    return element;
};

char Stack::peek() {
    return this->elements[this->top];
};

bool Stack::isFull() {
    return (this->top >= this->size - 1);
};

bool Stack::isEmpty() {
    return (this->top < 0);
};

void Stack::displayStack() {
    std::cout << this->name << std::endl;
    for (int i = this->size-1; i >= 0; i--) {
        if (i > this->top) {
            std::cout << "[   ]" << std::endl;
        }
        else {
            std::cout << "[ " << this->elements[i] << " ]" << std::endl;
        }
    }
};


bool isOperator(char element) {
    return (element == '+' || element == '-' || element == '*' || element == '/' || element =='^');
}

bool isOperand(char element) {
    return (!isOperator(element) && element != '(' && element != ')');
}

int associativity(char element) {
    int value = -1;
    switch (element) {
        case '+':
        case '-':
            value = 1;
            break;
        case '*':
        case '/':
            value = 2;
            break;
        case '^':
            value = 3;
            break;
        case '(':
        case ')':
            value = 0;
            break;
    }
    return value;
}


int main() {
    std::string infix = "(A+B^C)*D+E^5";

    // infix to prefix notation
    Stack *stack = new Stack(infix.length(), "Stack");
    Stack *prefix = new Stack(infix.length(), "Prefix");
    for(int i = infix.length()-1; i >= 0; i--) {
        char symbol = infix[i];

        // when number
        if (isOperand(symbol)) {
            prefix->push(symbol);

            std::cout << "-------------------" << std::endl;
            prefix->displayStack();
            stack->displayStack();
        }
        else {
            if (symbol == '(') {
                //symbol = ')';
                //stack->push(symbol);

                while (!stack->isEmpty() && stack->peek() != ')') {
                    prefix->push(stack->pop());

                    std::cout << "-------------------" << std::endl;
                    prefix->displayStack();
                    stack->displayStack();
                }
                stack->pop();

                std::cout << "-------------------" << std::endl;
                prefix->displayStack();
                stack->displayStack();
            }
            else if (symbol == ')') {
                //symbol = '(';
                //while (!stack->isEmpty() && stack->peek() != ')') {
                //    prefix->push(stack->pop());

                //    std::cout << "-------------------" << std::endl;
                //    prefix->displayStack();
                //    stack->displayStack();
                //}
                //stack->pop();

                stack->push(symbol);

                std::cout << "-------------------" << std::endl;
                prefix->displayStack();
                stack->displayStack();
            }
            else {
                if (associativity(stack->peek()) <= associativity(symbol)) {
                    stack->push(symbol);

                    std::cout << "-------------------" << std::endl;
                    prefix->displayStack();
                    stack->displayStack();
                }
                else {
                    while (!stack->isEmpty() && associativity(stack->peek()) >= associativity(symbol)) {
                        prefix->push(stack->pop());

                        std::cout << "-------------------" << std::endl;
                        prefix->displayStack();
                        stack->displayStack();
                    }
                    stack->push(symbol);

                    std::cout << "-------------------" << std::endl;
                    prefix->displayStack();
                    stack->displayStack();
                }
            }
        }
        std::cout << "-------------------" << std::endl;
        prefix->displayStack();
        stack->displayStack();
    }
	while (!stack->isEmpty()) {
		char symbol = stack->pop();
        prefix->push(symbol);

        std::cout << "-------------------" << std::endl;
        prefix->displayStack();
        stack->displayStack();
	}

    return 0;
};

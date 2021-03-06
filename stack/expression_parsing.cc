#include <iostream>
#include <cmath>
#include <string>


// Stack

template <class T>
class Stack {
public:
    T *elements;
    int top;
    int size;
    std::string name;

    Stack(const int size, const std::string name);
    ~Stack();

    /**
     * Pushing (storing) an element on the stack.
     * @param element char
     **/
    void push(T element);

    /**
     * Removing (accessing) an element from the stack.
     * @return element char
     **/
    T pop();

    /**
     * Get the top data element of the stack, without removing it.
     * @return element char
     **/
     //char peek();
     T peek();

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

template <class T>
Stack<T>::Stack(const int size, const std::string name) {
    this->elements = new T[size];
    this->top = -1;
    this->size = size;
    this->name = name;
};

template <class T>
Stack<T>::~Stack() {
    delete[] this->elements;
};

template <class T>
void Stack<T>::push(T element) {
    if (this->isFull()) { return; }

    this->top++;
    this->elements[this->top] = element;
};

template <class T>
T Stack<T>::pop() {
    T element = this->peek();
    this->top--;
    return element;
};

template <class T>
T Stack<T>::peek() {
    return this->elements[this->top];
};

template <class T>
bool Stack<T>::isFull() {
    return (this->top >= this->size - 1);
};

template <class T>
bool Stack<T>::isEmpty() {
    return (this->top < 0);
};

template <class T>
void Stack<T>::displayStack() {
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

int toInt(char element) {
    return (element - '0');
}


int main() {
    std::string infix = "(1+2^3)*4+5^6";

    Stack<char> *stack = new Stack<char>(infix.length(), "Stack");

    // infix to prefix notation
    Stack<char> *prefix = new Stack<char>(infix.length(), "Prefix");
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

    // prefix to postfix notation
    Stack<char> *postfix = new Stack<char>(infix.length(), "Postfix");
    for (int i = prefix->top; i >= 0; i--) {
        postfix->push(prefix->elements[i]);
    }
    std::cout << "-------------------" << std::endl;
    prefix->displayStack();
    postfix->displayStack();

    // using postfix for caliculation
    Stack<int> *intStack = new Stack<int>(infix.length(), "Int Stack");
	while (!postfix->isEmpty()) {
        char symbol = postfix->pop();
        if (isOperand(symbol)) {
            intStack->push(toInt(symbol));
        }
        else {
            int accumulator = 0;
            int left = intStack->pop();
            int right = intStack->pop();
            switch (symbol) {
                case '+':
                    accumulator = left + right;
                    break;
                case '-':
                    accumulator = left - right;
                    break;
                case '*':
                    accumulator = left * right;
                    break;
                case '/':
                    accumulator = left / right;
                    break;
                case '^':
                    accumulator = (int)std::pow(left, right);
                    break;
            }
            intStack->push(accumulator);
            std::cout << "-------------------" << std::endl;
            std::cout << left << symbol << right << '=' << accumulator << std::endl;
            intStack->displayStack();
        }
    }
    std::cout << "-------------------" << std::endl;
    intStack->displayStack();

    return 0;
};

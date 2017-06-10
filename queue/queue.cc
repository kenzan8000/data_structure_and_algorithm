#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>


// Queue

template <class T>
class Queue {
public:
    T *elements;
    int front;
    int size;
    std::string name;

    Queue(const int size, const std::string name);
    ~Queue();

    /**
     * add an element
     * @param element T
     **/
    void enqueue(T element);

    /**
     * remove an element
     * @return element T
     **/
    T dequeue();

    /**
     * Get the element at the front of the queue without removing it.
     * @return element T
     **/
     T peek();

    /**
     * Check if queue is full.
     * @return true or false Bool
     **/
    bool isFull();

    /**
     * Check if queue is empty.
     * @return true or false Bool
     **/
    bool isEmpty();

    /**
     * Displays the complete elements.
     **/
    void display();

};

template <class T>
Queue<T>::Queue(const int size, const std::string name) {
    this->elements = new T[size];
    this->front = -1;
    this->size = size;
    this->name = name;
};

template <class T>
Queue<T>::~Queue() {
    delete[] this->elements;
};

template <class T>
void Queue<T>::enqueue(T element) {
    if (this->isFull()) { return; }

    this->front++;
    for (int i = this->front; i > 0; i--) {
        this->elements[i] = this->elements[i-1];
    }
    this->elements[0] = element;
};

template <class T>
T Queue<T>::dequeue() {
    T element = this->peek();
    this->front--;
    return element;
};

template <class T>
T Queue<T>::peek() {
    return this->elements[this->front];
};

template <class T>
bool Queue<T>::isFull() {
    return (this->front >= this->size-1);
};

template <class T>
bool Queue<T>::isEmpty() {
    return (this->front < 0);
};

template <class T>
void Queue<T>::display() {
    std::cout << this->name << std::endl;
    for (int i = 0; i < this->size; i++) {
        if (i > this->front) { std::cout << "[   ]"; }
        else { std::cout << "[ " << this->elements[i] << " ]"; }
    }
    std::cout << std::endl;
};



int main() {
    std::srand(std::time(0));

    const int size = 5;
    const int count = 10;
    Queue<int> *queue = new Queue<int>(size, "Queue");
    for (int i = 0; i <= count; i++) {
        std::cout << "------------------------------" << std::endl;
        queue->display();

        std::cout << "------------------------------" << std::endl;
        if (queue->isFull()) {
            std::cout << "dequeued: " << queue->dequeue() << ", ";
        }
        const int number = std::rand() % 10;
        queue->enqueue(number);
        std::cout << "enqueued: " << number;
        std::cout << std::endl;
    }
    std::cout << "------------------------------" << std::endl;
    queue->display();

    return 0;
};

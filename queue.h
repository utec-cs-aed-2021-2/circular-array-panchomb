#include "circulararray.h"

template <typename T>
class QueueArray : public CircularArray<T> { 
    public:
        void enqueue(int data) {
            push_back(data);
        };
        T dequeue() {
            T final = pop_front();
            return final;
        };
};
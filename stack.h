#include "circulararray.h"

template <typename T>
class StackArray : public CircularArray<T> { 
    public:
        void push(T data) {
            push_back(data);
        }
        T pop() { 
            T final = pop_back();
            return final;
        }
};
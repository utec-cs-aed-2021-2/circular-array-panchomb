#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray();
    CircularArray(int _capacity) {
        array = new T[_capacity];
        this->capacity = capacity;
    };
    virtual ~CircularArray();
    void push_front(T data) {
        if (is_empty()) {
            front = back;
            *(array + front) = data;
        } else if (is_full()) {
            capacity *= 2;
            T *new_array = new T[capacity];
            for (int i = front; i <= back; i++) {
                *(new_array + i) = *(array + i);
            }
            array = new_array;
            front = (front-1)%capacity;
            *(array + front) = data;
        } else {
            front = (front-1)%capacity;
            *(array + front) = data;
        }
    };
    void push_back(T data) {
        if (is_empty()) {
            front = back;
            *(array + back) = data;
        } else if (is_full()) {
            capacity *= 2;
            T *new_array = new T[capacity];
            for (int i = front; i <= back; i++) {
                *(new_array + i) = *(array + i);
            }
            back = (back+1)%capacity;
            *(array + back) = data;
            array = new_array;
        }
        else {
            back = (back+1)%capacity;
            *(array + back) = data;
        }
    };
    void insert(T data, int pos) {
        if (pos > capacity) {
            return;
        } else {
            *(array + pos) = data;
        }
    };
    T pop_front() {
        if (is_empty()) {
            return;
        }
        else if (size() == 1) {
            front = -1;
        }
        else {
            T final = *(array + front);
            front = (front+1)%capacity;
            return final;
        }
        
    };
    T pop_back() {
        if (is_empty()) {
            return;
        }
        else if (size() == 1) {
            front = -1;
        }
        else {
            T final = *(array + back);
            back = (back-1)%capacity;
            return final;
        }
    };
    bool is_full() {
        return (capacity == size());
    };
    bool is_empty() {
        return (front==-1);
    };
    int size() {
        return back-front+1;
    };
    void clear() {
        delete []array;
        array = new T[capacity];
    };
    T &operator[](int index) {
        return *(array + index);
    };
    void sort();
    bool is_sorted(){
        for (int i = front; i < back; i++) {
            if (*(array + i) > *(array + i + 1)) {
                return false;
            }
        }
        return true;
    };
    void reverse() {
        T *new_array = new T[capacity];
        for (int i = back; i <= front; i--) {
            *(new_array + size() - i) = *(array + i);
        }
        array = new_array;
    };
    string to_string(string sep=" ");

private:
    int next(int);
    int prev(int);
};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;    
}

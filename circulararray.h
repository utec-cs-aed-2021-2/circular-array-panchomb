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
    CircularArray(int _capacity);
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
            front = (front==0)?(capacity-1):(front-1)%capacity;
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
        if (!is_empty()) {
            if (size() == 1) {
                T final = *(array + front);
                front = -1;
                return final;
            }
            else {
                T final = *(array + front);
                front = (front+1)%capacity;
                return final;
            }
        }
    };
    T pop_back() {
        if (!is_empty()) {
            if (size() == 1) {
                T final = *(array + back);
                front = -1;
                return final;
            }
            else {
                T final = *(array + back);
                back = (back==0)?(capacity-1):(back-1)%capacity;
                return final;
            }
        }
    };
    bool is_full() {
        return (capacity == size());
    };
    bool is_empty() {
        return (front==-1);
    };
    int size() {
        return front>back?(capacity - (front-back+1) + 2):(back-front+1);
    };
    void clear() {
        delete []array;
        array = new T[capacity];
    };
    T &operator[](int index) {
        return *(array + index);
    };
    void swap(int* a, int* b){
        int temp = *a;
        *a = *b;
        *b = temp;
    }
    int index(int i) {
        return (i+front)%capacity;
    }
    int partition(int* arr, int low, int high){
        int pivot = arr[index(high)];	// ultimo elemento del vector
        int i = (low - 1);

        for(int j=low; j<=high-1; j++){
            if(arr[index(j)] <= pivot){
                i++;
                swap(&arr[index(i)], &arr[index(j)]);
            }
        }

        swap(&arr[index(i+1)], &arr[index(high)]);

        return (i+1);
    }
    void quickSort(int arr[], int low, int high) {
        if (low < high) {
            int pivot = partition(arr, low, high);
    
            quickSort(arr, low, pivot - 1);
            quickSort(arr, pivot + 1, high);
        }
    }
    void sort() {
        quickSort(array, 0, size()-1);
    }
    bool is_sorted(){
        for (int i = 0; i < size(); i++) {
            if (array[(i+front)%capacity] > array[(i+front)%capacity + 1]) {
                return false;
            }
        }
        return true;
    };
    void reverse() {
        int* new_array = new int[capacity];
        for (int i = 0; i < size(); i++) {
            new_array[index(i)] = array[index(size() - i - 1)];
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
    this->front = -1;
    this->back = 0;
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
        result += std::to_string((*this)[index(i)]) + sep;
    return result;    
}

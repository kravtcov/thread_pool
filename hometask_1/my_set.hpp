#pragma once
#include <algorithm>
#include <iostream>

template <typename T>
class MySet {
public:
    bool isEmpty();
    size_t getSize();
    MySet(size_t size = 0);
    MySet(const MySet& other);
    MySet& operator=(const MySet& other);
    ~MySet();
    void insert(T elem);

private:
    T *_data_array;
    size_t _size;
};


template <typename T>
MySet<T> getSet()
{
    std::cout << "get" << std::endl;
    MySet<T> new_set(16);
    return new_set;
}

template <typename T>
MySet<T>::MySet(size_t size)
    : _size(size),
      _data_array(_size ? new T[_size] : nullptr)
{
    std::cout << "constructor" << std::endl;
}

template <typename T>
MySet<T>::MySet(const MySet& other)
    : _size(other._size),
      _data_array(_size ? new T[_size] : nullptr)
{
    std::cout << "copy constructor" << std::endl;
    std::copy_n(other._data_array, _size, _data_array);
}

template <typename T>
MySet<T>& MySet<T>::operator=(const MySet& other)
{
    std::cout << "copy assignment operator" << std::endl;
    if (this != &other)
    {
        if (_size != other._size)
        {
            _size = other._size;
            _data_array = _size ? new T[_size] : nullptr;
        }

        std::copy_n(other._data_array, _size, _data_array);
    }
    return *this;
}

template <typename T>
MySet<T>::~MySet() {
    std::cout << "destructor" << std::endl;
    delete [] _data_array;
}

template <typename T>
bool MySet<T>::isEmpty() {
    return !_size;
}

template <typename T>
size_t MySet<T>::getSize() {
    return _size;
}

template <typename T>
void MySet<T>::insert(T elem) {
  //if ( find(elem) == 0) {
  //    if ( _size == _max_size) {
  //        _max_size *= 2;
  //        T temp_data = new T[_max_size];

  //    }
  //}

}


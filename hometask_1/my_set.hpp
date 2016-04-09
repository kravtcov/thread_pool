#pragma once
#include <algorithm>
#include <iostream>

template <typename T> class MySet;
template <typename T> void swap(MySet<T> &first, MySet<T> &second);

template <typename T>
class MySet {
public:
    MySet(size_t size = 0);
    MySet(const MySet &other);
    MySet& operator=(const MySet &other);
    MySet(MySet &&other);
    MySet& operator=(MySet &&other);
    ~MySet();

    bool isEmpty() const;
    size_t getSize() const;
    bool isContained(const T &item) const;
    void insert(const T &item);

    friend void swap<T>(MySet &first, MySet &second);

private:
    size_t _size;
    T *_data_array;
};

template <typename T>
bool MySet<T>::isContained(const T &item) const
{
    for (T set_item : _data_array)
    {
        if (set_item == item)
            return true;
    }
    return false;
}


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

// copy constructor
template <typename T>
MySet<T>::MySet(const MySet &other)
    : _size(other._size),
      _data_array(_size ? new T[_size] : nullptr)
{
    std::cout << "copy constructor" << std::endl;
    std::copy_n(other._data_array, _size, _data_array);
}

// copy assignmen operator
template <typename T>
MySet<T>& MySet<T>::operator=(const MySet &other)
{
    std::cout << "copy assignment operator" << std::endl;
    if (this != &other)
    {
        MySet<T> temp(other);
        swap(*this, temp);
    }
    return *this;
}

// move constructor
template <typename T>
MySet<T>::MySet(MySet &&other)
    : _size(0),
      _data_array(nullptr) // necessary!!
{
    std::cout << "move constructor" << std::endl;
    swap(*this, other);
}

// move assignmen operator
template <typename T>
MySet<T>& MySet<T>::operator=(MySet &&other)
{
    std::cout << "move assignment operator" << std::endl;
    if (this != &other)
    {
        swap(*this, other);
    }
    return *this;
}

template <typename T>
MySet<T>::~MySet() {
    std::cout << "destructor" << std::endl;
    if (_data_array)
        delete [] _data_array;
}

template <typename T>
bool MySet<T>::isEmpty() const {
    return !_size;
}

template <typename T>
size_t MySet<T>::getSize() const {
    return _size;
}

template <typename T>
void MySet<T>::insert(const T &item) {
  if (!isContained(item)) {
      MySet<T> updated_set(_size + 1);
      updated_set = *this;
      *this = std::move(updated_set);
      _data_array[_size++] = item;

    //if ( _size == _max_size) {
    //    _max_size *= 2;
    //    T temp_data = new T[_max_size];

    //}
  }

}

template <typename T>
void swap(MySet<T> &first, MySet<T> &second)
{
    std::swap(first._size, second._size);
    std::swap(first._data_array, second._data_array);
}


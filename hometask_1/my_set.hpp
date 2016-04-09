#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

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

    std::string dump() const;

    friend void swap<T>(MySet &first, MySet &second);

private:
    size_t _size;
    T *_data_array;
};

template <typename T>
bool MySet<T>::isContained(const T &item) const
{
    //for (T set_item : _data_array)
    for (size_t i = 0; i < _size; i++)
    {
        if (_data_array[i] == item)
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
    std::copy_n(other._data_array, _size, _data_array);
    std::cout << "copy constructor of " << *this << std::endl;
}

// copy assignmen operator
template <typename T>
MySet<T>& MySet<T>::operator=(const MySet &other)
{
    if (this != &other)
    {
        MySet<T> temp(other);
        swap(*this, temp);
    }
    std::cout << "copy assignment operator of " << *this << std::endl;
    return *this;
}

// move constructor
template <typename T>
MySet<T>::MySet(MySet &&other)
    : _size(0),
      _data_array(nullptr) // necessary!!
{
    swap(*this, other);
    std::cout << "move constructor of " << *this << std::endl;
}

// move assignmen operator
template <typename T>
MySet<T>& MySet<T>::operator=(MySet &&other)
{
    if (this != &other)
    {
        swap(*this, other);
    }
    std::cout << "move assignment operator of " << *this << std::endl;
    return *this;
}

template <typename T>
MySet<T>::~MySet() {
    std::cout << "destructor of " << *this << std::endl;
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
        std::copy_n(_data_array, _size, updated_set._data_array);
        updated_set._data_array[_size] = item;
        *this = std::move(updated_set);

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

template <typename T>
std::string MySet<T>::dump() const
{
    std::ostringstream oss;
    if (!_size)
    {
        oss << "item is empty";
        return oss.str();
    }

    T first_item = _data_array[0];
    oss << "{ " << first_item;

    size_t second_item_index = 1;
    for (size_t offset = second_item_index; offset < _size; offset++)
    {
        oss << ", " << _data_array[offset];
    }
    oss << "}";
    return oss.str();
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const MySet<T> &item)
{
    return out << item.dump();
}

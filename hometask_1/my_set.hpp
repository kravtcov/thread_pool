#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

template <typename T> class MySet;
template <typename T> void swap(MySet<T> &first, MySet<T> &second);

template <typename T>
MySet<T> setUnion(const MySet<T> &first, const MySet<T> &second);

template <typename T>
MySet<T> setDifference(const MySet<T> &first, const MySet<T> &second);

template <typename T>
MySet<T> setIntersection(const MySet<T> &first, const MySet<T> &second);

template <typename T>
class MySet
{
public:
    MySet(size_t max_size = 0);
    MySet(const MySet &other);
    MySet(MySet &&other);
    MySet& operator=(MySet other);
    ~MySet();

    bool isEmpty() const;
    size_t getSize() const;
    bool isContained(const T &item) const;

    void insert(const T &item);
    void extend(const MySet &other);

    void erase(const T &item);

    // erase intersection of this and other from this
    void erase(const MySet<T> &other);
    void intersect(const MySet<T> &other);

    std::string dump() const;

    friend void swap<T>(MySet &first, MySet &second);
    friend MySet setUnion<T>(const MySet &first, const MySet &second);
    friend MySet setDifference<T>(const MySet &first, const MySet &second);
    friend MySet setIntersection<T>(const MySet &first, const MySet &second);

    MySet& operator+=(const MySet& other);
    MySet& operator-=(const MySet& other);
    MySet& operator&=(const MySet& other);

private:
    size_t _size;     // the current size
    size_t _max_size; // the allocated size
    static const size_t _min_size = 1;
    T *_data_array;

    int getIndexOf(const T &item) const;
};

template <typename T>
void swap(MySet<T> &first, MySet<T> &second)
{
    std::swap(first._size, second._size);
    std::swap(first._max_size, second._max_size);
    std::swap(first._data_array, second._data_array);
}

template <typename T>
MySet<T>& MySet<T>::operator+=(const MySet<T> &other)
{
    extend(other);
    return *this;
}

template <typename T>
MySet<T>& MySet<T>::operator-=(const MySet<T> &other)
{
    erase(other);
    return *this;
}

template <typename T>
MySet<T>& MySet<T>::operator&=(const MySet<T> &other)
{
    intersect(other);
    return *this;
}

template <typename T>
MySet<T> operator+(MySet<T> &first, const MySet<T> &second)
{
    return setUnion(first, second);
}

// Allow also get 'set union' throught | : A | B == A + B
template <typename T>
MySet<T> operator|(MySet<T> &first, const MySet<T> &second)
{
    return setUnion(first, second);
}

template <typename T>
MySet<T> operator-(MySet<T> &first, const MySet<T> &second)
{
    return setDifference(first, second);
}

// be aware of operator precedence:
// & has less precedence that <<
template <typename T>
MySet<T> operator&(MySet<T> &first, MySet<T> &second)
{
    return setIntersection(first, second);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const MySet<T> &item)
{
    return out << item.dump();
}

template <typename T>
bool MySet<T>::isContained(const T &item) const
{
    return getIndexOf(item) >= 0;
}

template <typename T>
int MySet<T>::getIndexOf(const T &item) const
{
    //for (T set_item : _data_array)
    for (size_t idx = 0; idx < _size; ++idx)
    {
        if (_data_array[idx] == item)
            return idx;
    }
    return -1;
}


template <typename T>
MySet<T>::MySet(size_t max_size)
    : _size(0),
      _max_size(max_size ? max_size : _min_size),
      _data_array(_max_size ? new T[_max_size] : nullptr)
{
    std::cout << "constructor with max size " << max_size << std::endl;
}

// copy constructor
template <typename T>
MySet<T>::MySet(const MySet &other)
    : _size(other._size),
      _max_size(other._max_size),
      _data_array(_max_size ? new T[_max_size] : nullptr)
{
    std::copy_n(other._data_array, _size, _data_array);
    std::cout << "copy constructor of " << *this << std::endl;
}

// move constructor
template <typename T>
MySet<T>::MySet(MySet &&other)
    : _size(0),
      _max_size(_min_size),
      _data_array(nullptr) // necessary!!
{
    swap(*this, other);
    std::cout << "move constructor of " << *this << std::endl;
}

// assignment operator
template <typename T>
MySet<T>& MySet<T>::operator=(MySet other)
{
    // there is waste copy in constructor while this == &other
    swap(*this, other);
    std::cout << "assignment operator of " << *this << std::endl;
    return *this;
}

template <typename T>
MySet<T>::~MySet()
{
    std::cout << "destructor of " << *this << std::endl;
    if (_data_array)
        delete [] _data_array;
}

template <typename T>
bool MySet<T>::isEmpty() const
{
    return !_size;
}

template <typename T>
size_t MySet<T>::getSize() const
{
    return _size;
}

template <typename T>
void MySet<T>::insert(const T &item)
{
    if (isContained(item)) {
        return;
    }

    if ( _size == _max_size) {
        // reallocate data
        MySet<T> updated_set(_max_size * 2);
        std::copy_n(_data_array, _size, updated_set._data_array);
        updated_set._size = _size;

        swap(*this, updated_set);
    }
    _data_array[_size++] = item;
}

template <typename T>
void MySet<T>::extend(const MySet<T> &other)
{
    for (size_t idx = 0; idx < other._size; ++idx) {
        insert(other._data_array[idx]);
    }
}

template <typename T>
void MySet<T>::erase(const T &item)
{
    int idx = getIndexOf(item);
    if (idx == -1)
        return;

    _data_array[idx] = _data_array[--_size];
}

template <typename T>
void MySet<T>::erase(const MySet<T> &other)
{
    for (size_t idx = 0; idx < other._size; ++idx) {
        erase(other._data_array[idx]);
    }
}

template <typename T>
void MySet<T>::intersect(const MySet<T> &other)
{
    // iterate in reverse for simple erasing
    for (size_t idx = _size - 1; idx >= 0; --idx) {
        T *item = &_data_array[idx];
        if (!other.isContained(*item)) {
            --_size;
            _data_array[idx] = _data_array[_size];
        }
    }
}

template <typename T>
std::string MySet<T>::dump() const
{
    std::ostringstream oss;
    if (!_size) {
        oss << "an empty item";
        return oss.str();
    }

    T first_item = _data_array[0];
    oss << "{ " << first_item;

    size_t second_item_index = 1;
    for (size_t idx = second_item_index; idx < _size; ++idx) {
        oss << ", " << _data_array[idx];
    }
    oss << "}";
    return oss.str();
}

template <typename T>
MySet<T> setUnion(const MySet<T> &first, const MySet<T> &second)
{
    MySet<T> set_union(first);
    set_union.extend(second);
    return set_union;
}

template <typename T>
MySet<T> setDifference(const MySet<T> &first, const MySet<T> &second)
{
    MySet<T> set_diff;
    for (size_t idx = 0; idx < first._size; ++idx) {
        // avoid copying by saving of addr
        T *first_item = &first._data_array[idx];
        if (!second.isContained(*first_item))
            set_diff.insert(*first_item);
    }

    return set_diff;
}

template <typename T>
MySet<T> setIntersection(const MySet<T> &first, const MySet<T> &second)
{
    MySet<T> intersection;
    for (size_t idx = 0; idx < first._size; ++idx) {
        // avoid copying by saving of addr
        T *first_item = &first._data_array[idx];
        if (second.isContained(*first_item))
            intersection.insert(*first_item);
    }

    return intersection;
}

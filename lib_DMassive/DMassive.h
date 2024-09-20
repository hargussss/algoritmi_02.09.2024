// Copyright 2024 Ivan Karpich

#ifndef LIB_DMASSIVE_DMASSIVE_H_
#define LIB_DMASSIVE_DMASSIVE_H_

#include <iostream>
#include <stdexcept>

#define STEP_CAPACITY 15

enum State { empty, busy, deleted };

namespace algorithms {
    template<typename T>
    inline void swap(T& val_1, T& val_2) noexcept {
        T tmp = val_1;
        val_1 = val_2;
        val_2 = tmp;
    }

    template<typename T>
    T max(T val_1, T val_2) {
        return (val_1 > val_2) ? val_1 : val_2;
    }
}

template <typename T>
class DMassiv {
    T* _data;
    State* _states;
    size_t _capacity;
    size_t _size;
    size_t _deleted;

 public:
    DMassiv();
    DMassiv(const DMassiv& archive);
    DMassiv(const T* arr, size_t n);
    DMassiv(size_t n, T value);
    DMassiv(const DMassiv& archive, size_t pos, size_t len);

    ~DMassiv();

    void print() const noexcept;

    inline bool empty() const noexcept;
    inline bool full() const noexcept;

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    const T* data() const noexcept;

    void swap(DMassiv& archive);

    void clear();
    void reserve(size_t n);
    void resize(size_t n, T value);
    void repack();

    DMassiv& assign(const DMassiv& archive);

    void push_back(T value);
    void pop_back();
    void push_front(T value);
    void pop_front();

    DMassiv& insert(const T* arr, size_t n, size_t pos);
    DMassiv& insert(T value, size_t pos);

    DMassiv& replace(size_t pos, T new_value);

    DMassiv& remove_by_index(size_t pos);
    DMassiv& erase(size_t pos, size_t n);
    DMassiv& remove_all(T value);
    DMassiv& remove_first(T value);
    DMassiv& remove_last(T value);

    size_t find_first(T value) const noexcept;
    size_t find_last(T value) const noexcept;

 private:
    void check_index(size_t pos) const;  // вспомогательная функция для проверки индекса
};

// реализация функций

template <typename T>
DMassiv<T>::DMassiv() {
    _size = 0;
    _capacity = STEP_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];
    _deleted = 0;
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}

template <typename T>
DMassiv<T>::~DMassiv() {
    delete[] _data;
    delete[] _states;
}

// функция для проверки корректности индекса
template <typename T>
void DMassiv<T>::check_index(size_t pos) const {
    if (pos >= _size) {
        throw std::out_of_range("Index out of bounds");
    }
}

template <typename T>
inline bool DMassiv<T>::empty() const noexcept {
    return _size == 0;
}

template <typename T>
inline bool DMassiv<T>::full() const noexcept {
    return _size == _capacity;
}

template <typename T>
size_t DMassiv<T>::size() const noexcept {
    return _size;
}

template <typename T>
size_t DMassiv<T>::capacity() const noexcept {
    return _capacity;
}

template <typename T>
const T* DMassiv<T>::data() const noexcept {
    return _data;
}

template <typename T>
void DMassiv<T>::swap(DMassiv& archive) {
    for (size_t i = 0; i < algorithms::max(_size, archive._size); i++) {
        algorithms::swap(_data[i], archive._data[i]);
    }
}

template <typename T>
void DMassiv<T>::clear() {
    _size = 0;
    _deleted = 0;
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}

template <typename T>
void DMassiv<T>::resize(size_t n, T value) {
    reserve(n);
    for (size_t i = _size; i < n; i++) {
        _data[i] = value;
        _states[i] = State::busy;
    }
    _size = n;
}

template <typename T>
void DMassiv<T>::push_back(T value) {
    reserve(1);
    _data[_size] = value;
    _states[_size] = State::busy;
    _size++;
}

template <typename T>
void DMassiv<T>::pop_back() {
    if (_size == 0) throw std::out_of_range("Array is empty");
    _states[_size - 1] = State::empty;
    _size--;
}

template <typename T>
DMassiv<T>& DMassiv<T>::replace(size_t pos, T new_value) {
    check_index(pos);  // проверка индекса
    _data[pos] = new_value;
    return *this;
}

template <typename T>
size_t DMassiv<T>::find_first(T value) const noexcept {
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value && _states[i] == State::busy) {
            return i;
        }
    }
    return -1;  // если не найдено
}

template <typename T>
size_t DMassiv<T>::find_last(T value) const noexcept {
    for (size_t i = _size; i > 0; i--) {
        if (_data[i - 1] == value && _states[i - 1] == State::busy) {
            return i - 1;
        }
    }
    return -1;  // если не найдено
}

#endif  // LIB_DMASSIVE_DMASSIVE_H_

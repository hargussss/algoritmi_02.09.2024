// Copyright 2024 Ivan Karpich

#ifndef LIB_DMASSIVE_DMASSIVE_H_
#define LIB_DMASSIVE_DMASSIVE_H_

#include <iostream>
#include <stdexcept>
#include <utility>
#include <algorithm>

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
    inline T max(const T& val_1, const T& val_2) {
        return (val_1 > val_2) ? val_1 : val_2;
    }
}  // namespace algorithms

template <typename T>
class DMassive {
    T* _data;
    State* _states;
    size_t _capacity;
    size_t _size;
    size_t _deleted;

 public:
    DMassive();
    DMassive(const DMassive& archive);
    DMassive(const T* arr, size_t n);
    DMassive(size_t n, T value);
    DMassive(const DMassive& archive, size_t pos, size_t len);

    ~DMassive();

    void print() const noexcept;

    inline bool empty() const noexcept;
    inline bool full() const noexcept;

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    const T* data() const noexcept;

    void swap(DMassive& archive);

    void clear();
    void reserve(size_t n);
    void resize(size_t n, T value);
    void repack();

    DMassive& assign(const DMassive& archive);

    void push_back(T value);
    void pop_back();
    void push_front(T value);
    void pop_front();

    DMassive& insert(const T* arr, size_t n, size_t pos);
    DMassive& insert(T value, size_t pos);

    DMassive& replace(size_t pos, T new_value);

    DMassive& remove_by_index(size_t pos);
    DMassive& erase(size_t pos, size_t n);
    DMassive& remove_all(T value);
    DMassive& remove_first(T value);
    DMassive& remove_last(T value);

    size_t find_first(T value) const noexcept;
    size_t find_last(T value) const noexcept;

 private:
    void check_index(size_t pos) const;  // вспомогательная функция
                                         // для проверки индекса
};

// реализация функций

template <typename T>
DMassive<T>::DMassive() {
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
DMassive<T>::~DMassive() {
    delete[] _data;
    delete[] _states;
}

// функция для проверки корректности индекса
template <typename T>
void DMassive<T>::check_index(size_t pos) const {
    if (pos >= _size) {
        throw std::out_of_range("Index out of bounds");
    }
}

template <typename T>
inline bool DMassive<T>::empty() const noexcept {
    return _size == 0;
}

template <typename T>
inline bool DMassive<T>::full() const noexcept {
    return _size == _capacity;
}

template <typename T>
size_t DMassive<T>::size() const noexcept {
    return _size;
}

template <typename T>
size_t DMassive<T>::capacity() const noexcept {
    return _capacity;
}

template <typename T>
const T* DMassive<T>::data() const noexcept {
    return _data;
}

template <typename T>
void DMassive<T>::swap(DMassive& archive) {
    for (size_t i = 0; i < algorithms::max(_size, archive._size); i++) {
        algorithms::swap(_data[i], archive._data[i]);
    }
}

template <typename T>
void DMassive<T>::clear() {
    _size = 0;
    _deleted = 0;
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}

template <typename T>
void DMassive<T>::reserve(size_t n) {
    if (_capacity >= _size + n) return;
    size_t new_capacity = _capacity + algorithms::max<size_t>(n, STEP_CAPACITY);
    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity];

    for (size_t i = 0; i < _size; i++) {
        new_data[i] = _data[i];
        new_states[i] = _states[i];
    }

    for (size_t i = _size; i < new_capacity; i++) {
        new_states[i] = State::empty;
    }

    delete[] _data;
    delete[] _states;

    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
}

template <typename T>
void DMassive<T>::resize(size_t n, T value) {
    reserve(n);
    for (size_t i = _size; i < n; i++) {
        _data[i] = value;
        _states[i] = State::busy;
    }
    _size = n;
}

template <typename T>
void DMassive<T>::push_back(T value) {
    reserve(1);
    _data[_size] = value;
    _states[_size] = State::busy;
    _size++;
}

template <typename T>
void DMassive<T>::pop_back() {
    if (_size == 0) throw std::out_of_range("Array is empty");
    _states[_size - 1] = State::empty;
    _size--;
}

template <typename T>
void DMassive<T>::push_front(T value) {
    reserve(1);
    for (size_t i = _size; i > 0; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
    _data[0] = value;
    _states[0] = State::busy;
    _size++;
}

template <typename T>
void DMassive<T>::pop_front() {
    if (_size == 0) throw std::out_of_range("Array is empty");
    for (size_t i = 0; i < _size - 1; i++) {
        _data[i] = _data[i + 1];
        _states[i] = _states[i + 1];
    }
    _size--;
    _states[_size] = State::empty;
}

template <typename T>
DMassive<T>& DMassive<T>::insert(const T* arr, size_t n, size_t pos) {
    check_index(pos);
    reserve(n);
    for (size_t i = _size + n - 1; i >= pos + n; --i) {
        _data[i] = _data[i - n];
        _states[i] = _states[i - n];
    }
    for (size_t i = 0; i < n; ++i) {
        _data[pos + i] = arr[i];
        _states[pos + i] = State::busy;
    }
    _size += n;
    return *this;
}

template <typename T>
DMassive<T>& DMassive<T>::insert(T value, size_t pos) {
    check_index(pos);
    reserve(1);
    for (size_t i = _size; i > pos; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
    _data[pos] = value;
    _states[pos] = State::busy;
    _size++;
    return *this;
}

template <typename T>
DMassive<T>& DMassive<T>::replace(size_t pos, T new_value) {
    check_index(pos);
    _data[pos] = new_value;
    return *this;
}

template <typename T>
DMassive<T>& DMassive<T>::remove_by_index(size_t pos) {
    check_index(pos);

    // Помечаем элемент как удалённый
    _states[pos] = State::deleted;
    _deleted++;

    // Сдвигаем элементы, если удалённый элемент не последний
    if (pos != _size - 1) {
        for (size_t i = pos; i < _size - 1; ++i) {
            _data[i] = _data[i + 1];
            _states[i] = _states[i + 1];
        }
    }

    // Уменьшаем размер массива
    _size--;

    return *this;
}

template <typename T>
DMassive<T>& DMassive<T>::erase(size_t pos, size_t n) {
    for (size_t i = 0; i < n; i++) {
        remove_by_index(pos + i);
    }
    return *this;
}

template <typename T>
DMassive<T>& DMassive<T>::remove_all(T value) {
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value && _states[i] == State::busy) {
            remove_by_index(i);
        }
    }
    return *this;
}

template <typename T>
DMassive<T>& DMassive<T>::remove_first(T value) {
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value && _states[i] == State::busy) {
            remove_by_index(i);
            break;
        }
    }
    return *this;
}

template <typename T>
DMassive<T>& DMassive<T>::remove_last(T value) {
    for (size_t i = _size; i > 0; i--) {
        if (_data[i] == value && _states[i] == State::busy) {
            remove_by_index(i);
            break;
        }
    }
    return *this;
}

template <typename T>
size_t DMassive<T>::find_first(T value) const noexcept {
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value && _states[i] == State::busy) return i;
    }
    return static_cast<size_t>(-1);
}

template <typename T>
size_t DMassive<T>::find_last(T value) const noexcept {
    for (size_t i = _size - 1; i >= 0; i--) {
        if (_data[i] == value && _states[i] == State::busy) return i;
    }
    return static_cast<size_t>(-1);
}

template <typename T>
DMassive<T>::DMassive(const DMassive& archive) {
    _capacity = archive._capacity;
    _size = archive._size;
    _deleted = archive._deleted;
    _data = new T[_capacity];
    _states = new State[_capacity];

    for (size_t i = 0; i < _capacity; i++) {
        _data[i] = archive._data[i];
        _states[i] = archive._states[i];
    }
}

template <typename T>
void DMassive<T>::repack() {
    if (_deleted == 0) return;

    size_t new_size = 0;
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] == State::busy) {
            _data[new_size] = _data[i];
            _states[new_size] = _states[i];
            new_size++;
        }
    }
    _size = new_size;
    _deleted = 0;
}

#endif  // LIB_DMASSIVE_DMASSIVE_H_

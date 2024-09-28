// Copyright 2024 Ivan Karpich

#ifndef LIB_QUEUE_QUEUE_H_
#define LIB_QUEUE_QUEUE_H_

#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {
 private:
    T* _data;
    size_t _size;
    size_t _front;
    size_t _rear;
    size_t _count;

 public:
    explicit Queue(size_t size)
    : _size(size),
      _front(0),
      _rear(size - 1),
      _count(0) {
        _data = new T[_size];
    }

    ~Queue() {
        delete[] _data;
    }

    //  метод для добавления элемента в очередь
    void enqueue(const T& value) {
        if (_count == _size) {
            throw std::overflow_error("Queue overflow");
        }
        _rear = (_rear + 1) % _size;
        // перемещаем индекс последнего элемента
        _data[_rear] = value;
        ++_count;
    }

    //  метод для удаления элемента из очереди
    T dequeue() {
        if (_count == 0) {
            throw std::underflow_error("Queue underflow");
        }
        T value = _data[_front];
        _front = (_front + 1) % _size;   //  передвигаем индекс первого элемента
        --_count;
        return value;
    }

    //  метод для получения первого элемента без удаления
    T front() const {
        if (_count == 0) {
            throw std::underflow_error("Queue is empty");
        }
        return _data[_front];
    }

    //  метод для проверки, пуста ли очередь
    bool isEmpty() const {
        return _count == 0;
    }

    //  метод для получения текущего размера очереди
    size_t size() const {
        return _count;
    }
};

#endif  // LIB_QUEUE_QUEUE_H_

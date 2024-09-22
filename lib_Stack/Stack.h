// Copyright 2024 Ivan Karpich

#ifndef LIB_STACK_STACK_H_
#define LIB_STACK_STACK_H_

#include <iostream>
#include <stdexcept>

template <typename T>
class TStack {
private:
    T* _data;          //  массив для хранения элементов стека
    size_t _size;      //  максимальный размер стека
    size_t _top;       //  индекс верхнего элемента стека

public:
    explicit TStack(size_t size) : _size(size), _top(0) {
        _data = new T[_size];
    }

    ~TStack() {
        delete[] _data;
    }

    //  метод для добавления элемента в стек
    void push(const T& value) {
        if (_top >= _size) {
            throw std::overflow_error("Stack overflow");
        }
        _data[_top++] = value;
    }

    //  метод для удаления элемента из стека
    T pop() {
        if (_top == 0) {
            throw std::underflow_error("Stack underflow");
        }
        return _data[--_top];
    }

    //  метод для получения верхнего элемента без удаления
    T top() const {
        if (_top == 0) {
            throw std::underflow_error("Stack is empty");
        }
        return _data[_top - 1];
    }

    //  метод для проверки, пуст ли стек
    bool isEmpty() const {
        return _top == 0;
    }

    //  метод для получения текущего размера стека
    size_t size() const {
        return _top;
    }
};

#endif // LIB_STACK_STACK_H_

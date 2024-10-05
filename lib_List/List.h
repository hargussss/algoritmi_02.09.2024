// Copyright 2024 Ivan Karpich

#ifndef LIB_LIST_LIST_H_
#define LIB_LIST_LIST_H_

#include <iostream>
#include <stdexcept>

template <class T>
class TNode {
    T _value;
    TNode<T>* _pnext;

 public:
    explicit TNode(T value) : _value(value), _pnext(nullptr) {}
    TNode(const TNode& other) = default;
    ~TNode() = default;

    TNode<T>& operator=(const TNode<T>& other) = default;
    bool operator==(const TNode<T>& other) const {
        return _value == other._value;
    }

    T getValue() const { return _value; }
    void setValue(T value) { _value = value; }

    TNode<T>* getNext() const { return _pnext; }
    void setNext(TNode<T>* next) { _pnext = next; }

    friend std::ostream& operator<<(std::ostream& os, const TNode<T>& node) {
        os << node._value;
        return os;
    }
};

template <class T>
class TList {
    TNode<T>* _head;
    TNode<T>* _tail;

 public:
    TList() : _head(nullptr), _tail(nullptr) {}
    ~TList();

    void insertFront(T value);
    void insertBack(T value);
    void insertAfter(TNode<T>* node, T value);
    void insertAt(int pos, T value);

    TNode<T>* find(T value) const;

    void removeFront();
    void removeBack();
    void removeAt(int pos);
    void removeNode(TNode<T>* node);

    void replaceNode(TNode<T>* node, T value);
    void replaceAt(int pos, T value);

    bool isEmpty() const { return _head == nullptr; }

    TList<T>& operator=(const TList<T>& other);

    friend std::ostream& operator<<(std::ostream& os, const TList<T>& list) {
        TNode<T>* current = list._head;
        while (current) {
            os << *current << " -> ";
            current = current->getNext();
        }
        os << "null";
        return os;
    }
};

template <class T>
TList<T>::~TList() {
    while (!isEmpty()) {
        removeFront();
    }
}

// вставка в начало списка
template <class T>
void TList<T>::insertFront(T value) {
    TNode<T>* newNode = new TNode<T>(value);
    newNode->setNext(_head);
    _head = newNode;
    if (!_tail) {
        _tail = _head;
    }
}

// вставка в конец списка
template <class T>
void TList<T>::insertBack(T value) {
    TNode<T>* newNode = new TNode<T>(value);
    if (isEmpty()) {
        _head = _tail = newNode;
    } else {
        _tail->setNext(newNode);
        _tail = newNode;
    }
}

// вставка после указанного узла
template <class T>
void TList<T>::insertAfter(TNode<T>* node, T value) {
    if (!node) {
        throw std::invalid_argument("Node cannot be null");
    }
    TNode<T>* newNode = new TNode<T>(value);
    newNode->setNext(node->getNext());
    node->setNext(newNode);
    if (node == _tail) {
        _tail = newNode;
    }
}

// вставка на указанную позицию
template <class T>
void TList<T>::insertAt(int pos, T value) {
    if (pos < 0) {
        throw std::out_of_range("Position cannot be negative");
    }
    if (pos == 0) {
        insertFront(value);
        return;
    }

    TNode<T>* current = _head;
    for (int i = 0; i < pos - 1 && current; ++i) {
        current = current->getNext();
    }
    if (!current) {
        throw std::out_of_range("Position out of range");
    }

    insertAfter(current, value);
}

// поиск по значению
template <class T>
TNode<T>* TList<T>::find(T value) const {
    TNode<T>* current = _head;
    while (current) {
        if (current->getValue() == value) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

// удаление из начала списка
template <class T>
void TList<T>::removeFront() {
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    TNode<T>* oldHead = _head;
    _head = _head->getNext();
    if (!_head) {
        _tail = nullptr;
    }
    delete oldHead;
}

// удаление из конца списка
template <class T>
void TList<T>::removeBack() {
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    if (_head == _tail) {
        delete _head;
        _head = _tail = nullptr;
        return;
    }

    TNode<T>* current = _head;
    while (current->getNext() != _tail) {
        current = current->getNext();
    }

    delete _tail;
    _tail = current;
    _tail->setNext(nullptr);
}

// удаление по позиции
template <class T>
void TList<T>::removeAt(int pos) {
    if (pos < 0 || isEmpty()) {
        throw std::out_of_range("Invalid position or list is empty");
    }
    if (pos == 0) {
        removeFront();
        return;
    }

    TNode<T>* current = _head;
    for (int i = 0; i < pos - 1 && current; ++i) {
        current = current->getNext();
    }
    if (!current || !current->getNext()) {
        throw std::out_of_range("Position out of range");
    }

    removeNode(current->getNext());
}

// удаление указанного узла
template <class T>
void TList<T>::removeNode(TNode<T>* node) {
    if (isEmpty() || !node) {
        throw std::invalid_argument("Invalid node or list is empty");
    }
    if (node == _head) {
        removeFront();
        return;
    }

    TNode<T>* current = _head;
    while (current && current->getNext() != node) {
        current = current->getNext();
    }
    if (!current) {
        throw std::invalid_argument("Node not found");
    }

    current->setNext(node->getNext());
    if (node == _tail) {
        _tail = current;
    }
    delete node;
}

// замена значения указанного узла
template <class T>
void TList<T>::replaceNode(TNode<T>* node, T value) {
    if (!node) {
        throw std::invalid_argument("Node cannot be null");
    }
    node->setValue(value);
}

// замена значения по позиции
template <class T>
void TList<T>::replaceAt(int pos, T value) {
    if (pos < 0) {
        throw std::out_of_range("Position cannot be negative");
    }

    TNode<T>* current = _head;
    for (int i = 0; i < pos && current; ++i) {
        current = current->getNext();
    }
    if (!current) {
        throw std::out_of_range("Position out of range");
    }

    current->setValue(value);
}

// оператор присваивания
template <class T>
TList<T>& TList<T>::operator=(const TList<T>& other) {
    if (this == &other) {
        return *this;
    }

    while (!isEmpty()) {
        removeFront();
    }

    TNode<T>* current = other._head;
    while (current) {
        insertBack(current->getValue());
        current = current->getNext();
    }

    return *this;
}

#endif  // LIB_LIST_LIST_H_

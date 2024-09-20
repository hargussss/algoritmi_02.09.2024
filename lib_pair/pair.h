// Copyright 2024 Ivan Karpich

#ifndef LIB_PAIR_PAIR_H_
#define LIB_PAIR_PAIR_H_

#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
#include <utility>

template <typename T1, typename T2>
class TPair {
 private:
    T1 _first;
    T2 _second;

 public:
    // конструкторы
    TPair();
    TPair(const T1& first, const T2& second);
    TPair(T1&& first, T2&& second) noexcept;
    TPair(const TPair& other);
    TPair(TPair&& other) noexcept;

    // геттеры и сеттеры
    T1 first() const noexcept;
    T2 second() const noexcept;
    void set_first(const T1& value) noexcept;
    void set_second(const T2& value) noexcept;

    // операторы
    TPair& operator=(const TPair& other) noexcept;
    TPair& operator=(TPair&& other) noexcept;
    bool operator==(const TPair& other) const noexcept;
    bool operator!=(const TPair& other) const noexcept;
    bool operator<(const TPair& other) const noexcept;
    bool operator>(const TPair& other) const noexcept;
    bool operator<=(const TPair& other) const noexcept;
    bool operator>=(const TPair& other) const noexcept;

    // арифметические операции
    TPair operator+(const TPair& other) const noexcept;
    TPair operator-(const TPair& other) const noexcept;

    std::string to_string() const noexcept;

    // вывод в поток
    template <typename U1, typename U2>
    friend std::ostream& operator<<(
        std::ostream& os,
        const TPair<U1, U2>& pair);
};

// конструкторы и деструкторы
template <typename T1, typename T2>
TPair<T1, T2>::TPair() : _first(T1()), _second(T2()) { }

template <typename T1, typename T2>
TPair<T1, T2>::TPair(const T1& first, const T2& second)
    : _first(first), _second(second) { }

template <typename T1, typename T2>
TPair<T1, T2>::TPair(T1&& first, T2&& second) noexcept
    : _first(std::move(first)), _second(std::move(second)) { }

template <typename T1, typename T2>
TPair<T1, T2>::TPair(const TPair& other) : _first(other._first),
    _second(other._second) { }

template <typename T1, typename T2>
TPair<T1, T2>::TPair(TPair&& other) noexcept
    : _first(std::move(other._first)), _second(std::move(other._second)) { }

// геттеры и сеттеры
template <typename T1, typename T2>
T1 TPair<T1, T2>::first() const noexcept { return _first; }

template <typename T1, typename T2>
T2 TPair<T1, T2>::second() const noexcept { return _second; }

template <typename T1, typename T2>
void TPair<T1, T2>::set_first(const T1& value) noexcept { _first = value; }

template <typename T1, typename T2>
void TPair<T1, T2>::set_second(const T2& value) noexcept { _second = value; }

// операторы
template <typename T1, typename T2>
TPair<T1, T2>& TPair<T1, T2>::operator=(const TPair& other) noexcept {
    if (this != &other) {
        _first = other._first;
        _second = other._second;
    }
    return *this;
}

template <typename T1, typename T2>
TPair<T1, T2>& TPair<T1, T2>::operator=(TPair&& other) noexcept {
    if (this != &other) {
        _first = std::move(other._first);
        _second = std::move(other._second);
    }
    return *this;
}

template <typename T1, typename T2>
bool TPair<T1, T2>::operator==(const TPair& other) const noexcept {
    return (_first == other._first && _second == other._second);
}

template <typename T1, typename T2>
bool TPair<T1, T2>::operator!=(const TPair& other) const noexcept {
    return !(*this == other);
}

template <typename T1, typename T2>
bool TPair<T1, T2>::operator<(const TPair& other) const noexcept {
    return (_first < other._first) ||
        (_first == other._first && _second < other._second);
}

template <typename T1, typename T2>
bool TPair<T1, T2>::operator>(const TPair& other) const noexcept {
    return other < *this;
}

template <typename T1, typename T2>
bool TPair<T1, T2>::operator<=(const TPair& other) const noexcept {
    return !(*this > other);
}

template <typename T1, typename T2>
bool TPair<T1, T2>::operator>=(const TPair& other) const noexcept {
    return !(*this < other);
}

#endif  // LIB_PAIR_PAIR_H_
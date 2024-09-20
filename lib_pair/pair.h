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

#endif  // LIB_PAIR_PAIR_H_
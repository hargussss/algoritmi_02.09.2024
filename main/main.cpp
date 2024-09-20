// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
// #define TPAIR_EXAMPLE

#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#elif defined(TPAIR_EXAMPLE)

#include <iostream>
#include "../lib_pair/pair.h"

int main() {
    // создание объектов TPair
    TPair<int, double> p1(1, 2.5);
    TPair<int, double> p2(3, 4.5);

    // демонстрация работы методов и операторов
    std::cout << "Pair 1: " << p1 << std::endl;
    std::cout << "Pair 2: " << p2 << std::endl;

    // операции
    TPair<int, double> p3 = p1 + p2;
    TPair<int, double> p4 = p2 - p1;

    std::cout << "Pair 1 + Pair 2: " << p3 << std::endl;
    std::cout << "Pair 2 - Pair 1: " << p4 << std::endl;

    // сравнения
    if (p1 == p2) {
        std::cout << "Pair 1 is equal to Pair 2" << std::endl;
    } else {
        std::cout << "Pair 1 is not equal to Pair 2" << std::endl;
    }

    if (p1 < p2) {
        std::cout << "Pair 1 is less than Pair 2" << std::endl;
    }

    return 0;
}

#endif  // EASY_EXAMPLE

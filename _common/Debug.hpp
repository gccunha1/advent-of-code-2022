#pragma once
#include <iostream>

template <class T> void PrintIterable(T iterable) {
    for (auto x : iterable) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}
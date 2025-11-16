#pragma once
#include <vector>
#include <random>
#include <algorithm>

class ArrayGenerator {
    std::mt19937 gen;

public:
    ArrayGenerator() : gen(std::random_device{}()) {}
    std::vector<int> randomArray(int n, int maxVal = 10000) {
        std::uniform_int_distribution<int> dist(0, maxVal);
        std::vector<int> a(n);
        for (int &x : a) x = dist(gen);
        return a;
    }
    std::vector<int> reverseArray(int n) {
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i)
            a[i] = n - i;
        return a;
    }
    std::vector<int> almostSorted(int n) {
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i)
            a[i] = i;
        std::uniform_int_distribution<int> dist(0, n - 1);
        for (int k = 0; k < 10; ++k)
            std::swap(a[dist(gen)], a[dist(gen)]);
        return a;
    }
};

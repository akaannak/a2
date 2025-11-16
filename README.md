# Анализ MERGE+INSERTION SORT

## ID посылки: 348895156
## Github: https://github.com/akaannak/a2

### arraygenerator.hpp - генерация тестовых массивов.
### mergesort.hpp - гибридный MergeSort (Merge + Insertion)
### puremerge.hpp - чистый рекурсивный MergeSort
### plot_random.png - график времени работы алгоритмов для случайных массивов
### plot_reverse.png - график времени для обратных (убывающих) массивов
### plot_almost.png - график времени для почти отсортированных массивов
### plots.py - читает csv-файлы, строит графики, сохраняет их в png
### results_pure.csv pезультаты чистого MergeSort
### results_hybrid_thr5.csv - результаты для массива из 5 элементов для гибридного MergeSort
### results_hybrid_thr10.csv - результаты для массива из 10 элементов для гибридного MergeSort
### results_hybrid_thr20.csv - результаты для массива из 20 элементов для гибридного MergeSort
### results_hybrid_thr30.csv - результаты для массива из 30 элементов для гибридного MergeSort
### results_hybrid_thr50.csv - результаты для массива из 50 элементов для гибридного MergeSort
### sorttester - бинарник
### sorttester.cpp - главный файл

# ArrayGenerator
```cpp
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
```

# SortTester
```cpp
#include <iostream>
#include <fstream>
#include <chrono>
#include "arraygenerator.hpp"
#include "puremerge.hpp"
#include "mergesort.hpp"


long timePure(const std::vector<int>& base) {
    std::vector<int> a = base, b(a.size());
    auto t1 = std::chrono::high_resolution_clock::now();
    mergeSortPure(a, b, 0, a.size());
    auto t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
}

long timeHybrid(const std::vector<int>& base, int thr) {
    std::vector<int> a = base, b(a.size());
    auto t1 = std::chrono::high_resolution_clock::now();
    mergeSort(a, b, 0, a.size(), thr);
    auto t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
}

int main() {
    ArrayGenerator gen;

    std::vector<int> Ns;
    for (int n = 500; n <= 100000; n += 500)
        Ns.push_back(n);

    std::ofstream pure("results_pure.csv");
    pure << "N,random,reverse,almost\n";

    for (int n : Ns) {
        pure << n << ","
             << timePure(gen.randomArray(n)) << ","
             << timePure(gen.reverseArray(n)) << ","
             << timePure(gen.almostSorted(n)) << "\n";
    }

    std::vector<int> thresholds = {5, 10, 20, 30, 50};

    for (int thr : thresholds) {
        std::string fname = "results_hybrid_thr" + std::to_string(thr) + ".csv";
        std::ofstream out(fname);

        for (int n : Ns) {
            out << n << ","
                << timeHybrid(gen.randomArray(n), thr) << ","
                << timeHybrid(gen.reverseArray(n), thr) << ","
                << timeHybrid(gen.almostSorted(n), thr) << "\n";
        }
    }

    return 0;
}
```

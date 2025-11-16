# Анализ MERGE+INSERTION SORT

## ID посылки: 348900836
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

# Эмпирический анализ
Были проведены запуски (эксперименты) для оценки времени работы гибридного алгоритма MergeSort, в котором:
- обычный MergeSort используется для крупных подмассивов,
- а при достижении размера ≤ threshold ({5, 10, 20, 30, 50}) применяется Insertion Sort
Это проводилось на трёх типах массивов:
- Random (полностью случайные данные)
- Reverse (строго убывающие данные)
- Almost sorted (почти отсортированные массивы)
Для каждого размера массива:
N = 500, 1000, 1500, … , 100000
были выполнены:
- замеры чистого MergeSort: results_pure.csv
- замеры гибридного MergeSort: results_hybrid_thrX.csv для всех X

# Немного о CSV-файлах
Структура:
N — размер массива
random — время сортировки случайного массива (в микросекундах)
reverse — время сортировки убывающего массива
almost — время сортировки почти отсортированного массива
Создаётся 6 CSV-файлов:
- results_pure.csv — чистый MergeSort
- results_hybrid_thr5.csv
- results_hybrid_thr10.csv
- results_hybrid_thr20.csv
- results_hybrid_thr30.csv
- results_hybrid_thr50.csv
Они дальше используются для plots.py, который строит графики.

# Сравнительный анализ результатов
## Random
<img width="2400" height="1200" alt="plot_random" src="https://github.com/user-attachments/assets/30b72eca-b806-490a-91ad-b250d4cbf08a" />

- все гибридные варианты работают быстрее чистого MergeSort
- особенно хороши T=20 и T=30
- они почти всегда ниже синей линии Pure MergeSort
- порог T=5 и T=10 тоже быстрее, но иногда дают небольшие всплески
- при больших N тенденции сохраняются: гибрид стабильно быстрее

Вывод: Гибрид обгоняет MergeSort при любом пороге T, но оптимальный диапазон — около 20–30. T=50 уже не даёт преимущества и иногда даже замедляет отдельные пики.

## Reverse
<img width="2400" height="1200" alt="plot_reverse" src="https://github.com/user-attachments/assets/9e7c0027-225e-4ac9-b8ed-e20600da7de5" />

- на полностью обратных массивах все гибриды также быстрее чистой версии
- линии разных T почти накладываются друг на друга
- Pure MergeSort (синяя линия) периодически даёт высокие пики, тогда как гибридные версии — нет
- 20 и 30 снова дают самые ровные графики

Вывод: На худшем входе гибрид ещё сильнее опережает чистую версию. Оптимальная зона T=20–30.

## Almost sorted
<img width="2400" height="1200" alt="plot_almost" src="https://github.com/user-attachments/assets/baed42f6-a8cf-4ef5-bc5b-b4c95ea47e51" />

- поведение схоже со случайным массивом
- при T=50 появляются большие пики

Вывод: Оптимальный порог — T ≈ 20.

## Основной вывод
Гибрид всегда работает быстрее или не хуже чистого MergeSort, он снижает число дорогостоящих операций слияния, имеет оптимальную область порогов 20–30 элементов. После T > 30 алгоритм начинает замедляться, так как Insertion Sort применяется слишком часто и сортирует слишком большие куски. Оптимальный threshold: T = 20–30

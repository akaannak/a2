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

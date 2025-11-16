#pragma once
#include <vector>

void mergePure(std::vector<int>& a, int left, int mid, int right, std::vector<int>& b) {
    int i = left;
    int j = mid;
    int k = left;

    while (i < mid && j < right) {
        if (a[i] <= a[j]) {
            b[k++] = a[i++];
        } else {
            b[k++] = a[j++];
        }
    }
    while (i < mid) {
        b[k++] = a[i++];
    }
    while (j < right) {
        b[k++] = a[j++];
    }

    for (int i = left; i < right; ++i) {
        a[i] = b[i];
    }
}

void mergeSortPure(std::vector<int>& a, std::vector<int>& b, int left, int right) {
    if (right - left <= 1) {
        return;
    }

    int mid = (left + right) / 2;

    mergeSortPure(a, b, left, mid);
    mergeSortPure(a, b, mid, right);
    mergePure(a, left, mid, right, b);
}

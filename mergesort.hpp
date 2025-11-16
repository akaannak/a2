#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <random>
#include <iomanip>

void insertion(std::vector<int>& a, int left, int right) {
    for (int i = left + 1; i < right; ++i) {
        int value = a[i];
        int j = i - 1;
        while (j >= left && a[j] > value) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = value;
    }
}

void merge(std::vector<int>& a, int left, int mid, int right, std::vector<int>& b) {
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

void mergeSort(std::vector<int>& a, std::vector<int>& b, int left, int right, int THR) {
    if (right - left <= 1) {
        return;
    }
    if (right - left <= 15) {
        insertion(a, left, right);
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(a, b, left, mid, THR);
    mergeSort(a, b, mid, right, THR);
    merge(a, left, mid, right, b);
}

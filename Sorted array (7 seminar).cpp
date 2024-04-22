/*2)Используя многопоточное программирование, отсортировать массив*/

#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

// Функция для сортировки части массива в отдельном потоке
void partialSort(std::vector<int>& arr, size_t start, size_t end) {
    std::sort(arr.begin() + start, arr.begin() + end);
}

// Функция для объединения отсортированных частей массива
void merge(std::vector<int>& arr, size_t start, size_t mid, size_t end) {
    std::vector<int> temp(end - start);
    size_t i = start, j = mid, k = 0;

    while (i < mid && j < end) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i < mid)
        temp[k++] = arr[i++];
    while (j < end)
        temp[k++] = arr[j++];

    std::copy(temp.begin(), temp.end(), arr.begin() + start);
}

// Функция для многопоточной сортировки массива
void parallelMergeSort(std::vector<int>& arr, size_t start, size_t end, int numThreads) {
    if (end - start < 2)
        return;

    if (numThreads <= 1 || end - start < 1000) {
        std::sort(arr.begin() + start, arr.begin() + end);
    } else {
        size_t mid = start + (end - start) / 2;
        std::thread leftThread(parallelMergeSort, std::ref(arr), start, mid, numThreads / 2);
        std::thread rightThread(parallelMergeSort, std::ref(arr), mid, end, numThreads / 2);
        leftThread.join();
        rightThread.join();
        merge(arr, start, mid, end);
    }
}

int main() {
    std::vector<int> arr = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int numThreads = std::thread::hardware_concurrency();

    parallelMergeSort(arr, 0, arr.size(), numThreads);

    std::cout << "Sorted array: ";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}
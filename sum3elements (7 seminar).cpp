/*1) Используя многопоточное программирование, 
найти сумму 3 самых больших элементов массива, 
заполненного случайными числами*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <thread>
#include <future>

// Функция для генерации случайного массива
std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);

    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }

    return arr;
}

// Функция для нахождения суммы трех самых больших элементов в массиве
int findTop3Sum(const std::vector<int>& array) {
    std::vector<int> sortedArray = array; // Создаем копию массива
    std::sort(sortedArray.begin(), sortedArray.end(), std::greater<int>()); // Сортируем массив по убыванию
    int sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += sortedArray[i]; // Суммируем три самых больших элемента
    }
    return sum;
}

int main() {
    const int arraySize = 100;
    const int numThreads = 4;

    // Генерируем случайный массив
    std::vector<int> arr = generateRandomArray(arraySize);

    // Создаем вектор будущих результатов для каждого потока
    std::vector<std::future<int>> futures(numThreads);

    // Разбиваем массив на части для обработки в нескольких потоках
    int chunkSize = arraySize / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        std::vector<int> chunk(arr.begin() + i * chunkSize, arr.begin() + (i + 1) * chunkSize);
        futures[i] = std::async(std::launch::async, findTop3Sum, chunk);
    }

    // Собираем результаты из потоков
    int totalSum = 0;
    for (auto& future : futures) {
        totalSum += future.get(); // Получаем результаты из каждого потока и суммируем их
    }

    std::cout << "Sum of the three biggest: " << totalSum << std::endl;

    return 0;
}
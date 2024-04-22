/*1) ��������� ������������� ����������������, 
����� ����� 3 ����� ������� ��������� �������, 
������������ ���������� �������*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <thread>
#include <future>

// ������� ��� ��������� ���������� �������
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

// ������� ��� ���������� ����� ���� ����� ������� ��������� � �������
int findTop3Sum(const std::vector<int>& array) {
    std::vector<int> sortedArray = array; // ������� ����� �������
    std::sort(sortedArray.begin(), sortedArray.end(), std::greater<int>()); // ��������� ������ �� ��������
    int sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += sortedArray[i]; // ��������� ��� ����� ������� ��������
    }
    return sum;
}

int main() {
    const int arraySize = 100;
    const int numThreads = 4;

    // ���������� ��������� ������
    std::vector<int> arr = generateRandomArray(arraySize);

    // ������� ������ ������� ����������� ��� ������� ������
    std::vector<std::future<int>> futures(numThreads);

    // ��������� ������ �� ����� ��� ��������� � ���������� �������
    int chunkSize = arraySize / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        std::vector<int> chunk(arr.begin() + i * chunkSize, arr.begin() + (i + 1) * chunkSize);
        futures[i] = std::async(std::launch::async, findTop3Sum, chunk);
    }

    // �������� ���������� �� �������
    int totalSum = 0;
    for (auto& future : futures) {
        totalSum += future.get(); // �������� ���������� �� ������� ������ � ��������� ��
    }

    std::cout << "Sum of the three biggest: " << totalSum << std::endl;

    return 0;
}
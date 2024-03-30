/*1) ����������� ��������� � 10 000 ���������� (�� ����������������) ����������.  ����������� 2 ���� ����������. 
��������, ����� �������. ��������� ������ �������� ����� � �������� �������� ������� ����������.*/

#include <iostream>
#include <vector>
#include <ctime>
#include<chrono>

// ��������� ��������������� ����� �� 0 �� 9999
int getRandomNumber()
{
    return rand() % 10000;
}

// ���������� ���������
void bubbleSort(std::vector<int>& array)
{
    int n = array.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (array[j] > array[j + 1])
            {
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

// ���������� ��������
void insertSort(std::vector<int>& array)
{
    int n = array.size();
    for (int i = 1; i < n; ++i)
    {
        int current = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > current)
        {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = current;
    }
}

int main()
{
    srand(time(0)); // ��������� ��������� ����� ������ ������� �� �������

    std::vector<int> container(10000);

    // ���������� ���������� ���������� �������
    for (int i = 0; i < 10000; ++i)
    {
        container[i] = getRandomNumber();
    }

    // ��������� ������� ���������� ����������
    auto start_time = std::chrono::high_resolution_clock::now();

    bubbleSort(container);

    auto end_time = std::chrono::high_resolution_clock::now();

    auto time_bubble = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "bubble sort insert time: " << time_bubble << " microseconds" << std::endl;

    start_time = std::chrono::high_resolution_clock::now();

    insertSort(container);

    end_time = std::chrono::high_resolution_clock::now();

    auto time_insert = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "insert sort insert time: " << time_insert << " microseconds" << std::endl;

 // �������� ����� ������� ����������
    if (time_bubble < time_insert)
    {
        std::cout << "bubble sort is faster (" << time_bubble << " microseconds)" << std::endl;
    }
    else
    {
        std::cout << "insert sort is faster (" << time_insert << " microseconds)" << std::endl;
    }

    return 0;
}
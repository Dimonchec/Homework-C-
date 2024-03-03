/*Бинарный поиск
Реализуйте функцию бинарного поиска в отсортированном по возрастанию массиве.
Если объект есть в массиве, функция должна вернуть его индекс, иначе — вернуть -1.
*/

#include <iostream>

int Search(int array[], int length, int i) {
    int left = 0;
    int right = length - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == i) 
        {
            return mid; // объект найден
        }
        else if (array[mid] < i) 
        {
            left = mid + 1;  // объект находится в правой половине
        }
        else
        {
            right = mid - 1; // объект находится в левой половине
        }
    }

    return -1; // объект не найден
}

int main() 
{
    int array[] {1, 2, 3, 4, 5, 6, 7};
    int length = sizeof(array) / sizeof(array[0]);
    int i = 3;

    int index = Search(array, length, i);

    if (index != -1) {
        std::cout << "Найден номер объекта  " << index << std::endl;
    }
    else {
        std::cout << "Объект не найден" << std::endl;
    }

    return 0;
}
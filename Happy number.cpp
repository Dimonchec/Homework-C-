/*Счастливые числа.
Определим последовательность натуральных чисел рекурсивно: следующее число
равно сумме квадратов цифр текущего числа. Если последовательность придёт к 1, то
начальное число последовательности называется счастливым. Например, 19 —
счастливое число (последовательность 19 -> 82 -> 68 -> 100 -> 1), а число 2 — нет
(последовательность 2 -> 4 -> 16 -> 37 -> 18 -> 65 -> 61 -> 37 -> ...).
Напишите функцию, проверяющую, является ли переданное ей натуральное число
счастливым.*/

#include <iostream>


int Count(int num) 
{
    int sum = 0;
    while (num > 0) 
    {
        int symbol = num % 10;
        sum += symbol * symbol;
        num /= 10;
    }
    return sum;
}


void HappyNumber(int num)
{
    
    while (num > 243)
    {
        num = Count(num);
    }

    
    for (int i = 0; i < 244; i++)
    {
        if (num == 1)
        {
            std::cout << "Happy number" << std::endl;
            exit(0);
        }
        num = Count(num);
    }
    std::cout << "No happy number" << std::endl;
    exit(0);
}

int main()
{
	int num = 0;
	std::cout << "enter a number" << std::endl;
	std::cin >> num;
	HappyNumber(num);
}
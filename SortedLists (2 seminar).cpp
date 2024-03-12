/*2) Составить программу, которая на основе заданного списка формирует два других, помещая в первый из них положительные,
а во второй — отрицательные элементы исходного списка, сортируя их по возрастанию при заполнении.
*/

#include <iostream>
#include <list>
#include <algorithm>


void Separate(const std::list<int>& bas, std::list<int>& pos, std::list<int>& neg)
{
    for (int elem : bas)
    {
        if (elem >= 0)
        {
            pos.push_back(elem);
        }
        else
        {
            neg.push_back(elem);
        }
    }
   
    pos.sort();
    neg.sort();
}

int main()
{
    std::list<int> list = { -7, 4, 5, -17, 1,-1 };
    std::list<int> poslist;
    std::list<int> neglist;

    Separate(list, poslist, neglist);

    std::cout << "Positive elements: ";
    for (int elem : poslist)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "Negative elements: ";
    for (int elem : neglist)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
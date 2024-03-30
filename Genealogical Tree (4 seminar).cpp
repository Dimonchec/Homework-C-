/*2) С помощью ассоциативного контейнера реализовать генеалогическое древо
 Каждом элементу дерева сопоставляется целое неотрицательное число, называемое высотой. 
 У родоначальника высота равна 0, у любого другого элемента высота на 1 больше, чем у его родителя.

Вам дано генеалогическое древо, определите высоту всех его элементов.*/


#include <iostream>
#include <map>
#include <string>

// Класс дерева
class GenealogicalTree
{
private:
    std::map<std::string, std::string> parent; // Потомок : Родитель
    std::map<std::string, int> height;         // Потомок : Высота

public:
    // Связь
    void relation(const std::string& child, const std::string& parent)
    {
        this->parent[child] = parent;
    }

    // Рекурсивная функция перебора
    int calculateHeight(const std::string& child)
    {
        if (!parent.count(child))
        {
            height[child] = 0;
            return 0;
        }
        int current = calculateHeight(parent[child]) + 1;
        height[child] = current;
        return current;
    }

    // Считаем высоту
    void Height()
    {
        for (const auto& pair : parent)
        {
            if (!height.count(pair.first))
            {
                calculateHeight(pair.first);
            }
        }
    }

    // Печатаем дерево
    void printTree()
    {
        for (const auto& pair : height)
        {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }
};


int main()
{
    int numberOfReletives = 9;
    GenealogicalTree gTree;
    std::map<std::string, std::string> relatives = { { "Alexei", "Peter_I" }     , { "Anna", "Peter_I" }
                                                   , { "Elizabeth", "Peter_I" }  , { "Peter_II", "Alexei" }
                                                   , { "Peter_III", "Anna" }     , { "Paul_I", "Peter_III" }
                                                   , { "Alexander_I", "Paul_I" } , { "Nicholaus_I", "Paul_I" } };

    for (const auto pair : relatives)
    {
        gTree.relation(pair.first, pair.second);
    }

    gTree.Height();
    gTree.printTree();

    return 0;
}
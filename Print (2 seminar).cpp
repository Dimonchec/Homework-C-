/*1) Условие
Вам надо написать функцию аналогичную Print, 
которая умеет печатать в поток std::cout элементы переданного контейнера через указанную строку - разделитель.
Первый аргумент функции — контейнер.Гарантируется, что по этому контейнеру можно проитерироваться с помощью 
стандартного цикла range - based for, и что элементы контейнера можно напечатать в поток std::cout 
с помощью стандартного оператора << .Второй аргумент функции — строка - разделитель,
которую надо печатать между элементами.В конце необходимо напечатать перевод строки \n.

Пример вызова :
int main() {
    std::vector<int> data = { 1, 2, 3 };
    Print(data, ", ");  // 1, 2, 3
}
*/



#include <iostream>
#include <vector>
#include <string>

// Функция печати для любого контейнера

void Print(const std::vector<int>& container, const std::string& separation)
{
    auto iter = container.begin();
    std::cout << *iter;
    iter++;
    for (; iter != container.end(); ++iter)
    {
        std::cout << separation << *iter;
    }
    std::cout << std::endl;
}

// Пример из условия
int main()
{
    std::vector<int> data = { 1, 2, 3 };
    Print(data, ", ");  // 1, 2, 3
    return 0;
}
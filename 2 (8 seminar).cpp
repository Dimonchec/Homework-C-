/*2) Реализовать свой потокобезопасный контейнер

Контейнер, который можно использовать в нескольких потоках без дополнительных блокировок*/




#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

template<typename T>
class Container // Класс потокобезопасного контейнера
{
private:
    std::vector<T> data; // Вектор с любым типом данных
    mutable std::mutex mutex; // Мьютекс (mutable - чтобы можно было изменять даже в константных методах)

public:
    void push(const T& item) // Добавление элемента
    {
        std::lock_guard<std::mutex> lock(mutex);
        data.push_back(item);
    }

    void pop() // Удаление элемента
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (!data.empty())
        {
            data.pop_back();
        }
    }

    size_t size() const // Размер контейнера
    {
        std::lock_guard<std::mutex> lock(mutex);
        return data.size();
    }

    bool empty() const // Проверка на пустоту 
    {
        std::lock_guard<std::mutex> lock(mutex);
        return data.empty();
    }

    typename std::vector<T>::iterator begin() // Итератор к первому элементу
    {
        std::lock_guard<std::mutex> lock(mutex);
        return data.begin();
    }

    typename std::vector<T>::iterator end() // Итератор к последнему элементу
    {
        std::lock_guard<std::mutex> lock(mutex);
        return data.end();
    }

    typename std::vector<T>::const_iterator cbegin() const // Константный итератор к первому элементу
    {
        std::lock_guard<std::mutex> lock(mutex);
        return data.cbegin();
    }

    typename std::vector<T>::const_iterator cend() const // Константный итератор к последнему элементу
    {
        std::lock_guard<std::mutex> lock(mutex);
        return data.cend();
    }
};

int main() 
{
    Container<int> container;

    // Добавим элементы в контейнер из разных потоков
    std::thread t1([&]()
        {
            for (int i = 0; i < 5; ++i)
            {
                container.push(i);
            }
        });

    std::thread t2([&]()
        {
            for (int i = 5; i < 10; ++i)
            {
                container.push(i);
            }
        });

    t1.join();
    t2.join();

    // Посчитаем размер контейнера
    std::cout << container.size() << std::endl;

    // Проверим, является ли контейнер пустым
    container.empty();

    // Удалим один элемент из контейнера
    container.pop();

    // Выведем все элементы контейнера с помощью обычных итераторов
    for (auto iterator = container.begin(); iterator != container.end(); ++iterator)
    {
        std::cout << *iterator << " ";
    }
    std::cout << std::endl;

    // Выведем все элементы контейнера с помощью константных итераторов
    for (auto citerator = container.cbegin(); citerator != container.cend(); ++citerator)
    {
        std::cout << *citerator << " ";
    }
    std::cout << std::endl;

    return 0;
}
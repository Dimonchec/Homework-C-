#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

class Fork // Класс вилки
{
private:
    std::mutex mutex; // Мютекс

public:
    void putDown() // Если вилка свободна, освобождаем ее
    {
        mutex.unlock();
    }

    bool tryPickUp() // Попытка взять вилку без блокировки. Возвращает true, если удалось взять
    {
        return mutex.try_lock();
    }
};

class Philosopher // Класс философа 
{
private:
    std::string name; // Имя философа
    Fork& left_fork;  // Вилка слева 
    Fork& right_fork; // Вилка справа
    int eatCount;     // количество приемов пищи
    const int maxEating; // максимальное количество приемов пищи

public:
    Philosopher(std::string name, Fork& left, Fork& right, int maxEating)
        : name(name), left_fork(left), right_fork(right), eatCount(0), maxEating(maxEating) {}

    void meal() // Питание
    {
        while (eatCount < maxEating)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Размышляет одну секунду

            std::cout << name << " Neuron activation" << std::endl;

            // Пытаемся захватить вилки
            bool leftPicked = left_fork.tryPickUp();
            bool rightPicked = right_fork.tryPickUp();

            if ( leftPicked && rightPicked) // Если почучилось захватить обе вилки, то кушает
            {
                std::cout << name << " Eating" << std::endl;

                std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Кушает одну секунду

                left_fork.putDown();
                right_fork.putDown();

                ++eatCount;
            }
            else // Если не почучилось захватить обе вилки, освобождает то, что удалось захватить
            {
                if (leftPicked)
                    left_fork.putDown();
                if (rightPicked)
                    right_fork.putDown();
            }
                

            std::cout << name << " Neuron activation again" << std::endl; // Опять размышляет
        }
    }

};

int main()
{
    std::vector<std::thread> philosophers; // 5 философов
    std::vector<Fork> forks(5); // 5 вилок
    std::string Idiots[5] = { "Philosopher 1", "Philosopher 2", "Philosopher 3", "Philosopher 4", "Philosopher 5" }; // Имена философов

    for (int i = 0; i < 5; ++i) // Сажаем философов за стол
    {
        philosophers.emplace_back(std::thread([&Idiots, &forks, i]()
            {
                Philosopher philosopher(Idiots[i], forks[i], forks[(i + 1) % 5], 5); // 5 приемов пищи для каждого философа
                philosopher.meal();
            }));
    }

    for (auto& philosopher : philosophers)  // Дожидаемся конца работы всех потоков
    {
        philosopher.join();
    }

    std::cout << "Философы нажрались до коллапса" << std::endl; // Конец

    return 0;
}


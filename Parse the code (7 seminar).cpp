/*3) Разобраться, что делает код */

#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <string>

std::condition_variable g_Bell;     // Уведомление о звонке
std::condition_variable_any g_Door; // Уведомление о состоянии двери

// Класс Менеджера
class Manager
{
public:
    void ComeToWork()
    {
        std::cout << "Hey security, please open the door!\n"; // Сообщение менеджера о приходе
        g_Bell.notify_one(); // Уведомление о звонке
        std::mutex mutex;
        mutex.lock();
        g_Door.wait(mutex);  // Ожидание открытия двери
        mutex.unlock();
    }
};

// Класс Охранника
class Security
{
    static bool m_SectorClear;       // Флаг, указывающий на доступность сектора
    static std::mutex m_SectorMutex; // Мьютекс для безопасного доступа к флагу
public:
    static bool SectorClear()
    {
        std::lock_guard<std::mutex> lock(m_SectorMutex);
        return m_SectorClear;  // Возвращает доступность сектора
    }
    void NotifyFellows()
    {
        std::lock_guard<std::mutex> lock(m_SectorMutex);
        m_SectorClear = false; // Флаг, указывающий на недоступность сектора
    }
    void WorkHard()
    {
        m_SectorClear = true;  // Флаг, указывающий на доступность сектора
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        while (true)
        {
            if (g_Bell.wait_for(lock, std::chrono::seconds(5)) == std::cv_status::timeout) // Ожидание сигнала о звонке с таймаутом
                std::this_thread::sleep_for(std::chrono::seconds(10)); // Если таймаут истек, охранник спит
            else
            {
                NotifyFellows();     // Уведомление коллег об открытии двери
                g_Door.notify_one(); // Уведомление об открытии двери
                std::cout << "Hello Great Manager, your slaves are ready to serve you!\n" << std::endl; // Сообщение об открытии двери менеджеру
            }
        }
    }
};

bool Security::m_SectorClear;       // Инициализация статической переменной
std::mutex Security::m_SectorMutex; // Инициализация статического мьютекса

// Класс Программиста
class Programmer
{
public:
    void WorkHard()
    {
        std::cout << "Let's write some govnokod!\n" << std::endl; // Сообщение о начале работы
        int i = 0;
        while (true)
        {
            i++;
            i--;
        }
    }
    void PlayStarcraft()
    {
        while (Security::SectorClear()) // Проверка доступности сектора
            ; // Играем, пока сектор доступен
        WorkHard(); // Работаем, если сектор недоступен
    }
};


int main()
{
    Manager manager;
    Programmer programmer;
    Security security;

    // Лямбда-функции для запуска в потоках
    auto managerCall = [&manager]()
        {
            manager.ComeToWork(); // Вызов метода менеджера
        };
    auto programmerCall = [&programmer]()
        {
            programmer.PlayStarcraft(); // Вызов метода программиста
        };
    auto securityCall = [&security]()
        {
            security.WorkHard(); // Вызов метода охранника
        };

    // Создание потоков
    std::thread securityThread(securityCall);             // Поток для охранника
    std::thread programmerThread(programmerCall);         // Поток для программиста
    std::this_thread::sleep_for(std::chrono::minutes(1)); // Подождать минуту
    std::thread managerThread(managerCall);               // Поток для менеджера

    // Ожидание завершения работы всех потоков
    managerThread.join();
    programmerThread.join();
    securityThread.join();

    return 0;
}
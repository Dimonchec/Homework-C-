/*1) Доделать программу с занятия. Добавить к ней функцию поиска элемента.*/

#include <iostream>
#include <vector>
#include <list>
#include <string>

// Класс для представления элемента в таблице
class HashElem
{
public:
    std::string key; // Ключ
    int value;       // Значение

    // Структура элемента
    HashElem(std::string key, int value) : key(key), value(value) {}
};

// Класс хеш-таблицы
class HashTable
{
private:
    int size;
    std::vector<std::list<HashElem>> table;

    // Хеш-функция
    int hashFunction(std::string key)
    {
        int hash = 0;
        for (char c : key)
        {
            hash += c;
        }
        return hash % size;
    }

public:
    HashTable(int size) : size(size), table(size) {}

    // Добавление элемента в таблицу
    void insert(std::string key, int value)
    {
        int index = hashFunction(key);
        table[index].push_back(HashElem(key, value));
    }

    // Поиск элемента в таблице
    int search(std::string key)
    {
        int index = hashFunction(key);
        for (HashElem& elem : table[index])
        {
            if (elem.key == key)
            {
                return elem.value;
            }
        }
        return -1;
    }

    // Удаление элемента из таблицы
    void remove(std::string key)
    {
        int index = hashFunction(key);
        for (auto iterator = table[index].begin(); iterator != table[index].end(); ++iterator)
        {
            if ((*iterator).key == key)
            {
                table[index].erase(iterator);
                return;
            }
        }
    }
};


// Пример
int main()
{
    HashTable hashTable(10);

    hashTable.insert("beast", 1);
    hashTable.insert("bird", 2);
    hashTable.insert("fish", 3);

    std::cout << hashTable.search("beast") << std::endl;  // 1
    std::cout << hashTable.search("bird") << std::endl; // 2
    std::cout << hashTable.search("fish") << std::endl; // 3

    hashTable.remove("beast");
    hashTable.remove("bird");
    hashTable.remove("fish");

    std::cout << hashTable.search("beast") << std::endl;  // -1
    std::cout << hashTable.search("bird") << std::endl; // -1
    std::cout << hashTable.search("fish") << std::endl; // -1

    return 0;
}
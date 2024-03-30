/*1) �������� ��������� � �������. �������� � ��� ������� ������ ��������.*/

#include <iostream>
#include <vector>
#include <list>
#include <string>

// ����� ��� ������������� �������� � �������
class HashElem
{
public:
    std::string key; // ����
    int value;       // ��������

    // ��������� ��������
    HashElem(std::string key, int value) : key(key), value(value) {}
};

// ����� ���-�������
class HashTable
{
private:
    int size;
    std::vector<std::list<HashElem>> table;

    // ���-�������
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

    // ���������� �������� � �������
    void insert(std::string key, int value)
    {
        int index = hashFunction(key);
        table[index].push_back(HashElem(key, value));
    }

    // ����� �������� � �������
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

    // �������� �������� �� �������
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


// ������
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
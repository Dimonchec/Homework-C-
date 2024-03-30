/*2) Реализовать красно-черное дерево и любой другой контейнер. 
Заполнить их 500 случайными неповторяющимися числами. 
Сравнить время поиска. Время добавления нового элемента.*/

#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#define NUM (500) 

// Задаем класс цвета 
enum class Color { RED, BLACK };

// Задаем элемент с родителем, двумя потоиками и цветом
struct Node
{
    int data;     // Значение
    Color color;  // Цвет
    Node* left;   // Левый потомок
    Node* right;  // Правый потомок
    Node* parent; // Родитель

    Node(int data) : data(data), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Класс красно-черного дерева
class RedBlackTree
{
private:
    Node* root;

    // Вращает узел х влево относительно его правого потомка у для балансировки
    void rotateLeft(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        // Потомок элемента обладает правым потомком
        if (y->left != nullptr)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        // Элемент является корнем дерева
        if (x->parent == nullptr)
        {
            root = y;
        }
        // Элемент является левым потомком
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        // Элемент является правым потомком
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // Вращает узел х вправо относительно его правого потомка у для балансировки
    void rotateRight(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;
        // Потомок элемента обладает левым потомком
        if (y->right != nullptr)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        // Элемент является корнем дерева
        if (x->parent == nullptr)
        {
            root = y;
        }
        // Элемент является правым потомком
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        // Элемент является левым потомком
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Балансировка после добавления элемента
    void fixInsertion(Node* z)
    {
        // Родитель элемента красный
        while (z != root && z->parent->color == Color::RED)
        {
            // Родитель элемента левый потомок
            if (z->parent == z->parent->parent->left)
            {
                Node* y = z->parent->parent->right;
                // Дядя элемента находится справа и является красным
                if (y != nullptr && y->color == Color::RED)
                {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                }
                // Дядя элемента является черным или отсутствунт
                else
                {
                    // Элемент является правым потомком
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rotateRight(z->parent->parent);
                }
            }
            // Родитель элемента правый потомок
            else
            {
                Node* y = z->parent->parent->left;
                // Дядя элемента находится слева и является красным
                if (y != nullptr && y->color == Color::RED)
                {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                }
                // Дядя элемента является черным или отсутствунт
                else
                {
                    // Элемент является левым потомком
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = Color::BLACK; // Корень дерева всегда черный
    }

    // Поиск элемента
    Node* search(int data)
    {
        Node* current = root;
        while (current != nullptr && current->data != data)
        {
            if (data < current->data)
            {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return current;
    }

public:
    RedBlackTree() : root(nullptr) {}

    // Добавление элемента
    void insert(int data)
    {
        Node* z = new Node(data);
        Node* y = nullptr;
        Node* x = root;
        while (x != nullptr)
        {
            y = x;
            if (z->data < x->data)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
        z->parent = y;
        if (y == nullptr)
        {
            root = z;
        }
        else if (z->data < y->data)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }
        z->left = nullptr;
        z->right = nullptr;
        z->color = Color::RED;
        fixInsertion(z);
    }

    // Элемент найден или не найден
    bool contains(int data)
    {
        return search(data) != nullptr;
    }
};

// Генерация псевдослучайных чисел от 0 до NUM
int getRandomNumber()
{
    return rand() % NUM;
}

int main()
{
    srand(time(0)); // Генерация случайных чисел теперь зависит от времени

    std::vector<int> container(NUM);

    RedBlackTree tree;

    // Сравнение времени добавлние элемента

    // Заполнение вектора случайными числами
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM; ++i)
    {
        container[i] = getRandomNumber();
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    auto time_vector = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "vector element insert time: " << time_vector << " microseconds" << std::endl;

    // Заполнение дерева случайными числами
    start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM; ++i)
    {
        tree.insert(getRandomNumber());
    }

    end_time = std::chrono::high_resolution_clock::now();

    auto time_tree = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "tree element insert time: " << time_tree << " microseconds" << std::endl;

    // Выбираем более быструю добавку
    if (time_vector < time_tree)
    {
        std::cout << "vector insert is faster" << std::endl;
    }
    else
    {
        std::cout << "tree insert is faster" << std::endl;
    }

    // Сравнение времени поиска элемента

    // Поиск случайных элементов вектора 
    start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM; ++i)
    {
        int randomNum = getRandomNumber();
        std::find(container.begin(), container.end(), randomNum);
    }

    end_time = std::chrono::high_resolution_clock::now();

    time_vector = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "vector element search time: " << time_vector << " microseconds" << std::endl;

    // Поиск случайных элементов дерева
    start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM; ++i)
    {
        int randomNum = getRandomNumber();
        tree.contains(randomNum);
    }

    end_time = std::chrono::high_resolution_clock::now();

    time_tree = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "tree element search time: " << time_tree << " microseconds" << std::endl;

    // Выбираем более быстрый поиск
    if (time_vector < time_tree)
    {
        std::cout << "vector search is faster" << std::endl;
    }
    else
    {
        std::cout << "tree search is faster" << std::endl;
    }

    return 0;
}
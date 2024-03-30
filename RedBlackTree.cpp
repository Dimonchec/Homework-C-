/*2) ����������� ������-������ ������ � ����� ������ ���������. 
��������� �� 500 ���������� ���������������� �������. 
�������� ����� ������. ����� ���������� ������ ��������.*/

#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#define NUM (500) 

// ������ ����� ����� 
enum class Color { RED, BLACK };

// ������ ������� � ���������, ����� ��������� � ������
struct Node
{
    int data;     // ��������
    Color color;  // ����
    Node* left;   // ����� �������
    Node* right;  // ������ �������
    Node* parent; // ��������

    Node(int data) : data(data), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// ����� ������-������� ������
class RedBlackTree
{
private:
    Node* root;

    // ������� ���� � ����� ������������ ��� ������� ������� � ��� ������������
    void rotateLeft(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        // ������� �������� �������� ������ ��������
        if (y->left != nullptr)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        // ������� �������� ������ ������
        if (x->parent == nullptr)
        {
            root = y;
        }
        // ������� �������� ����� ��������
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        // ������� �������� ������ ��������
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // ������� ���� � ������ ������������ ��� ������� ������� � ��� ������������
    void rotateRight(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;
        // ������� �������� �������� ����� ��������
        if (y->right != nullptr)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        // ������� �������� ������ ������
        if (x->parent == nullptr)
        {
            root = y;
        }
        // ������� �������� ������ ��������
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        // ������� �������� ����� ��������
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // ������������ ����� ���������� ��������
    void fixInsertion(Node* z)
    {
        // �������� �������� �������
        while (z != root && z->parent->color == Color::RED)
        {
            // �������� �������� ����� �������
            if (z->parent == z->parent->parent->left)
            {
                Node* y = z->parent->parent->right;
                // ���� �������� ��������� ������ � �������� �������
                if (y != nullptr && y->color == Color::RED)
                {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                }
                // ���� �������� �������� ������ ��� �����������
                else
                {
                    // ������� �������� ������ ��������
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
            // �������� �������� ������ �������
            else
            {
                Node* y = z->parent->parent->left;
                // ���� �������� ��������� ����� � �������� �������
                if (y != nullptr && y->color == Color::RED)
                {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                }
                // ���� �������� �������� ������ ��� �����������
                else
                {
                    // ������� �������� ����� ��������
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
        root->color = Color::BLACK; // ������ ������ ������ ������
    }

    // ����� ��������
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

    // ���������� ��������
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

    // ������� ������ ��� �� ������
    bool contains(int data)
    {
        return search(data) != nullptr;
    }
};

// ��������� ��������������� ����� �� 0 �� NUM
int getRandomNumber()
{
    return rand() % NUM;
}

int main()
{
    srand(time(0)); // ��������� ��������� ����� ������ ������� �� �������

    std::vector<int> container(NUM);

    RedBlackTree tree;

    // ��������� ������� ��������� ��������

    // ���������� ������� ���������� �������
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM; ++i)
    {
        container[i] = getRandomNumber();
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    auto time_vector = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "vector element insert time: " << time_vector << " microseconds" << std::endl;

    // ���������� ������ ���������� �������
    start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM; ++i)
    {
        tree.insert(getRandomNumber());
    }

    end_time = std::chrono::high_resolution_clock::now();

    auto time_tree = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "tree element insert time: " << time_tree << " microseconds" << std::endl;

    // �������� ����� ������� �������
    if (time_vector < time_tree)
    {
        std::cout << "vector insert is faster" << std::endl;
    }
    else
    {
        std::cout << "tree insert is faster" << std::endl;
    }

    // ��������� ������� ������ ��������

    // ����� ��������� ��������� ������� 
    start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM; ++i)
    {
        int randomNum = getRandomNumber();
        std::find(container.begin(), container.end(), randomNum);
    }

    end_time = std::chrono::high_resolution_clock::now();

    time_vector = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "vector element search time: " << time_vector << " microseconds" << std::endl;

    // ����� ��������� ��������� ������
    start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM; ++i)
    {
        int randomNum = getRandomNumber();
        tree.contains(randomNum);
    }

    end_time = std::chrono::high_resolution_clock::now();

    time_tree = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "tree element search time: " << time_tree << " microseconds" << std::endl;

    // �������� ����� ������� �����
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
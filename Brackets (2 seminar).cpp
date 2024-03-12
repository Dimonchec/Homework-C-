/*4) ������ �� ������������� ���������. �� ���� ������� ��������� ������������������ � ������, ������� ������� �� ������ ()[]{}. 
��� ����� ����������, �������� �� ��� ����������. 
� ���������� ��������� ������������������ ������ ����������� ������ ������������� ����������� � ���� ������ ��������� ������� ���� � �����.*/

#include <iostream>
#include <stack>
#include <string>


bool String_brackets(const std::string& brackets) {
    std::stack<char> stack;
    for (char element : brackets) 
    {
        if (element == '(' || element == '[' || element == '{')
        {
            stack.push(element);
        }
        else if (element == ')' || element == ']' || element == '}')
        {
            if (stack.empty())
            {
                return false;
            }
            char top = stack.top();
            stack.pop();
            if ((element == ')' && top != '(') || (element == ']' && top != '[') || (element == '}' && top != '{'))
            {
                return false;
            }
        }
    }
    return stack.empty();
}

int main()
{
    std::string brackets;
    std::cout << "Enter any brackets: ";
    std::cin >> brackets;

    if (String_brackets(brackets))
    {
        std::cout << "True\n";
    }
    else
    {
        std::cout << "False\n";
    }

    return 0;
}
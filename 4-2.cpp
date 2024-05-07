#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

template <class T>
void delete_all(stack<T> &s, const T &x)
{
    stack<T> temp;

    while (!s.empty())
    {
        if (s.top() != x)
        {
            temp.push(s.top());
        }
        s.pop();
    }

    while (!temp.empty())
    {
        s.push(temp.top());
        temp.pop();
    }
}

int main()
{
    stack<char> stk;
    ifstream input("input.txt");
    char ch;
    if (!input >> ch)
    {
        cerr<<"Error opening input file";
        return 1;
    }
        input >> ch;
    char x = ch;
    while (input >> ch)
    {
        stk.push(ch);
    }

    delete_all(stk, x);

    while (!stk.empty())
    {
        cout << stk.top() << " ";
        stk.pop();
    }

    return 0;
}
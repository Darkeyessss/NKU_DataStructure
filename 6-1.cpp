#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_SIZE = 100;

class Deque
{
private:
    int deque[MAX_SIZE];
    int left, right;
    int size;

public:
    Deque()
    {
        size = 0;
        left = MAX_SIZE / 2;
        right = MAX_SIZE / 2 + 1;
    }

    bool IsEmpty()
    {
        return size == 0;
    }

    bool IsFull()
    {
        return size == MAX_SIZE;
    }

    void AddLeft(int value)
    {
        if (IsFull())
        {
            cout << "FULL" << endl;
            return;
        }
        deque[left] = value;
        left = (left - 1 + MAX_SIZE) % MAX_SIZE;
        size++;
        Print();
    }

    void AddRight(int value)
    {
        if (IsFull())
        {
            cout << "FULL" << endl;
            return;
        }
        deque[right] = value;
        right = (right + 1) % MAX_SIZE;
        size++;
        Print();
    }

    void DeleteLeft()
    {
        if (IsEmpty())
        {
            cout << "EMPTY" << endl;
            return;
        }
        left = (left + 1) % MAX_SIZE;
        size--;
        Print();
    }

    void DeleteRight()
    {
        if (IsEmpty())
        {
            cout << "EMPTY" << endl;
            return;
        }
        right = (right - 1 + MAX_SIZE) % MAX_SIZE;
        size--;
        Print();
    }

    void Print()
    {
        if (IsEmpty())
        {
            cout << "EMPTY" << endl;
            return;
        }
        int current = (left + 1) % MAX_SIZE;
        for (int i = 0; i < size; i++)
        {
            cout << deque[current] << " ";
            current = (current + 1) % MAX_SIZE;
        }
        cout << endl;
    }
};

int main()
{
    ifstream infile("input.txt");
    if (!infile)
    {
        cerr << "Cannot open the input file." << endl;
        return 1;
    }

    Deque dq;
    string command;
    int value;
    while (infile >> command)
    {
        if (command == "End")
        {
            break;
        }
        else if (command == "AddLeft")
        {
            infile >> value;
            dq.AddLeft(value);
        }
        else if (command == "AddRight")
        {
            infile >> value;
            dq.AddRight(value);
        }
        else if (command == "DeleteLeft")
        {
            dq.DeleteLeft();
        }
        else if (command == "DeleteRight")
        {
            dq.DeleteRight();
        }
        else if (command == "IsEmpty")
        {
            if (dq.IsEmpty())
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
        else if (command == "IsFull")
        {
            if (dq.IsFull())
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
        else if (command == "Print")
        {
            dq.Print();
        }
        else
        {
            cout << "WRONG" << endl;
        }
    }

    infile.close();
    return 0;
}
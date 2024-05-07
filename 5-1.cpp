#include <iostream>
#include <vector>

using namespace std;

class HashTable
{
private:
    const int TABLE_SIZE = 10;
    vector<int> table;
    vector<bool> neverUsed;

public:
    HashTable()
    {
        table = vector<int>(TABLE_SIZE, -1);
        neverUsed = vector<bool>(TABLE_SIZE, true);
    }

    int Function(int key)
    {
        return key % TABLE_SIZE;
    }

    void insert(int key)
    {
        int index = Function(key);
        while (neverUsed[index] == false)
        {
            index = (index + 1) % TABLE_SIZE; // 线性探查
        }
        table[index] = key;
        neverUsed[index] = false;
        if (should())
        {
            reorganize();
        }
    }

    void remove(int key)
    {
        int index = Function(key);
        while (table[index] != key)
        {
            index = (index + 1) % TABLE_SIZE; // 线性探查
        }
        table[index] = -1;
    }

    void reorganize()
    {
        vector<int> tempTable = table;
        vector<bool> tempNeverUsed = neverUsed;
        table = vector<int>(TABLE_SIZE, -1);
        neverUsed = vector<bool>(TABLE_SIZE, true);
        int tmp = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (tempTable[i] != -1)
            {
                table[tmp] = tempTable[i];
                tmp++;
            }
        }
    }

    bool should()
    {
        int count = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (!neverUsed[i])
            {
                count++;
            }
        }
        return (count >= 0.6 * TABLE_SIZE);
    }

    void print()
    {
        cout << "HashTable: ";
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (table[i] != -1)
            {
                cout << table[i] << " ";
            }
            else
            {
                cout << "N ";
            }
        }
        cout << endl;
    }
};

int main()
{
    HashTable test;
    test.insert(5);
    test.insert(15);
    test.insert(25);
    test.insert(35);
    test.insert(45);
    test.print();
    test.insert(55);
    test.insert(65);
    test.print();
    test.remove(25);
    test.remove(15);
    test.print();
    return 0;
}

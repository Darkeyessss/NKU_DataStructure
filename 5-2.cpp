#include <iostream>
#include <vector>
using namespace std;
struct Node
{
    int key;
    int value;
    Node *next;
    Node(int k, int v) : key(k), value(v), next(nullptr) {}
};

class hashChainsWithTail
{
private:
    int size;
    vector<Node *> buckets;
    Node *tail;

    int hashFunction(int key)
    {
        return key % size;
    }

public:
    hashChainsWithTail(int s) : size(s), tail(nullptr)
    {
        buckets = vector<Node *>(size, nullptr);
    }

    void insert(int key, int value)
    {
        int index = hashFunction(key);
        Node *newNode = new Node(key, value);

        if (buckets[index] == nullptr)
        {
            buckets[index] = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void remove(int key)
    {
        int index = hashFunction(key);
        Node *current = buckets[index];
        Node *prev = nullptr;

        while (current != nullptr && current->key != key)
        {
            prev = current;
            current = current->next;
        }

        if (current == nullptr)
        {
            cout << "Key not found." << endl;
            return;
        }

        if (prev != nullptr)
        {
            prev->next = current->next;
        }
        else
        {
            buckets[index] = current->next;
        }

        if (current == tail)
        {
            tail = prev;
        }

        delete current;
    }
    void display()
    {
        for (int i = 0; i < size; i++)
        {
            Node *current = buckets[i];
            cout << "Bucket " << i << ": ";
            while (current != nullptr)
            {
                cout << "(" << current->key << ", " << current->value << ") ";
                current = current->next;
            }
            cout << endl;
        }
    }
};

int main()
{
    hashChainsWithTail hashTable(5);

    hashTable.insert(1, 10);
    hashTable.insert(2, 20);
    hashTable.insert(3, 30);
    hashTable.display();

    hashTable.remove(2);
    hashTable.display();

    return 0;
}

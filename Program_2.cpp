#include<iostream>
using namespace std;
template <class T>
class ChainNode {
    //friend Chain<T>;
public:
    ChainNode() { }
    ChainNode(const T& e) { data = e; }
    //private:
    T data;
    ChainNode<T>* link;
};
template <class T>
class Chain {
public:
    Chain() { first = 0; }
    ~Chain();
    void Insert(const T&);
    void Delete(T&);
    bool IsEmpty() const { return first == 0; }
    bool IsPresent(const T&) const;
    //private:
    ChainNode<T>* first; // ָ���һ���ڵ��ָ��
};

// Chain�����������
template <class T>
Chain<T>::~Chain() {
    ChainNode<T>* next;
    while (first) {
        next = first->link;
        delete first;
        first = next;
    }
}
// ���뺯����ʵ��
template <class T>
void Chain<T>::Insert(const T& x) {
    ChainNode<T>* p = new ChainNode<T>(x);
    p->link = first;
    first = p;
}

// ɾ��������ʵ��
template <class T>
void Chain<T>::Delete(T& x) {
    if (IsEmpty()) {
        cout << "����Ϊ��" << endl;
        return;
    }
    ChainNode<T>* current = first;
    if (x == current->data) {
        first = current->link;
        delete current;
        return;
    }
    ChainNode<T>* previous = current;
    current = current->link;
    while (current) {
        if (x == current->data) {
            previous->link = current->link;
            delete current;
            return;
        }
        previous = current;
        current = current->link;
    }
    cout << "Ԫ��δ�ҵ�" << endl;
}

// ���Ԫ���Ƿ���ڵ�ʵ��
template <class T>
bool Chain<T>::IsPresent(const T& x) const {
    ChainNode<T>* current = first;
    while (current) {
        if (x == current->data) {
            return true;
        }
        current = current->link;
    }
    return false;
}
template <class T>
class Term {
public:
    Term() {}
    Term(int r, int c, T v) : row(r), col(c), value(v) {}
    int row;
    int col;
    T value;
};

template<class T>
class SparseMatrix
{
    //�ǵ�ÿ��ǰ��һ��Ҫ��const�������治��

public:
    friend ostream& operator<< (ostream& , const SparseMatrix<T>&);
    friend istream& operator>> (istream& , const SparseMatrix<T>&);
    SparseMatrix(int maxTerms = 10);
    ~SparseMatrix() { delete[] a; }
    void Transpose(SparseMatrix<T>& b) const;
    T Get(int i, int j) const;
    void Append(const Term<T>& t) {
        /*if (terms >= MaxTerms)
            throw MatrixOverflow();*/
        a[terms] = t;
        terms++;
    }
    void Time(const SparseMatrix<T>& b, SparseMatrix<T>& c) const;
    int rows, cols; // matrix dimensions
    int terms; // current number of nonzero terms
    Chain<Term<T>> a; // term list
    int MaxTerms; //size of array a;
};

template<class T>
SparseMatrix<T>::SparseMatrix(int max)
{// Sparse matrix constructor.
    /*if (maxTerms < 1)
        throw BadInitializers();*/
    MaxTerms = max;
    a = new Term<T>[MaxTerms];
    terms = rows = cols = 0;
}

template<class T>
T SparseMatrix<T>::Get(int i, int j) const {
    for (int index = 0; index < terms; index++) {
        if (a[index].row == i && a[index].col == j) {
            return a[index].value; // Return the value when the row and column match.
        }
    }
    return 0; // If no matching term is found, return 0.
}


template<class T>
void SparseMatrix<T>::Time(const SparseMatrix<T>& b, SparseMatrix<T>& c) const
{
    /* if (cols != b.rows)
         throw MatrixDimensionMismatch();*/

    c.rows = rows;
    c.cols = b.cols;
    c.terms = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < b.cols; ++j) {
            T sum = 0;
            for (int k = 0; k < b.rows; ++k) {
                T term1 = Get(i + 1, k + 1);
                T term2 = b.Get(k + 1, j + 1);
                sum += term1 * term2;
            }
            if (sum != 0) {
                c.Append(Term<T>(i + 1, j + 1, sum));
            }
        }
    }
}
template<class T>
ostream& operator<< (ostream& out, SparseMatrix<T>& x)
{// Put *this in output stream.
    out << "rows = " << x.rows << " columns = " << x.cols << endl;
    out << "nonzero terms = " << x.terms << endl;
    for (int i = 0; i < x.terms; i++)
        out << "a(" << x.a[i].row << ',' << x.a[i].col << ") = " << x.a[i].value << endl;
    return out;
};
template<class T>
istream& operator>> (istream& in, SparseMatrix<T>& x)
{// Input a sparse matrix.
    //cout << "Enter number of rows, columns, and terms" << endl;
    in >> x.rows >> x.cols >> x.terms;
    /*if (x.terms > x.MaxTerms) throw NoMem();*/
    for (int i = 0; i < x.terms; i++) {
        //cout << "Enter row, column, and value of term " << (i + 1) << endl;
        in >> x.a[i].row >> x.a[i].col >> x.a[i].value;
    }
    return in;
};

int main() {
    SparseMatrix<int> a(1), b(1), c(4);
    cin >> a;
    cin >> b;
    a.Time(b, c);
    cout << c;
}
/*
#include <iostream>
#include <vector>

using namespace std;

class HashTable {
private:
    int capacity; // ɢ�б������
    vector<int> keys; // �洢��������
    vector<bool> neverUsed; // ÿ��Ͱ�Ƿ�ʹ�ù��ı��

    int hash(int key) {
        return key % capacity; // �򵥵Ĺ�ϣ����������ֱ��ʹ��ȡģ
    }

public:
    HashTable(int capacity) {
        this->capacity = capacity;
        keys = vector<int>(capacity, -1); // ��ʼ�����м�Ϊ-1
        neverUsed = vector<bool>(capacity, true); // ��ʼ������Ͱ��neverUsedΪtrue
    }

    void insert(int key) {
        int index = hash(key);
        while (keys[index] != -1) { // ����̽��Ѱ�ҿ�Ͱ
            index = (index + 1) % capacity;
        }
        keys[index] = key;
        neverUsed[index] = false; // ��������neverUsed
    }

    bool search(int key) {
        int index = hash(key);
        int counter = 0;
        while (keys[index] != key && keys[index] != -1 && counter < capacity) { // ��ɢ�б���Ѱ�Ҽ�
            index = (index + 1) % capacity;
            counter++;
        }
        return keys[index] == key;
    }

    void remove(int key) {
        int index = hash(key);
        int counter = 0;
        while (keys[index] != key && keys[index] != -1 && counter < capacity) { // Ѱ��Ҫɾ���ļ�
            index = (index + 1) % capacity;
            counter++;
        }
        if (keys[index] == key) {
            keys[index] = -1;
            neverUsed[index] = true; // ���ΪneverUsed
        }
    }

    void reorganize() {
        int threshold = 0.6 * capacity; // 60%�Ŀ�Ͱ��neverUsed���ֵΪfalseʱ��������֯ɢ�б�
        int count = 0;
        for (int i = 0; i < capacity; i++) {
            if (keys[i] == -1 && !neverUsed[i]) {
                count++;
            }
        }
        if (count >= threshold) {
            vector<int> newKeys(capacity, -1);
            vector<bool> newNeverUsed(capacity, true);
            for (int i = 0; i < capacity; i++) {
                if (keys[i] != -1) {
                    int newIndex = hash(keys[i]);
                    while (newKeys[newIndex] != -1) { // ����̽��Ѱ�ҿ�Ͱ
                        newIndex = (newIndex + 1) % capacity;
                    }
                    newKeys[newIndex] = keys[i];
                    newNeverUsed[newIndex] = false;
                }
            }
            keys = newKeys;
            neverUsed = newNeverUsed;
        }
    }
};

int main() {
    HashTable table(10);
    table.insert(5);
    table.insert(15);
    table.insert(25);
    table.insert(35);
    cout << table.search(15) << endl; // 1
    table.remove(15);
    cout << table.search(15) << endl; // 0
    table.reorganize();
    return 0;
}*/
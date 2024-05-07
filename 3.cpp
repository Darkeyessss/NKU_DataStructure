
#include <iostream>
#include <iomanip>

using namespace std;
template <class T>
class lowerTriangularMatrix
{
public:
    friend ostream &operator<<(ostream &, const lowerTriangularMatrix<T> &);
    friend istream &operator>>(istream &, const lowerTriangularMatrix<T> &);
    // 构造函数和析构函数
    lowerTriangularMatrix(int N);
    void print();
    void print2();
    ~lowerTriangularMatrix() { delete[] element; }
    T *element;                                 // 矩阵中元素存储所在数组
    T get(int, int) const;                      // 获取矩阵中元素
    void set(int, int, const T &);              // 设置矩阵元素值
    lowerTriangularMatrix<T> transpose() const; // 矩阵转置方法
    int n;                                      // 矩阵非零元素最大个数
private:
};

// 构造函数
template <class T>
lowerTriangularMatrix<T>::lowerTriangularMatrix(int N)
{
    /*if (N < 1)
        throw illegalParameterValue();*/

    n = N;
    element = new T[n * (n + 1) / 2];
}

// get()
template <class T>
T lowerTriangularMatrix<T>::get(int i, int j) const
{
    /*if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();*/

    if (i >= j)
        return element[i * (i - 1) / 2 + j - 1];
    else
        return 0;
}

// set()
template <class T>
void lowerTriangularMatrix<T>::set(int i, int j, const T &newValue)
{
    /*if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();*/

    if (i >= j)
    {
        element[i * (i - 1) / 2 + j - 1] = newValue;
        // cout << "1 ";
    }

    /*else
        if (newValue != 0)
            throw illegalParameterValue();*/
}

template <class T>
lowerTriangularMatrix<T> lowerTriangularMatrix<T>::transpose() const
{
    lowerTriangularMatrix<T> t(n);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            t.set(j, i, get(i, j));
        }
    }
    return t;
}

template <class T>
void lowerTriangularMatrix<T>::print2()
{
    int k = 1;
    for (int i = 1; i <= n; i++)
    {
        int x = 1;
        for (; x < i; x++)
        {
            cout << setw(3) << "0";
        }
        for (int j = 0; j < n - x + 1; j++, k++)
        {
            cout << setw(3) << element[k - 1];
        }
        cout << endl;
    }
}

template <class T>
void lowerTriangularMatrix<T>::print()
{
    int k = 1;
    for (int i = 1; i <= n; i++)
    {
        int x = 1;
        for (; x <= i; k++, x++)
        {
            cout << setw(3) << element[k - 1];
        }
        for (int j = 0; j < n - x + 1; j++)
        {
            cout << setw(3) << "0";
        }
        cout << endl;
    }
}

template <class T>
ostream &operator<<(ostream &out, lowerTriangularMatrix<T> &x)
{ // Put *this in output stream.
    int k = 0;
    for (int i = 1; i <= x.n; i++)
    {
        int temp = 1;
        for (; temp <= i; k++, temp++)
        {
            out << setw(3) << x.element[k];
        }
        for (int j = 0; j < x.n - i; j++)
        {
            out << setw(3) << "0";
        }
        out << endl;
    }
    return out;
}

template <class T>
istream &operator>>(istream &in, lowerTriangularMatrix<T> &x)
{
    for (int i = 1; i <= x.n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            T tmp;
            in >> tmp;
            x.set(i, j, tmp);
            // cout << "1 ";
        }
    }
    return in;
}

int main()
{
    lowerTriangularMatrix<int> a(4), b(4), c(4);
    int k = 1;
    cin >> a;
    // for (int i = 1; i <= 10; i++) {
    //     for (int j = 1; j <= i; j++, k++) {
    //         a.set(i, j, k);
    //         //cout << "1 ";
    //     }
    // }
    cout << a;
     a.print();
     a.transpose();
    a.print2();
}
////////////////////////////////

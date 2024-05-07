#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

// 树节点类
class TreeNode
{
public:
    char data;            // 数据域
    TreeNode *LeftChild;  // 左子节点指针
    TreeNode *RightChild; // 右子节点指针

    // 构造函数
    TreeNode(char data)
    {
        this->data = data;
        LeftChild = nullptr;
        RightChild = nullptr;
    }
};

// 树类
class Tree
{
public:
    TreeNode *root; // 根节点指针

    // 构造函数
    Tree()
    {
        root = nullptr;
    }
    stack<TreeNode *> a;
    // 插入节点
    void insertNode(char data)
    {
        root = new TreeNode(data);
        if (data == '+' || data == '-' || data == '*' || data == '/' && a.size() >= 2)
        {
            TreeNode *tmpr = a.top();
            a.pop();
            TreeNode *tmpl = a.top();
            a.pop();
            root->LeftChild = tmpl;
            root->RightChild = tmpr;
            a.push(root);
            return;
        }
        a.push(root);
    }
    void inorderTraversal(TreeNode *root, int depth)
    {
        if (root == nullptr)
        {
            return;
        }

        // 递归遍历右子树
        inorderTraversal(root->RightChild, depth + 1);

        // 打印空格表示深度
        for (int i = 0; i < depth; i++)
        {
            cout << "   ";
        }

        // 打印节点的值
        cout << root->data << endl;

        // 递归遍历左子树
        inorderTraversal(root->LeftChild, depth + 1);
    }
};
// 中缀转后缀
string res(string s)
{
    int l = s.length();
    string target;
    string a;
    stack<char> sk;
    for (int i = 0; i < l; i++)
    {
        char temp = s[i];
        switch (temp)
        {
        case '(':
            sk.push(temp);
            break;
        case ')':
            while (sk.top() != '(')
            {
                a = sk.top();
                target.append(a);
                sk.pop();
            }
            sk.pop();
            break;
        case '+':
        case '-':
            if (sk.empty() || sk.top() == '(')
                sk.push(temp);
            else
            {
                while (!sk.empty() && sk.top() != '(')
                {
                    a = sk.top();
                    target.append(a);
                    sk.pop();
                }
                sk.push(temp);
            }
            break;
        case '*':
        case '/':
            if (sk.empty() || (sk.top() != '/' && sk.top() != '*'))
                sk.push(temp);
            else
            {
                a = sk.top();
                target.append(a);
                sk.pop();
                sk.push(temp);
            }
            break;
        default:
            a = temp;
            target.append(a);
            break;
        }
    }
    while (!sk.empty())
    {
        a = sk.top();
        target.append(a);
        sk.pop();
    }
    return target;
}
int main()
{
    Tree tree;
    string input = "a+b+c*(d+e)";
    string output = res(input);
    //cout << output << endl;
    for (int i = 0; i < output.length(); i++)
    {
        tree.insertNode(output[i]);
    }
    tree.inorderTraversal(tree.root, 0);

    return 0;
}
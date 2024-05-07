#include <iostream>
#include <queue>
using namespace std;

class TreeNode
{
public:
    char data;            // 数据域
    TreeNode *LeftChild;  // 左子节点指针
    TreeNode *RightChild; // 右子节点指针

    // 构造函数
    TreeNode(char da)
    {
        data = da;
        LeftChild = nullptr;
        RightChild = nullptr;
    }
};

class BinaryTree
{
private:
    TreeNode *root; // 根节点
public:
    //统计叶节点数目
    int count(TreeNode *node)
    {
        if (node == nullptr)
            return 0;
        if (node->LeftChild == nullptr && node->RightChild == nullptr)
            return 1;
        return count(node->LeftChild) + count(node->RightChild);
    }

    // 交换左右子树
    void swap1(TreeNode *node)
    {
        if (node == nullptr)
            return;
        swap(node->LeftChild, node->RightChild);
        swap1(node->LeftChild);
        swap1(node->RightChild);
    }


    // 构造函数
    BinaryTree()
    {
        root = nullptr;
    }

    // 插入节点
    void insert(char data, char parentData, char position)
    {
        TreeNode *newNode = new TreeNode(data);
        if (root == nullptr)
        {
            root = newNode;
            return;
        }
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            TreeNode *current = q.front();
            q.pop();
            if (current->data == parentData)
            {
                if (position == 'L' && current->LeftChild == nullptr)
                {
                    current->LeftChild = newNode;
                    return;
                }
                if (position == 'R' && current->RightChild == nullptr)
                {
                    current->RightChild = newNode;
                    return;
                }
            }
            if (current->LeftChild != nullptr)
                q.push(current->LeftChild);
            if (current->RightChild != nullptr)
                q.push(current->RightChild);
        }
    }

    // 统计叶节点数目
    int countL()
    {
        return count(root);
    }

    // 交换左右子树
    void swapChildren()
    {
        swap1(root);
    }

    // 按层次顺序遍历二叉树
    void levelTraversal()
    {
        if (root == nullptr)
            return;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            TreeNode *current = q.front();
            q.pop();
            cout << current->data << " ";
            if (current->LeftChild != nullptr)
                q.push(current->LeftChild);
            if (current->RightChild != nullptr)
                q.push(current->RightChild);
        }
    }

    // 求二叉树的宽度
    int width()
    {
        if (root == nullptr)
            return 0;
        int maxWidth = 0;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            maxWidth = max(maxWidth, size);
            for (int i = 0; i < size; i++)
            {
                TreeNode *current = q.front();
                q.pop();
                if (current->LeftChild != nullptr)
                    q.push(current->LeftChild);
                if (current->RightChild != nullptr)
                    q.push(current->RightChild);
            }
        }
        return maxWidth;
    }
};

int main()
{
    BinaryTree tree;
    tree.insert('A', '\0', '\0');
    tree.insert('B', 'A', 'L');
    tree.insert('C', 'A', 'R');
    tree.insert('D', 'B', 'L');
    tree.insert('E', 'B', 'R');
    tree.insert('F', 'C', 'L');
    tree.insert('G', 'C', 'R');

    // 统计叶节点数目
    cout << tree.countL() << endl;
    tree.levelTraversal();
    cout << endl;
    // 交换左右子树
    tree.swapChildren();
    tree.levelTraversal();
    cout << endl;

    // 按层次顺序遍历二叉树
    tree.levelTraversal();
    cout << endl;

    // 求二叉树的宽度
    cout << tree.width() << endl;

    return 0;
}

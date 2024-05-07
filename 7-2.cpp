#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

struct HuffmanNode
{
    char data;
    int frequency;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

struct CompareNodes
{
    bool operator()(HuffmanNode *left, HuffmanNode *right)
    {
        return left->frequency > right->frequency;
    }
};

class HuffmanTree
{
private:
    HuffmanNode *root;

    void deleteTree(HuffmanNode *node)
    {
        if (node)
        {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    void generateCodes(HuffmanNode *node, string code, unordered_map<char, string> &codes)
    {
        if (node)
        {
            if (!node->left && !node->right)
            {
                codes[node->data] = code;
            }
            generateCodes(node->left, code + "0", codes);
            generateCodes(node->right, code + "1", codes);
        }
    }

public:
    HuffmanTree() : root(nullptr) {}

    ~HuffmanTree()
    {
        deleteTree(root);
    }

    // 构建Huffman树
    void buildTree(unordered_map<char, int> &frequencies)
    {
        priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> pq;

        // 将每个字符及其频率加入优先队列
        for (const auto &pair : frequencies)
        {
            pq.push(new HuffmanNode(pair.first, pair.second));
        }

        while (pq.size() > 1)
        {
            // 从优先队列中取出两个节点，构造一个新的节点，将这两个节点作为新节点的左右子节点
            HuffmanNode *left = pq.top();
            pq.pop();

            HuffmanNode *right = pq.top();
            pq.pop();

            // 构造新节点的频率为左右子节点的频率之和
            HuffmanNode *newNode = new HuffmanNode('\0', left->frequency + right->frequency);
            newNode->left = left;
            newNode->right = right;

            // 将新节点加入优先队列
            pq.push(newNode);
        }

        // 保存Huffman树的根节点
        root = pq.top();
    }
    unordered_map<char, string> generateCodes()
    {
        unordered_map<char, string> codes;
        generateCodes(root, "", codes);
        return codes;
    }

    string encode(const string &text)
    {
        unordered_map<char, int> frequencies;
        for (char c : text)
        {
            frequencies[c]++;
        }

        buildTree(frequencies);
        unordered_map<char, string> codes = generateCodes();

        string encodedText = "";
        for (char c : text)
        {
            encodedText += codes[c];
        }

        return encodedText;
    }

    string decode(const string &encodedText)
    {
        string decodedText = "";
        HuffmanNode *current = root;

        for (char bit : encodedText)
        {
            if (bit == '0')
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }

            if (!current->left && !current->right)
            {
                decodedText += current->data;
                current = root;
            }
        }

        return decodedText;
    }
};

int main()
{
    string text = "aaabbc";
    HuffmanTree tree;

    string encodedText = tree.encode(text);
    string decodedText = tree.decode(encodedText);
    unordered_map<char, string> codes = tree.generateCodes();
    cout << "Original Text: " << text << endl;
    cout << "Encoded Text: " << encodedText << endl;
    cout << "Codes:" << endl;
    for (const auto &code : codes)
    {
        cout << "'" << code.first << "': " << code.second << endl;
    }

    cout << "Decoded Text: " << decodedText << endl;
    return 0;
}

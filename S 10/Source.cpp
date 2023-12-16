#include <iostream>
#include <queue>

struct Node
{
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

struct Result
{
    bool isFull;
    int height;

    Result(bool isFull, int height) : isFull(isFull), height(height) {}
};

int height(Node* node)
{
    if (node == nullptr) return 0;
    return node->height;
}

int balanceFactor(Node* node)
{
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

Node* rotateRight(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* rotateLeft(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* root, int key)
{
    if (root == nullptr) return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);

    else if (key > root->key)
        root->right = insert(root->right, key);

    else
        return root;

    root->height = 1 + std::max(height(root->left), height(root->right));

    int balance = balanceFactor(root);

    if (balance > 1 && key < root->left->key)
        return rotateRight(root);

    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    if (balance > 1 && key > root->left->key)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && key < root->right->key)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Result isFullBinaryTree(Node* root)
{
    if (root == nullptr)
        return Result(true, 0);

    Result left = isFullBinaryTree(root->left);
    Result right = isFullBinaryTree(root->right);

    int current_height = std::max(left.height, right.height) + 1;

    if (left.isFull && right.isFull && left.height == right.height)
        return Result(true, current_height);
    else
        return Result(false, current_height);
}

void findFullBinarySubtrees(Node* root, int& max_height, Node*& max_height_subtree)
{
    if (root == nullptr)
        return;

    Result result = isFullBinaryTree(root);

    if (result.isFull && result.height > max_height)
    {
        max_height = result.height;
        max_height_subtree = root;
    }

    findFullBinarySubtrees(root->left, max_height, max_height_subtree);
    findFullBinarySubtrees(root->right, max_height, max_height_subtree);
}

void printTree(Node* root, int level)
{
    if (root != nullptr)
    {
        printTree(root->right, level + 1);
        for (int i = 0; i < level; i++)
            std::cout << "   ";
        std::cout << root->key << "\n";
        printTree(root->left, level + 1);
    }
}

int main()
{
    system("chcp 1251");

    Node* root = nullptr;

    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 10);
    root = insert(root, 25);
    root = insert(root, 35);
    root = insert(root, 50);
    root = insert(root, 7);

    printTree(root, 0);

    int max_height = 0;
    Node* max_height_subtree = nullptr;

    findFullBinarySubtrees(root, max_height, max_height_subtree);

    if (max_height_subtree)
        std::cout << "\nМаксимальное полное бинарное поддерево имеет корень в узле с ключом: " << max_height_subtree->key << std::endl;
    else
        std::cout << "Нет полных бинарных поддеревьев." << std::endl;

    return 0;
}

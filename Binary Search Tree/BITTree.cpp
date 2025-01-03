#pragma once//без этого проект не компилируется, ищу причину...
#include "BITTree.h"
template<class T>
BinTree<T>::Node::Node(T val) : value(val), right(nullptr), left(nullptr), parent(nullptr) {}

template<class T>
void BinTree<T>::addElem(Node*& node, T val, Node* par)
{
    if (node == nullptr)
    {
        node = new Node(val);
        node->parent = par;
        length++;
    }
    else if (node->value > val)
    {
        addElem(node->left, val, node);
    }
    else if (node->value < val)
    {
        addElem(node->right, val, node);
    }
    // Equal values are not inserted in this tree
}

template<class T>
typename BinTree<T>::Node* BinTree<T>::findElem(Node*& node, T val)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else if (node->value == val)
    {
        return node;
    }
    else if (node->value > val)
    {
        return findElem(node->left, val);
    }
    else if (node->value < val)
    {
        return findElem(node->right, val);
    }
    return nullptr;
}

template<class T>
T BinTree<T>::findMin(Node*& node)
{
    if (node->left == nullptr)
        return node->value;
    return findMin(node->left);
}
template<class T>
T BinTree<T>::findMax(Node*& node)
{
    if (node->right == nullptr)
        return node->value;
    return findMax(node->right);
}

template<class T>
void BinTree<T>::printInOrder(Node*& node)
{
    if (!node) return;
    printInOrder(node->left);
    cout << node->value << ' ';
    printInOrder(node->right);
}

template<class T>
int BinTree<T>::getHeight(Node* node)
{
    if (!node) return 0;
    int left = getHeight(node->left);
    int right = getHeight(node->right);
    return 1 + max(left, right);
}

template<class T>
void BinTree<T>::removeElem(Node*& it, T val)
{
    if (it->left == nullptr && it->right == nullptr)
    {
        // Leaf node
        if (it->parent)
        {
            if (it->parent->left == it) it->parent->left = nullptr;
            else it->parent->right = nullptr;
        }
        else
        {
            root = nullptr;
        }
        delete it;
    }
    else if (it->left && it->right)
    {
        // Node with two children
        Node* child = it->right;
        while (child->left) child = child->left;
        swap(child->value, it->value);
        removeElem(child, child->value);
    }
    else
    {
        // Node with one child
        Node* child = (it->left ? it->left : it->right);
        if (it->parent)
        {
            if (it->parent->left == it) it->parent->left = child;
            else it->parent->right = child;
        }
        else
        {
            root = child;
        }
        child->parent = it->parent;
        delete it;
    }

}

template<class T>
typename BinTree<T>::Node* BinTree<T>::buildBalancedTree(vector<T>& val, int l, int r)
{
    if (l > r) return nullptr;
    int mid = (l + r) / 2;
    Node* node = new Node(val[mid]);
    node->left = buildBalancedTree(val, l, mid - 1);
    node->right = buildBalancedTree(val, mid + 1, r);
    return node;
}

template<class T>
void BinTree<T>::collectInOrder(Node* node, vector<T>& val)
{
    if (!node)return;
    collectInOrder(node->left, val);
    val.push_back(node->value);
    collectInOrder(node->right, val);
}

template<class T>
void BinTree<T>::balanceTree()
{
    vector<T> val;
    collectInOrder(root, val);
    clearTree();
    this->length = val.size();
    root = buildBalancedTree(val, 0, val.size() - 1);
}

template<class T>
bool BinTree<T>::isBalanced(Node* node)
{
    if (!node) return true;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (abs(leftHeight - rightHeight) <= 1 && isBalanced(node->left) && isBalanced(node->right));
}

//public section

template<class T>
BinTree<T>::BinTree() : root(nullptr), length(0) {}

template<class T>
BinTree<T>::~BinTree()
{
    stack<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        auto it = q.top();
        q.pop();
        if (it == nullptr)
            continue;
        q.push(it->left);
        q.push(it->right);
        delete it;
    }
}

template<class T>
void BinTree<T>::clearTree()
{
    stack<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        auto it = q.top();
        q.pop();
        if (it == nullptr)
            continue;
        q.push(it->left);
        q.push(it->right);
        delete it;
    }
    length = 0;
}

template<class T>
void BinTree<T>::addElem(T val)
{
    addElem(root, val, nullptr);
    if (!isBalanced())
    {
        balanceTree();
    }
}

template<class T>
int BinTree<T>::getLength()
{
    return this->length;
};

template<class T>
int BinTree<T>::getHeight()// Calculates the height of the tree
{
    return getHeight(root);
}

template<class T>
bool BinTree<T>::isBalanced()
{
    return isBalanced(root);
}

template<class T>
void BinTree<T>::printTreeBFS()// Prints the tree using BFS
{
    queue<Node*> q;

    q.push(root);
    while (!q.empty())
    {
        auto it = q.front();
        q.pop();

        if (it == nullptr)
            continue;

        cout << it->value << ' ';
        q.push(it->left);
        q.push(it->right);
    }
    cout << endl;
}

template<class T>
void BinTree<T>::printInOrder()// Prints the tree in in-order traversal
{
    printInOrder(root);
    cout << endl;
}

template<class T>
typename BinTree<T>::Node* BinTree<T>::findElem(T val)
{
    return findElem(root, val);
}

template<class T>
T BinTree<T>::findMin()
{
    if (isEmpty())return -1e9;
    return findMin(root);
}
template<class T>
T BinTree<T>::findMax()
{
    if (isEmpty())return -1e9;
    return findMax(root);
}

template<class T>
bool BinTree<T>::isEmpty()
{
    return root == nullptr;
}

template<class T>
void BinTree<T>::removeElem(int val)// Removes a node with the specified value
{
    if (isEmpty())
        return;
    auto it = findElem(val);
    if (it == nullptr) return;
    length--;

    removeElem(it, val);

    if (!isBalanced())
    {
        balanceTree();
    }
}

template<class T>
T BinTree<T>::upperBound(T val)
{
    Node* curr = root;
    Node* candidate = nullptr;
    while (curr)
    {
        if (curr->value > val)
        {
            candidate = curr;
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    return (candidate ? candidate->value : -1e9);
}

template<class T>
T BinTree<T>::lowerBound(T val)
{
    Node* curr = root;
    Node* candidate = nullptr;
    while (curr)
    {
        if (curr->value >= val)
        {
            candidate = curr;
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    return (candidate ? candidate->value : -1e9);
}

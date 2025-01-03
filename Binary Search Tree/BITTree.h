#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>

using namespace std;

template<class T>
class BinTree {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        Node* parent;
        Node(T val);
    };

    Node* root;
    int length;

    void addElem(Node*& node, T val, Node* par);
    Node* findElem(Node*& node, T val);
    T findMin(Node*& node);
    T findMax(Node*& node);
    void printInOrder(Node*& node);
    int getHeight(Node* node);
    void removeElem(Node*& it, T val);
    Node* buildBalancedTree(vector<T>& val, int l, int r);
    void collectInOrder(Node* node, vector<T>& val);
    void balanceTree();
    bool isBalanced(Node* node);

public:
    BinTree();
    ~BinTree();

    void clearTree();
    void addElem(T val);
    int getLength();
    int getHeight();
    bool isBalanced();
    void printTreeBFS();
    void printInOrder();
    Node* findElem(T val);
    T findMin();
    T findMax();
    bool isEmpty();
    void removeElem(int val);
    T upperBound(T val);
    T lowerBound(T val);
};

#include "BITTree.cpp"

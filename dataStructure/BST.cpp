#include <iostream>
#include <vector>

using namespace std;

template<class T>
class BSTNode{
public:
    T key;
    BSTNode *left;
    BSTNode *right;
    BSTNode *parent;
    BSTNode(T value):key(value),left(nullptr),right(nullptr),parent(nullptr){}
};

template<class T>
class BSTree{
private:
    BSTNode<T> *mRoot;
public:
    BSTree():mRoot(nullptr) {};
    ~BSTree();

    void insert(T value);

    void preOrder();

    BSTNode<T>* search(T key);

    BSTNode<T>* successor(BSTNode<T>* n);
private:
    void destory(BSTNode<T>* &tree);

    void insert(BSTNode<T>* &tree, BSTNode<T>* n);

    void preOrder(BSTNode<T>* tree) const;

    BSTNode<T>* search(BSTNode<T>* tree, T key);
    
};
//后继
template<class T>
BSTNode<T>* BSTree<T>::successor(BSTNode<T>* n)
{
    BSTNode<T>* ret = nullptr;
    //有右孩子
    if(n->right != nullptr){
        ret = n->right;
        while(ret->left != nullptr){
            ret = ret->left;
        }
        return ret;
    }else{
        ret = n->parent;
        //是父节点的左孩子
        if(n == ret->left){
            return ret;
        }else{
            while(ret == ret->parent->right)
                ret = ret->parent;
            ret = ret->parent;
            return ret;
        }
    }
}

//查找
template<class T>
BSTNode<T>* BSTree<T>::search(T key)
{
    return search(mRoot, key);
}
template<class T>
BSTNode<T>* BSTree<T>::search(BSTNode<T>* tree, T key)
{
    if(tree == nullptr)
        return nullptr;
    if(key < tree->key)
        return search(tree->left, key);
    else if(key > tree->key)
        return search(tree->right, key);
    else
        return tree;
}

//遍历
template<class T>
void BSTree<T>::preOrder()
{
    cout << "preOrder:";
    preOrder(mRoot);
    cout << endl;
}
template<class T>
void BSTree<T>::preOrder(BSTNode<T>* tree) const
{
    if(tree == nullptr) return;
    cout << tree->key << " ";
    preOrder(tree->left);
    preOrder(tree->right);
}

//插入
template<class T>
void BSTree<T>::insert(T value)
{
    BSTNode<T> *node = new BSTNode<T>(value);
    if(node == nullptr){
        cout << "create node error!" << endl;
        return;
    }
    insert(mRoot, node);
}
template<class T>
void BSTree<T>::insert(BSTNode<T>* &tree, BSTNode<T>* n)
{
    BSTNode<T> *prev = nullptr;
    BSTNode<T> *cur = tree;
    while(cur != nullptr){
        prev = cur;
        if(n->key < cur->key)
            cur = cur->left;
        else
            cur = cur->right;
    }
    n->parent = prev;
    if(prev == nullptr)
        tree = n;
    else if(n->key < prev->key)
        prev->left = n;
    else
        prev->right = n;
}

//析构
template<class T>
BSTree<T>::~BSTree()
{
    destory(mRoot);
}
template<class T>
void BSTree<T>::destory(BSTNode<T>* &tree)
{
    if(tree == nullptr){
        return;
    }
    if(tree->left){
        destory(tree->left);
    }
    if(tree->right){
        destory(tree->right);
    }
    delete tree;
    tree = nullptr;
}

int main()
{
    BSTree<int> t;
    vector<int> toInsert {7,4,9,2,6,8,10,1,3,5};
    for(int num:toInsert){
        t.insert(num);
    }
    t.preOrder();
    cout << t.successor(t.search(3))->key << endl;
}

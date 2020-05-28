#include <iostream>

using namespace std;

template<class T>
class AVLTreeNode
{
public:
    T key;
    int height;
    AVLTreeNode* left;
    AVLTreeNode* right;
    AVLTreeNode(T value, AVLTreeNode* l, AVLTreeNode* r):
    key(value), left(l), right(r), height(0){ }
};
template<class T>
class AVLTree
{
private:
    AVLTreeNode<T>* mRoot;
public:
    AVLTree():mRoot(nullptr){};
    ~AVLTree();

    void insert(T key);

    int height();
private:
    void destory(AVLTreeNode<T>* &tree);

    AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, AVLTreeNode<T>* node);

    int height(AVLTreeNode<T>* tree);
};

//高度
template<class T>
int AVLTree<T>::height()
{
    return height(mRoot);
}
template<class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree)
{
    if(tree != nullptr)
        return tree->height;
    return 0;
}
//插入
template<class T>
void AVLTree<T>::insert(T key)
{
    AVLTreeNode<T>* node = new AVLTreeNode<T>(key, nullptr, nullptr);
    insert(mRoot, node);
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, AVLTreeNode<T>* node)
{
    if(tree == nullptr){
        mRoot = node;
    }
    else if(node->key < tree->key)
    {
        tree->left = insert;
    }
}

//析构
template<class T>
AVLTree<T>::~AVLTree()
{
    destory(mRoot);
}
template<class T>
void AVLTree<T>::destory(AVLTreeNode<T>* &tree)
{
    if(tree == nullptr) return;
    if(tree->left != nullptr)
        destory(tree->left);
    if(tree->right!= nullptr)
        destory(tree->right);
    delete(tree);
    tree = nullptr;
}

int main()
{
    AVLTree<int> t;
    cout << t.height() << endl;
    cout << "sdfsdf" << endl;
    return 0;
}

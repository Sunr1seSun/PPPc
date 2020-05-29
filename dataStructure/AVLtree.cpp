#include <iostream>
#include <vector>
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

    void preOrder();
private:
    void destory(AVLTreeNode<T>* &tree);

    AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, AVLTreeNode<T>* node);

    int height(AVLTreeNode<T>* tree);

    //LL
    AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* tree);
    //LR
    AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* tree);
    //RL
    AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* tree);
    //RR
    AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* tree);

    //遍历
    void preOrder(AVLTreeNode<T>* tree) const;


};

template<class T>
void AVLTree<T>::preOrder()
{
    cout << "preOrder:";
    preOrder(mRoot);
    cout << endl;
}
template<class T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* tree) const
{
    if(tree == nullptr) return;
    cout << tree->key << " ";
    preOrder(tree->left);
    preOrder(tree->right);
}

//变换
template<class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* tree)
{
    AVLTreeNode<T>* newTree = tree->left;
    tree->left = newTree->right;
    newTree->right = tree;

    tree->height = max(height(tree->left), height(tree->right)) + 1;
    newTree->height = max(height(newTree->left), tree->height) + 1;

    return newTree;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* tree)
{
    AVLTreeNode<T>* newTree = tree->right;
    tree->right = newTree->left;
    newTree->left = tree;

    tree->height = max(height(tree->left), height(tree->right)) + 1;
    newTree->height = max(tree->height, height(newTree->right)) + 1;

    return newTree;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* tree)
{
    tree->left = rightRightRotation(tree->left);
    tree = leftLeftRotation(tree);
    return tree;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* tree)
{
    tree->right = leftLeftRotation(tree->right);
    tree = rightRightRotation(tree);
    return tree;
}
//插入
template<class T>
void AVLTree<T>::insert(T key)
{
    AVLTreeNode<T>* n = new AVLTreeNode<T>(key, nullptr, nullptr);
    insert(mRoot, n);
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, AVLTreeNode<T>* node)
{
    if(tree == nullptr)
        tree = node;
    else if(node->key < tree->key){
        tree->left = insert(tree->left, node);
        if(height(tree->left)-height(tree->right) == 2){
            if(node->key < tree->left->key){
                //LL
                tree = leftLeftRotation(tree);
            }else{
                //LR
                tree = leftRightRotation(tree);
            }
        }
    }
    else if(node->key > tree->key){
        tree->right = insert(tree->right, node);
        if(height(tree->right)-height(tree->left) == 2){
            if(node->key < tree->right->key){
                //RL
                tree = rightLeftRotation(tree);
            }else{
                //RR
                tree = rightRightRotation(tree);
            }
        }
    }else{
        cout << "不允许添加相同的节点!" << endl;
    }
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    return tree;
}

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

    vector<int> toInsert {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
    //vector<int> toInsert {1,2,3,4};
    for(int num:toInsert){
        t.insert(num);
    }
    t.preOrder();
    cout << t.height() << endl;
    return 0;
}

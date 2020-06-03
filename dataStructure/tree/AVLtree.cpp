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

    void remove(T key);

    AVLTreeNode<T>* search(T key); 
    T maximum();
    T minimum();
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

    //删除
    AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* n);

    //查找
    AVLTreeNode<T>* search(AVLTreeNode<T>* tree, T key); 

    AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);
    AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
};

template<class T>
T AVLTree<T>::maximum()
{
    return maximum(mRoot)->key;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree)
{
    if(tree->right)
        return maximum(tree->right);
    else
        return tree;
}
template<class T>
T AVLTree<T>::minimum()
{
    return minimum(mRoot)->key;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree)
{
    if(tree->left)
        return minimum(tree->left);
    else
        return tree;
}

//删除
template<class T>
void AVLTree<T>::remove(T key){
    auto node = search(mRoot, key);
    if(node == nullptr)
        return;
    else{
        mRoot = remove(mRoot, node);
    }
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* n)
{
    if(tree == nullptr)
        return nullptr;
    if(n->key < tree->key){
        tree->left = remove(tree->left, n);
        if(height(tree->right) - height(tree->left) == 2){
            AVLTreeNode<T> *r = tree->right;
            if(height(r->left) > height(r->right)){
                tree = rightLeftRotation(tree);
            }else{
                tree = rightRightRotation(tree);
            }
        }
    }else if(n->key > tree->key){
        tree->right = remove(tree->right, n);
        if(height(tree->left) - height(tree->right) == 2){
            AVLTreeNode<T> *l = tree->left;
            if(height(l->left) > height(l->right)){
                tree = leftLeftRotation(tree);
            }else{
                tree = leftRightRotation(tree);
            }
        }
    }else{
        //是要删除的节点
        if(tree->left != nullptr && tree->right != nullptr){
            if(height(tree->left) > height(tree->right)){
                AVLTreeNode<T>* max = maximum(tree->left);
                tree->key = max->key;
                tree->left = remove(tree->left, max);
            }else{
                AVLTreeNode<T>* min = minimum(tree->right);
                tree->key = min->key;
                tree->right = remove(tree->right, min);
            }
        }else{
            AVLTreeNode<T>* toRemove = tree;
            tree = (tree->left != nullptr)?tree->left:tree->right;
            delete toRemove;
        }

    }
    return tree;
}

//查找
template<class T>
AVLTreeNode<T>* AVLTree<T>::search(T key)
{
    auto res = search(mRoot, key);
    if(res == nullptr){
        cout << "can't find "<< key << "." <<endl;
        return nullptr;
    }
    else
        return res;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* tree, T key)
{
    if(tree == nullptr)
        return nullptr;
    else if(tree->key == key)
        return tree;
    else if(key < tree->key){
        return search(tree->left, key);
    }else{
        return search(tree->right, key);
    }
}

//遍历
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
    t.remove(1);
    t.preOrder();

    return 0;
}

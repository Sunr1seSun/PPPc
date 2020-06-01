#include <iostream>
#include <vector>
using namespace std;

enum RBTreeColor {RED, BLACK};

//todo:红黑树中的空节点是个节点，而不是nullptr
template <class T>
class RBTreeNode{
public:
    RBTreeColor color;
    T key;
    RBTreeNode* left;
    RBTreeNode* right;
    RBTreeNode* parent;

    RBTreeNode(T value, RBTreeColor c, RBTreeNode* p, RBTreeNode* l, RBTreeNode* r):
        key(value), color(c), parent(p), left(l), right(r){};
};

template <class T>
class RBTree{
private:
    RBTreeNode<T> *mRoot;
public:
    RBTree():mRoot(nullptr){ };
    ~RBTree();

    void insert(T value);
    
    void preOrder();
    void inOrder();

private:
    void destroy(RBTreeNode<T>* &tree);

    void insert(RBTreeNode<T>* &tree, RBTreeNode<T>* n);
    void insertFixUp(RBTreeNode<T>* &tree, RBTreeNode<T>* n);
    void leftRotate(RBTreeNode<T>* &tree, RBTreeNode<T>* n);
    void rightRotate(RBTreeNode<T>* &tree, RBTreeNode<T>* n);

    void preOrder(RBTreeNode<T>* tree) const;
    void inOrder(RBTreeNode<T>* tree) const;
};


//遍历
template<class T>
void RBTree<T>::inOrder()
{
    cout << "inOrder:";
    inOrder(mRoot);
    cout << endl;
}
template<class T>
void RBTree<T>::inOrder(RBTreeNode<T>* tree) const
{
    if(tree == nullptr) return;
    inOrder(tree->left);
    cout << tree->key << ":" << tree->color << " ";
    inOrder(tree->right);
}
template<class T>
void RBTree<T>::preOrder()
{
    cout << "preOrder:";
    preOrder(mRoot);
    cout << endl;
}
template<class T>
void RBTree<T>::preOrder(RBTreeNode<T>* tree) const
{
    if(tree == nullptr) return;
    cout << tree->key << ":" << tree->color << " ";
    preOrder(tree->left);
    preOrder(tree->right);
}

//rotate
template<class T>
void RBTree<T>::leftRotate(RBTreeNode<T>* &tree, RBTreeNode<T>* n)
{
    RBTreeNode<T>* newParent = n->right;
    n->right = newParent->left;
    if(newParent->left)
        newParent->left->parent = n;
    newParent->parent = n->parent;
    if(n->parent == nullptr)
        tree = newParent;
    else if(n == n->parent->left)
        n->parent->left = newParent;
    else
        n->parent->right = newParent;
    newParent->left = n;
    n->parent = newParent;
}
template<class T>
void RBTree<T>::rightRotate(RBTreeNode<T>* &tree, RBTreeNode<T>* n)
{
    RBTreeNode<T>* newParent = n->left;
    n->left = newParent->right;
    if(newParent->right)
        newParent->right->parent = n;
    newParent->parent = n->parent;
    if(n->parent == nullptr)
        tree = newParent;
    else if(n == n->parent->left)
        n->parent->left = newParent;
    else
        n->parent->right = newParent;
    newParent->right = n;
    n->parent = newParent;
}
//插入
template<class T>
void RBTree<T>::insert(T value)
{
    RBTreeNode<T> *node = new RBTreeNode<T>(value, BLACK, nullptr, nullptr, nullptr);
    insert(mRoot, node);
}
template<class T>
void RBTree<T>::insert(RBTreeNode<T>* &tree, RBTreeNode<T>* n)
{
    RBTreeNode<T>* parent = nullptr;
    RBTreeNode<T>* cur = tree;

    while(cur != nullptr){
        parent = cur;
        if(n->key < cur->key)
            cur = cur->left;
        else if(n->key > cur->key)
            cur = cur->right;
        else
            cout << n->key <<" already in RBTree." << endl;
    }
    n->parent = parent;

    if(parent != nullptr){
        if(n->key < parent->key)
            parent->left = n;
        else
            parent->right = n;
    }else
        tree = n;
    n->color = RED;
    insertFixUp(tree, n);
}
template<class T>
void RBTree<T>::insertFixUp(RBTreeNode<T>* &tree, RBTreeNode<T>* n)
{
    while(n->parent != nullptr && n->parent->color == RED){
        // 如果父亲是左节点
        if(n->parent == n->parent->parent->left){
            RBTreeNode<T>* uncle = n->parent->parent->right;
            if(uncle != nullptr && uncle->color == RED){
                //叔叔红色，一辈变黑，爷爷变红，处理爷爷。
                n->parent->color = BLACK;
                uncle->color = BLACK;
                n->parent->parent->color = RED;
                n = n->parent->parent;
            }
            // 如果叔叔是黑色，自己是右节点
            /*            grandp
                            /
                          p
                           \
                            n
            */
            else if(n == n->parent->right){
                n = n->parent;
                leftRotate(tree, n);
            // 如果叔叔是黑色，自己是左节点。
            /*            grandp
                            /
                          p
                         /
                       n   
            */
            }else{
                n->parent->color = BLACK;
                n->parent->parent->color = RED;
                rightRotate(tree, n->parent->parent);
            }
        }
        // 父亲是右节点
        else{
            RBTreeNode<T>* uncle = n->parent->parent->left;
            if(uncle != nullptr && uncle->color == RED){
                //叔叔红色，一辈变黑，爷爷变红，处理爷爷。
                n->parent->color = BLACK;
                uncle->color = BLACK;
                n->parent->parent->color = RED;
                n = n->parent->parent;
            }
            else if(n == n->parent->left){
                n = n->parent;
                rightRotate(tree, n);
            }else{
                n->parent->color = BLACK;
                n->parent->parent->color = RED;
                leftRotate(tree, n->parent->parent);
            }
        }
    }
    tree->color = BLACK;
}

//析构
template<class T>
RBTree<T>::~RBTree(){
    destroy(mRoot);
}
template<class T>
void RBTree<T>::destroy(RBTreeNode<T>* &tree){
    if(tree == nullptr) return;
    if(tree->left) destroy(tree->left);
    if(tree->right) destroy(tree->right);
    delete tree;
    tree = nullptr;
    return;
}

int main()
{
    RBTree<int> t;

    //vector<int> toInsert {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
    vector<int> toInsert {10, 40, 30, 60, 90, 70, 20, 50, 80 };
    //vector<int> toInsert {5,4,3,2,1 };
    for(int num:toInsert){
        t.insert(num);
    }
    t.preOrder();
    t.inOrder();

    return 0;
}

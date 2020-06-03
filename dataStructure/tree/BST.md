### BST

![1590647718791](.\photo\1590647718791.png)

二叉查找树(Binary Search Tree)，又被称为二叉搜索树。
它是特殊的二叉树：对于二叉树，假设x为二叉树中的任意一个结点，x节点包含关键字key，节点x的key值记为key[x]。如果y是x的左子树中的一个结点，则key[y] <= key[x]；如果y是x的右子树的一个结点，则key[y] >= key[x]。那么，这棵树就是二叉查找树。

#### node

```c++
template <class T>
class BSTNode{
public:
    T key;            // 关键字(键值)
    BSTNode *left;    // 左孩子
    BSTNode *right;    // 右孩子
    BSTNode *parent;// 父结点
};
```

#### BSTree

```
template <class T>
class BSTree {
private:
    BSTNode<T> *mRoot;
public:
	遍历;
	查找;
	插入;
	删除;
	找前驱，找后继;
```

#### 找后继

![1590653367171](.\photo\1590653367171.png)
#### 插入

- 树是空树
- 插入的节点在左边
  - `tree->left = insert(tree->left, node)`
    - LL
    - LR
- 插入的节点在右边
  - `tree->right = insert(tree->right, node)`
    - RL
    - RR

#### 删除

- 树是空树
- 要删除的节点在左边
  - `tree->left = remove(tree->left, n)`
    - RL
    - RR
- 要删除的节点在右边
  - `tree->right = remove(tree->right, n)`
    - LL
    - LR
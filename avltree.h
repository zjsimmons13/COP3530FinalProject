
#include "TreeNode.h"

class AVLTree{

public:
    TreeNode* rootNode;

    AVLTree();
    TreeNode* rotateLeft(TreeNode *node);

    TreeNode* rotateRight(TreeNode *node);

    int getHeight(TreeNode* node);

    TreeNode* getInorderSuccessor(TreeNode* node);

    int getBalanceFactor(TreeNode* node);

    TreeNode* InsertStock(TreeNode* root, Stock* data);
    TreeNode* RemoveStock(TreeNode* root, Stock* data);

    TreeNode* SearchStock(TreeNode* root, string name);
};


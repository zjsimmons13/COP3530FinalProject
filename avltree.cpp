#include "avltree.h"

AVLTree::AVLTree()
{
    rootNode = nullptr;
}
TreeNode* AVLTree::rotateLeft(TreeNode *node)
{
    TreeNode* child = node->right;
    TreeNode* grandchild = node->right->left;
    child->left = node;
    node->right = grandchild;
    node->height = max(getHeight(node->left), getHeight(node->right )) + 1;
    child->height = max(getHeight(child->left), getHeight(child->right )) + 1;
    return child;
};

TreeNode* AVLTree::rotateRight(TreeNode *node)
{
    TreeNode* child = node->left;
    TreeNode* grandchild = node->left->right;
    child->right = node;
    node->left = grandchild;
    node->height = max(getHeight(node->left), getHeight(node->right )) + 1;
    child->height = max(getHeight(child->left), getHeight(child->right )) + 1;
    return child;
};

int AVLTree::getHeight(TreeNode* node){
    if(node == nullptr){
        return 0;
    }
    return node->height;
}

TreeNode* AVLTree::getInorderSuccessor(TreeNode* node){
    if(node->left == nullptr){
        return node;
    }
    else{
        return getInorderSuccessor(node->left);
    }
}

int AVLTree::getBalanceFactor(TreeNode* node){
    if(node == nullptr){
        return 0;
    }
    return (getHeight(node->left) - getHeight(node->right));
}

TreeNode* AVLTree::InsertStock(TreeNode* root, Stock* data){
    if (rootNode == nullptr) {
        rootNode = new TreeNode(data);
        return rootNode;
    }

    if(root == nullptr){
        return (new TreeNode(data));
    }
    else if(*data < *root->data){
        root->left = InsertStock(root->left, data);
    }
    else if(*data > *root->data){
        root->right = InsertStock(root->right, data);
    }
    else{ //In case of a duplicate Stock
        return root;
    }

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1; //updates height
    int BF = getBalanceFactor(root);

    if(BF > 1 && *data < *root->left->data){ //checks for the need of 4 different rotations based on balanced factor
        return rotateRight(root);
    }
    if(BF > 1 && *data > *root->left->data){
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if(BF < -1 && *data > *root->right->data){
        return rotateLeft(root);
    }
    if(BF < -1 && data < root->right->data){
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root; //returns new root of the tree
}

TreeNode* AVLTree::RemoveStock(TreeNode* root, Stock* data){
    if(root == nullptr){ //In case of an empty tree or stock not found
        return root;
    }
    else if(*data < *root->data){
        root->left = RemoveStock(root->left, data);
    }
    else if(*data > *root->data){
        root->right = RemoveStock(root->right, data);
    }
    else{ // when stock is found
        if(root->right != nullptr && root->left != nullptr){ //node has two children
            TreeNode* temp = getInorderSuccessor(root->right);
            root->data = temp->data;
            root->right = RemoveStock(root->right, temp->data);
        }
        else{ //node has zero or one child
            if(root->left == nullptr){
                return root->right;
            }
            else{
                return root->left;
            }
        }
    }

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1; //updates height
    int BF = getBalanceFactor(root);

    if(BF > 1 && getBalanceFactor(root->left) >= 0){ //checks for the need of 4 different rotations based on balanced factor
        return rotateRight(root);
    }
    if(BF > 1 && getBalanceFactor(root->left) < 0){
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if(BF < -1 && getBalanceFactor(root->right) <= 0){
        return rotateLeft(root);
    }
    if(BF < -1 &&  getBalanceFactor(root->right) > 0){
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root; //returns new root of the tree
}

TreeNode* AVLTree::SearchStock(TreeNode* root, string name){
    TreeNode* node = nullptr;
    if(root == nullptr){ //stock not found
        return nullptr;
    }
    else if(name == root->data->name){
        return root;
    }
    if(name < root->data->name){
        node = SearchStock(root->left, name);
    }
    else{
        node = SearchStock(root->right, name);
    }
    return node;
}

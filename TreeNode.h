#include "stock.h"
using namespace std;

struct TreeNode{
    Stock* data;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode(Stock* _data){
        data = _data;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

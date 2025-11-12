#ifndef TREE_H
#define TREE_H
#include "array.h"

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
};

struct Tree {
    TreeNode* root;
};

Tree* create_tree(const char* name);
void tree_insert(Tree* t, int value);
Array* tree_nodes_with_two_children(Tree* t);
void tree_free(Tree* t);

#endif

#include "tree.h"

static TreeNode* node_create(int value) {
    TreeNode* n = new TreeNode;
    n->value = value;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

static void node_insert(TreeNode*& root, int value) {
    if (!root) {
        root = node_create(value);
        return;
    }
    if (value < root->value) {
        node_insert(root->left, value);
    } else{
        node_insert(root->right, value);
    }
}

static void node_collect(TreeNode* n, Array* out) {
    if (!n) {
        return;
    }
    if (n->left && n->right){
        array_push_back(out, n->value);
    }
    node_collect(n->left, out);
    node_collect(n->right, out);
}

static void node_free(TreeNode* n) {
    if (!n) {
        return;
    }
    node_free(n->left);
    node_free(n->right);
    delete n;
}

Tree* create_tree(const char* name) {
    Tree* t = new Tree;
    t->root = nullptr;
    return t;
}

void tree_insert(Tree* t, int value) {
    node_insert(t->root, value);
}

Array* tree_nodes_with_two_children(Tree* t) {
    Array* out = array_create(8);
    node_collect(t->root, out);
    array_sort(out);
    return out;
}

void tree_free(Tree* t) {
    node_free(t->root);
    delete t;
}

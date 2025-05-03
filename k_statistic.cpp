#include <iostream>
#include <algorithm>

struct node {
    int key;
    node *left;
    node *right;
    int height;
    int subtree_size;

    node(int k) : key(k), left(nullptr), right(nullptr), height(1), subtree_size(1) {
    }
};

int get_height(node *node) {
    if (node == nullptr) return 0;
    return node->height;
}

int get_subtree_size(node *node) {
    if (node == nullptr) return 0;
    return node->subtree_size;
}

void update_node(node *node) {
    node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    node->subtree_size = 1 + get_subtree_size(node->left) + get_subtree_size(node->right);
}

node *rotate_right(node *y) {
    node *x = y->left;
    node *temp_node = x->right;

    x->right = y;
    y->left = temp_node;

    update_node(y);
    update_node(x);

    return x;
}

node *rotate_left(node *x) {
    node *y = x->right;
    node *temp_node = y->left;

    y->left = x;
    x->right = temp_node;

    update_node(x);
    update_node(y);

    return y;
}

int get_balance(node *node) {
    if (node == nullptr) return 0;
    return get_height(node->left) - get_height(node->right);
}

node *insert_node(node *node, int key) {
    if (node == nullptr) return new struct node(key);

    if (key < node->key) {
        node->left = insert_node(node->left, key);
    } else if (key > node->key) {
        node->right = insert_node(node->right, key);
    } else {
        return node;
    }

    update_node(node);

    int balance = get_balance(node);

    if (balance > 1 && key < node->left->key) {
        return rotate_right(node);
    }

    if (balance < -1 && key > node->right->key) {
        return rotate_left(node);
    }

    if (balance > 1 && key > node->left->key) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

node *find_k_statistic(node *root, int k) {
    if (root == nullptr) return nullptr;

    int left_size = get_subtree_size(root->left);

    if (k == left_size) {
        return root;
    }

    if (k < left_size) {
        return find_k_statistic(root->left, k);
    }

    return find_k_statistic(root->right, k - left_size - 1);
}

int main() {
    node *root = nullptr;
    int data[] = {
        524287, 262144, 1048576, 131072, 65536,
        4194304, 2097152, 16384, 32768, 8388608
    };

    for (int num: data) {
        root = insert_node(root, num);
    }

    for (int k = 0; k < 10; ++k) {
        node *result = find_k_statistic(root, k);
        std::cout << k << " --- " << result->key << std::endl;
    }

    return 0;
}

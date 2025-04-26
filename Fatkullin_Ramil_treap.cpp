#include <iostream>
#include <cstdlib>
#include <ctime>

template<typename T>
class Treap {
private:
    struct Node {
        T value;
        int priority;
        int count;
        int size;

        Node* left;
        Node* right;

        Node(T val) : value(val), priority(rand()), count(1), size(1), left(nullptr), right(nullptr) {
        }
    };

    Node* root;

    void updateCount(Node* node) {
        if (node) {
            int leftCount = 0;
            if (node->left) {
                leftCount = node->left->count;
            }

            int rightCount = 0;
            if (node->right) {
                rightCount = node->right->count;
            }

            node->count = node->size + leftCount + rightCount;
        }
    }

    void split(Node* node, T key, Node*& left, Node*& right) {
        if (!node) {
            left = nullptr;
            right = nullptr;
            return;
        }

        if (node->value <= key) {
            Node* newRight = nullptr;
            split(node->right, key, node->right, newRight);
            left = node;
            right = newRight;
        }
        else {
            Node* newLeft = nullptr;
            split(node->left, key, newLeft, node->left);
            left = newLeft;
            right = node;
        }
        updateCount(node);
    }

    Node* merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            updateCount(left);
            return left;
        }
        else {
            right->left = merge(left, right->left);
            updateCount(right);
            return right;
        }
    }

    Node* insert(Node* node, Node* newNode) {
        if (!node) return newNode;

        if (newNode->priority > node->priority) {
            split(node, newNode->value, newNode->left, newNode->right);
            updateCount(newNode);
            return newNode;
        }

        if (newNode->value <= node->value) {
            node->left = insert(node->left, newNode);
        }
        else {
            node->right = insert(node->right, newNode);
        }
        updateCount(node);
        return node;
    }

    Node* remove(Node* node, T key) {
        if (!node) return nullptr;

        if (key < node->value) {
            node->left = remove(node->left, key);
        }
        else if (key > node->value) {
            node->right = remove(node->right, key);
        }
        else {
            if (node->size > 1) {
                node->size--;
                node->count--;
                return node;
            }

            Node* temp = merge(node->left, node->right);
            delete node;
            return temp;
        }
        updateCount(node);
        return node;
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    Treap() : root(nullptr) {
        srand(time(nullptr));
    }

    ~Treap() {
        clear(root);
    }

    void insert(T value) {
        Node* newNode = new Node(value);
        root = insert(root, newNode);
    }

    void remove(T value) {
        root = remove(root, value);
    }

    int size() const {
        if (root) {
            return root->count;
        }
        return 0;
    }

    bool contains(T value) const {
        Node* node = root;
        while (node) {
            if (value == node->value) {
                return true;
            }
            else if (value < node->value) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        return false;
    }
};

int main() {
    Treap<int> tree;
    std::cout << tree.size() << std::endl;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(5);
    std::cout << tree.size() << std::endl;

    std::cout << tree.contains(3) << std::endl;
    std::cout << tree.contains(5) << std::endl;
    std::cout << tree.contains(7) << std::endl;
    std::cout << tree.contains(10) << std::endl;

    tree.remove(5);
    std::cout << tree.size() << std::endl;
    std::cout << tree.contains(5) << std::endl;

    tree.remove(5);
    std::cout << tree.size() << std::endl;
    std::cout << tree.contains(5) << std::endl;

    tree.remove(3);
    tree.remove(7);
    std::cout << tree.size() << std::endl;

    tree.remove(100);
    std::cout << tree.size() << std::endl;

    return 0;
}

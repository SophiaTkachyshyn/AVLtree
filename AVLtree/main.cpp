#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

int height(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

// Функція для правого обертання дерева
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Функція для лівого обертання дерева
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Функція для вставки ключа у дерево
Node* insert(Node* node, int key) {
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    // Оновлюємо висоту поточного вузла
    node->height = 1 + max(height(node->left), height(node->right));

    // Отримуємо фактор балансу цього вузла
    int balance = getBalance(node);

    // Якщо вузол стає незбалансованим, то виконуємо один із чотирьох можливих випадків

    // Ліве піддерево важче за праве, і ключ < ключа лівого дочірнього вузла
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Праве піддерево важче за ліве, і ключ > ключа правого дочірнього вузла
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Ліве піддерево важче за праве, і ключ > ключа лівого дочірнього вузла
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Праве піддерево важче за ліве, і ключ < ключа правого дочірнього вузла
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Функція для виведення візуалізації AVL-дерева в консоль
void printTree(Node* root, string indent, bool last) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "  ";
            indent += "  ";
        }
        else {
            cout << "  ";
            indent += "  ";
        }
        cout << root->key << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

Node* minValueNode(Node* node) {
    Node* current = node;

    while (current && current->left != nullptr)
        current = current->left;

    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Якщо знайдено вузол для видалення
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;

            delete temp;
        }
        else {
            // Якщо вузол має два дочірні вузли
            Node* temp = minValueNode(root->right); // Знаходимо найменший вузол у правому піддереві
            root->key = temp->key; // Копіюємо значення ключа
            root->right = deleteNode(root->right, temp->key); // Видаляємо найменший вузол у правому піддереві
        }
    }

    if (root == nullptr)
        return root;

    // Оновлюємо висоту поточного вузла
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Ротації, якщо вузол незбалансований
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}



void preOrder(Node* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}
int main() {
    Node* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 70);
    root = deleteNode(root, 70);


    cout << "Pre-order traversal of AVL tree: ";
    preOrder(root);
    cout << endl;

    cout << "Visual representation of AVL tree:" << endl;
    printTree(root, "", true);

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
enum Color {RED, BLACK, DOUBLE_BLACK};

struct Node
{
    string key;
    ull value;
    int color;
    Node *left, *right, *parent;

    explicit Node(const string&, ull);
};

class RBTree
{
    private:
        Node *root;
    protected:
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void fixInsertRBTree(Node *&);
        void fixDeleteRBTree(Node *&);
        void inorderBST(Node *&);
        void preorderBST(Node *&);
        int getColor(Node *&);
        void setColor(Node *&, int);
        Node *minValueNode(Node *&);
        Node *maxValueNode(Node *&);
        Node* insertBST(Node *&, Node *&);
        Node* deleteBST(Node *&, const string &);
        Node* searchHelper(Node*, const string&);
        int getBlackHeight(Node *);
        void transplant(Node *u, Node *v);
        int compareString(const string &str1, const string &str2);
    public:
        RBTree();
        void insertValue(const string &, ull);
        void deleteValue(const string &);
        void inorder();
        void preorder();
        int search (const string &key);
        Node* get (const string &key);
        static std::string toLower(std::string str);
};
Node::Node(const string& key, ull value) {
    this->key = key;
    this->value = value;
    color = RED;
    left = right = parent = nullptr;
}

RBTree::RBTree() {
    root = nullptr;
}

int RBTree::getColor(Node *&node) {
    if (node == nullptr)
        return BLACK;

    return node->color;
}

void RBTree::setColor(Node *&node, int color) {
    if (node == nullptr)
        return;

    node->color = color;
}

Node* RBTree::insertBST(Node *&root, Node *&ptr) {
    if (root == nullptr)
        return ptr;

    if (ptr->key < root->key) {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    } else if (ptr->key > root->key) {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}

Node* RBTree::searchHelper(Node* node, const string& key)
    {
        if (node == nullptr || key == node->key) {
            return node;
        }
        if (key < node->key) {
            return searchHelper(node->left, key);
        }
        return searchHelper(node->right, key);
}


int RBTree::search(const string& key){
    Node * s = searchHelper(root, key);
    if(s == nullptr){
        return -1;
    }
    else{
        return 1;
    }
}
Node* RBTree::get(const string& key){
    Node * s = searchHelper(root, key);
    if(s == nullptr){
        return nullptr;
    }
    else{
        return s;
    }
}

void RBTree::insertValue(const string& key, ull value) {
    Node *node = new Node(key, value);
    root = insertBST(root, node);
    fixInsertRBTree(node);
}

void RBTree::rotateLeft(Node *&ptr) {
    Node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}

void RBTree::rotateRight(Node *&ptr) {
    Node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}

void RBTree::fixInsertRBTree(Node *&ptr) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}

void RBTree::fixDeleteRBTree(Node *&node) {
    if (node == nullptr)
        return;

    if (node == root) {
        root = nullptr;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node *child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    } else {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }
}

int RBTree::compareString(const string &str1, const string &str2) {
    if (str1 > str2) {
        return 1;
    } else if (str1 < str2) {
        return -1;
    } else {
        return 0;
    }
}


Node* RBTree::deleteBST(Node *&root, const string& key) {
    if (root == nullptr)
        return root;

    if (compareString(key, root->key) < 0)
        return deleteBST(root->left, key);

    if (compareString(key, root->key) > 0)
        return deleteBST(root->right, key);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    Node *temp = minValueNode(root->right);
    root->key = temp->key;
    return deleteBST(root->right, temp->key);
}

void RBTree::transplant(Node *u, Node *v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

void RBTree::deleteValue(const string &key) {
    Node *node = deleteBST(root, key);
    if (node == nullptr) {
        std::cout << "NoSuchWord\n";
        return;
    }

    Node *fix;
    int originalColor = node->color;
    Node *child;

    if (node->left == nullptr) {
        child = node->right;
        transplant(node, node->right);
    } else if (node->right == nullptr) {
        child = node->left;
        transplant(node, node->left);
    } else {
        Node *minRight = minValueNode(node->right);
        originalColor = minRight->color;
        child = minRight->right;

        if (minRight->parent == node) {
            if (child != nullptr) {
                child->parent = minRight;
            }
        } else {
            transplant(minRight, minRight->right);
            minRight->right = node->right;
            minRight->right->parent = minRight;
        }

        transplant(node, minRight);
        minRight->left = node->left;
        minRight->left->parent = minRight;
        minRight->color = node->color;
    }

    if (node == root) {
        if (child != nullptr) {
            root = child;
        } else if (node->left != nullptr) {
            root = node->left;
        } else if (node->right != nullptr) {
            root = node->right;
        } else {
            root = nullptr;
        }
    }

    delete node;

    if (originalColor == BLACK) {
        fixDeleteRBTree(child);
    }

}

void RBTree::inorderBST(Node *&ptr) {
    if (ptr == nullptr)
        return;

    inorderBST(ptr->left);
    cout << ptr->key << " " << ptr->color << endl;
    inorderBST(ptr->right);
}

void RBTree::inorder() {
    inorderBST(root);
}

void RBTree::preorderBST(Node *&ptr) {
    if (ptr == nullptr)
        return;

    cout << ptr->key << " " << ptr->color << endl;
    preorderBST(ptr->left);
    preorderBST(ptr->right);
}

void RBTree::preorder() {
    preorderBST(root);
    cout << "-------" << endl;
}

Node *RBTree::minValueNode(Node *&node) {

    Node *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

Node* RBTree::maxValueNode(Node *&node) {
    Node *ptr = node;

    while (ptr->right != nullptr)
        ptr = ptr->right;

    return ptr;
}

int RBTree::getBlackHeight(Node *node) {
    int blackheight = 0;
    while (node != nullptr) {
        if (getColor(node) == BLACK)
            blackheight++;
        node = node->left;
    }
    return blackheight;
}

string RBTree::toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    RBTree tree;
    string command, key, path;
    ull value;
    while (cin >> command) {
        try {
            if (command == "+") {
                cin >> key >> value;
                key = tree.toLower(key);
                if(tree.search(key) == -1){
                    tree.insertValue(key, value);
                    cout << "OK\n";
                }
                else{
                    cout << "Exist\n";
                }
            } else if (command == "-") {
                cin >> key;
                key = tree.toLower(key);
                if(tree.search(key) == 1){
                    tree.deleteValue(key);
                    cout << "OK\n";
                }
                else{
                    cout << "NoSuchWord\n";
                }
            } else if (command == "!") {
                // cin >> command;
                // if (command == "Save") {
                //     cin >> path;
                //     ofstream file;
                //     file.open(path, ios_base::binary);
                //     if (!file) throw runtime_error("Unable to open file for writing");
                //     tree.saveFile(file, tree.root);
                //     cout << "OK\n";
                //     size_t i = -1;
                //     file.write((char *)&i, sizeof(size_t));
                //     file.close();
                // } else if (command == "Load") {
                //     cin >> path;
                //     ifstream file;
                //     file.open(path, ios_base::binary);
                //     if (!file) throw runtime_error("Unable to open file for reading");
                //     tree.loadFile(file);
                //     file.close();
                // }
            } else {
                key = tree.toLower(command);
                if(tree.search(key) == 1){
                    Node* s = tree.get(key);
                    cout << "OK: " << s->value << '\n';
                }
                else{
                    cout << "NoSuchWord\n";
                }
            }
        } catch (const bad_alloc &) {
            cout << "ERROR: Not enough memory\n";
        } catch (const runtime_error &e) {
            cout << "ERROR: " << e.what() << '\n';
        } catch (...) {
            cout << "ERROR: n";
        }
    }

    // int data;
    // RBTree rbTree1;

    
    // rbTree1.insertValue("a", 1);
    // rbTree1.insertValue("aa", 1);
    // // rbTree1.insertValue("aaa", 1);
    // rbTree1.preorder();
    // rbTree1.deleteValue("aa");
    
    // rbTree1.preorder();

    
    return 0;
}

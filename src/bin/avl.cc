//! \brief AVL tree.
//! \author Fares A. Bakhit
//! \date 2025-05-10
//! \file avl.cpp

#include <algorithm>  // std::max
#include <functional> // std::less
#include <iostream>   // std::ostream
#include <stack>      // std::stack

//! \brief AVL tree
template <class T, class Compare = std::less<T>>
class AVLTree
{
private:
    //! \brief Binary tree node
    struct Node
    {
        T data;
        Node* left;
        Node* right;
        size_t height;

        Node(const T& data) : data(data), left(nullptr), right(nullptr), height(1)
        {
        }
    };

    Node* root;
    Compare cmp;

public:
    //! \brief Initializes the tree to an \ref empty() state.
    AVLTree(const Compare& comp = Compare()) : root(nullptr), cmp(comp)
    {
    }

    //! \brief Height of the tree
    size_t height() const
    {
        return height(root);
    }

    //! \brief Determines wheather the tree is empty.
    bool empty() const
    {
        return root == nullptr;
    }

    //! \brief Inserts an element into the tree.
    void insert(const T& value)
    {
        if (empty())
        {
            root = new Node(value);
            return;
        }
        std::stack<Node*> path;
        Node* parent = root;
        while (parent != nullptr)
        {
            path.push(parent);
            if (cmp(value, parent->data))
            {
                if (parent->left == nullptr)
                {
                    parent->left = new Node(value);
                    break;
                }
                parent = parent->left;
            }
            else if (cmp(parent->data, value))
            {
                if (parent->right == nullptr)
                {
                    parent->right = new Node(value);
                    break;
                }
                parent = parent->right;
            }
            // NOTE: Assume distinct elements.
        }
        while (!path.empty())
        {
            Node *node = path.top(), *prev = node;
            path.pop();
            size_t nodeLeftHeight = height(node->left);
            size_t nodeRightHeight = height(node->right);
            node->height = 1 + std::max(nodeLeftHeight, nodeRightHeight);
            if (nodeLeftHeight > 1 + nodeRightHeight)
            {
                if (height(node->left->left) > height(node->left->right))
                {
                    rightRotate(node);
                }
                else
                {
                    leftRotate(node->left);
                    rightRotate(node);
                }
            }
            else if (nodeRightHeight > 1 + nodeLeftHeight)
            {
                if (height(node->right->right) > height(node->right->left))
                {
                    leftRotate(node);
                }
                else
                {
                    rightRotate(node->right);
                    leftRotate(node);
                }
            }
            if (!path.empty())
            {
                Node* parent = path.top();
                if (parent->left == prev)
                {
                    parent->left = node;
                }
                else if (parent->right == prev)
                {
                    parent->right = node;
                }
            }
            else
            {
                root = node;
            }
        }
    }

    template <class Tp, class CompareP>
    friend std::ostream& operator<<(std::ostream& os, const AVLTree<Tp, CompareP>& avl);

    //! \brief Destroy all elements, leaving the tree in an \ref empty() state.
    void clear()
    {
        clear(root);
    }

    //! \brief Same as \ref clear().
    ~AVLTree()
    {
        clear();
    }

private:
    static void leftRotate(Node*& node)
    {
        Node* pivot = node->right;
        node->right = pivot->left;
        pivot->left = node;
        updateHeight(node);
        updateHeight(pivot);
        node = pivot;
    }

    static void rightRotate(Node*& node)
    {
        Node* pivot = node->left;
        node->left = pivot->right;
        pivot->right = node;
        updateHeight(node);
        updateHeight(pivot);
        node = pivot;
    }

    static void updateHeight(Node* node)
    {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    static size_t height(const Node* node)
    {
        return (node == nullptr) ? 0 : node->height;
    }

    static void printTree(std::ostream& os, const Node* node, const std::string& prefix,
                          bool isLeft)
    {
        if (node == nullptr)
        {
            return;
        }
        os << prefix << (isLeft ? "├── " : "└── ") << node->data << " (" << node->height
           << ")\n";
        printTree(os, node->left, prefix + (isLeft ? "│   " : "    "), true);
        printTree(os, node->right, prefix + (isLeft ? "│   " : "    "), false);
    }

    static void clear(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

template <class T, class Compare>
std::ostream& operator<<(std::ostream& os, const AVLTree<T, Compare>& avl)
{
    avl.printTree(os, avl.root, "", false);
    return os;
}

#include <iostream> // std::cout

int main()
{
    AVLTree<int> x;
    x.insert(5);
    x.insert(9);
    x.insert(7);
    x.insert(3);
    x.insert(8);
    x.insert(12);
    x.insert(1);
    std::cout << x;
    return 0;
}

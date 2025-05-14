//! \brief Binary search tree.
//! \author Fares A. Bakhit
//! \date 2025-04-18
//! \file bst.cpp

#include <functional>
#include <iostream>

//! \brief Binary search tree
template <typename T, class Compare = std::less<T>>
class BinarySearchTree
{
private:
    //! \brief Binary tree node
    struct Node
    {
        T data;
        Node* left;
        Node* right;

        Node(const T& data) : data(data), left(nullptr), right(nullptr)
        {
        }

        Node(const T& data, Node* left, Node* right)
            : data(data), left(left), right(right)
        {
        }
    };

    Node* root;
    Compare cmp;

    void printTree(Node* node, const std::string& prefix, bool isLeft) const
    {
        if (node == nullptr)
            return;

        std::cout << prefix;

        std::cout << (isLeft ? "├── " : "└── ");

        std::cout << node->data << std::endl;

        // Recurse left and right with updated prefix
        printTree(node->left, prefix + (isLeft ? "│   " : "    "), true);
        printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
    }

    void clear(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    //! \brief Initializes the tree to an \ref empty() state.
    BinarySearchTree(const Compare& comp = Compare()) : root(nullptr), cmp(comp)
    {
    }

    //! \brief Determines wheather the tree is empty.
    bool empty() const
    {
        return root == nullptr;
    }

    //! \brief Returns a pointer to the element equal to the given value, if
    //! found.
    T* find(const T& value) const
    {
        Node* node = root;
        while (node != nullptr)
        {
            if (cmp(value, node->data))
            {
                node = node->left;
            }
            else if (cmp(node->data, value))
            {
                node = node->right;
            }
            else
            {
                return &node->data;
            }
        }
        return nullptr;
    }

    //! \brief Inserts an element into the tree.
    void insert(const T& value)
    {
        if (empty())
        {
            root = new Node(value);
            return;
        }
        Node* nodeParent = root;
        while (nodeParent != nullptr)
        {
            if (cmp(value, nodeParent->data))
            {
                if (nodeParent->left == nullptr)
                {
                    nodeParent->left = new Node(value);
                    return;
                }
                nodeParent = nodeParent->left;
            }
            else if (cmp(nodeParent->data, value))
            {
                if (nodeParent->right == nullptr)
                {
                    nodeParent->right = new Node(value);
                    return;
                }
                nodeParent = nodeParent->right;
            }
            // NOTE: Assume distinct elements.
        }
    }

    //! \brief Removes an element from the binary search tree.
    //! \returns true if the element was found and removed, otherwise false.
    bool remove(const T& value)
    {
        if (empty())
        {
            return false;
        }
        Node* nodeParent = root;
        Node* node = root;
        while (node != nullptr)
        {
            if (cmp(value, node->data))
            {
                nodeParent = node;
                node = node->left;
            }
            else if (cmp(node->data, value))
            {
                nodeParent = node;
                node = node->right;
            }
            else // That's our node.
            {
                // Case 1: A leaf node
                if (node->left == nullptr && node->right == nullptr)
                {
                    // We can add a parent member to `Node` to avoid doing this.
                    if (nodeParent->left == node)
                    {
                        nodeParent->left = nullptr;
                    }
                    else if (nodeParent->right == node)
                    {
                        nodeParent->right = nullptr;
                    }
                    delete node;
                }
                // Case 2: Node with one child
                // We're removing node with an only left child.
                else if (node->right == nullptr)
                {
                    // We're removing a left node with an only left child.
                    if (nodeParent->left == node)
                    {
                        nodeParent->left = node->left;
                        delete node;
                    }
                    else if (nodeParent->right == node)
                    {
                        nodeParent->right = node->left;
                        delete node;
                    }
                }
                else if (node->left == nullptr)
                {
                    if (nodeParent->left == node)
                    {
                        nodeParent->left = node->right;
                        delete node;
                    }
                    else if (nodeParent->right == node)
                    {
                        nodeParent->right = node->right;
                        delete node;
                    }
                }
                else // Case 3: Node with two children
                {
                    // Search for node's logical predecessor in its subtrees.
                    Node* predecessorParent = node;
                    Node* predecessor = node->left;
                    while (predecessor->right != nullptr)
                    {
                        predecessorParent = predecessor;
                        predecessor = predecessor->right;
                    }
                    node->data = predecessor->data;
                    if (predecessorParent == node)
                    {
                        predecessorParent->left = predecessor->left;
                    }
                    else
                    {
                        predecessorParent->right = predecessor->left;
                    }
                }
                return true;
            }
        }
        return false;
    }

    //! \brief Prints a simple visual representation of the tree structure.
    void printTree() const
    {
        printTree(root, "", true);
    }

    //! \brief Destroy all elements, leaving the tree in an \ref empty() state.
    void clear()
    {
        clear(root);
    }

    //! \brief Same as \ref clear().
    ~BinarySearchTree()
    {
        clear();
    }
};

#include <iostream>

int main()
{
    BinarySearchTree<int, std::greater<int>> x;
    x.insert(5);
    x.insert(9);
    x.insert(7);
    x.insert(3);
    x.insert(8);
    x.insert(12);
    std::cout << "Before:\n";
    x.printTree();
    x.remove(9);
    x.remove(12);
    x.remove(8);
    x.remove(5);
    std::cout << "After:\n";
    x.printTree();
    return 0;
}

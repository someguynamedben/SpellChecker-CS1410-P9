#ifndef _BinaryTree_h
#define _BinaryTree_h

#include <memory>
#include <iostream>

template <typename T>
class BinaryTree
{
public:
    BinaryTree() :
            m_nodeCount(0)      //only need constructor to initialize node count variable
    {}
    
    bool insert(T value);
    void remove(T value);
    bool search(T value);
    unsigned int numberNodes();
    unsigned int numberLeafNodes();
    unsigned int height();
    void display();

private:
    unsigned int m_nodeCount;       //count of current nodes
    
    template <typename K>
    class TreeNode      //tree node in binary tree
    {
    public:
        TreeNode(K value) :
                data(value),
                left(nullptr),
                right(nullptr)
        {}
        
        K data;     //data in node
        
        std::shared_ptr<TreeNode<K>> left;      //left pointer
        std::shared_ptr<TreeNode<K>> right;     //right pointer
    };
    
    bool insert(std::shared_ptr<TreeNode<T>>& node, std::shared_ptr<TreeNode<T>> ptrNew);
    void remove(std::shared_ptr<TreeNode<T>>& node, T value);
    bool search(std::shared_ptr<TreeNode<T>> node, T value);
    unsigned int numberLeafNodes(std::shared_ptr<TreeNode<T>> node);
    unsigned int height(std::shared_ptr<TreeNode<T>>& node);
    void display(std::shared_ptr<TreeNode<T>> node);
    
    std::shared_ptr<TreeNode<T>> m_root;        //root node pointer
};

template<typename T>
bool BinaryTree<T>::insert(T value)
{
    std::shared_ptr<TreeNode<T>> ptrNew = std::make_shared<TreeNode<T>>(value);
    
    return insert(m_root, ptrNew);
}

template<typename T>
bool BinaryTree<T>::insert(std::shared_ptr<TreeNode<T>>& node, std::shared_ptr<TreeNode<T>> ptrNew)
{
    if (node == nullptr)        //check for leaf nodes to add to binary tree
    {
        node = ptrNew;
        m_nodeCount++;
        
        return true;
    }
    else if (node->data == ptrNew->data)        //if duplicate exists, don't add word
    {
        return false;
    }
    else if (node->data < ptrNew->data)     //navigate through binary tree to insert new node
    {
        return insert(node->right, ptrNew);
    }
    else
    {
        return insert(node->left, ptrNew);
    }
}

template<typename T>
void BinaryTree<T>::remove(T value)
{
    if(search(value))       //check if the value to remove exists
    {
        remove(m_root, value);
    }
    else
    {
        std::cout << "value does not exist" << std::endl;
    }
}

template<typename T>
void BinaryTree<T>::remove(std::shared_ptr<TreeNode<T>>& node, T value)
{
    if (node->data == value)        //check if correct node
    {
        if (node->right == nullptr)
        {
            node = node->left;
        }
        else if (node->left == nullptr)
        {
            node = node->right;
        }
        else        //voodoo magic to delete node
        {
            std::shared_ptr<TreeNode<T>> temp = node->right;
        
            while (temp->left)
            {
                temp = temp->left;
            }
        
            temp->left = node->left;
            node = node->right;
        }
        
        m_nodeCount--;      //decrement number of nodes
    }
    else if (node->data < value)        //search for correct node to delete
    {
        remove(node->right, value);
    }
    else
    {
        remove(node->left, value);
    }
}

template<typename T>
bool BinaryTree<T>::search(T value)
{
    return search(m_root, value);
}

template<typename T>
bool BinaryTree<T>::search(std::shared_ptr<TreeNode<T>> node, T value)
{
    if (node == nullptr)        //make sure there's something in the tree
    {
        return false;
    }
    if (node->data == value)        //return true if data is found
    {
        return true;
    }
    if (node->data < value)     //traverse tree in search of value
    {
        return search(node->right, value);
    }
    else
    {
        return search(node->left, value);
    }
}

template<typename T>
unsigned int BinaryTree<T>::numberNodes()
{
    return m_nodeCount;     //report current number of nodes
}

template<typename T>
unsigned int BinaryTree<T>::numberLeafNodes()
{
    return numberLeafNodes(m_root);
}

template<typename T>
unsigned int BinaryTree<T>::numberLeafNodes(std::shared_ptr<TreeNode<T>> node)
{
    if(node == nullptr) return 1;       //return a count of 1 if node is leaf node
    else if(node->left == nullptr)
    {
        return numberLeafNodes(node->right);
    }
    else if(node->right == nullptr)
    {
        return numberLeafNodes(node->left);
    }
    else
    {
        return numberLeafNodes(node->left) + numberLeafNodes(node->right);
    }
}

template<typename T>
unsigned int BinaryTree<T>::height()
{
    return height(m_root);
}

template<typename T>
unsigned int BinaryTree<T>::height(std::shared_ptr<TreeNode<T>>& node)
{
    if(node == nullptr) return 0;
    
    return 1 + std::max(height(node->left), height(node->right));       //fancy function to find height of tree
}

template<typename T>
void BinaryTree<T>::display()       //print out all values to display
{
    std::cout << "-- Tree Stats --" << std::endl << std::endl;
    std::cout << "Total Nodes: " << numberNodes() << std::endl;
    std::cout << "Leaf Nodes: " << numberLeafNodes() << std::endl;
    std::cout << "Tree Height: " << height() << std::endl << std::endl;
    
    //display(m_root);      //print out values inside the binary tree
}

template<typename T>
void BinaryTree<T>::display(std::shared_ptr<TreeNode<T>> node)
{
    if (node != nullptr)        //print values of tree node as long as they exist
    {
        display(node->left);        //print next left node
        std::cout << node->data << std::endl;       //print current node
        display(node->right);       //print next right node
    }
}

#endif
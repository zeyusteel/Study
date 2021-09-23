#include "13_28.h"
#include <iostream>

TreeNode::TreeNode() : value(std::string()), count(new int(1)), left(nullptr), right(nullptr)
{

}

TreeNode::TreeNode(const TreeNode &tree) : value(tree.value), count(tree.count), left(tree.left), right(tree.left)
{
    ++*count;
}

TreeNode& TreeNode::operator=(const TreeNode &tree)
{
    ++*tree.count;
    if (--*count == 0) {
        delete count;
        delete left;
        delete right;
    }

    value = tree.value;
    count = tree.count;
    left = tree.left;
    right = tree.right;

    return *this;
}

BinStrTree::BinStrTree() : root(new TreeNode())
{

}

BinStrTree::BinStrTree(const BinStrTree& bin) : root(new TreeNode(*bin.root))
{

}

BinStrTree& BinStrTree::operator=(const BinStrTree &bin)
{
    TreeNode *new_root = new TreeNode(*bin.root);
    delete root;
    root = new_root;
    return *this;
}

int main(int argc, char const *argv[])
{
    
    return 0;
}

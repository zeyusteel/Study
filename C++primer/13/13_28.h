/*
给定下面的类，为其实现一个默认构造函数和必要的拷贝控制成员。
(a) 
class TreeNode {
private:
	std::string value;
	int count;
	TreeNode *left;
	TreeNode *right;	
};
(b)
class BinStrTree{
private:
	TreeNode *root;	
};
*/

#include <iostream>
#include <string>
class TreeNode {
public:
	TreeNode();
	TreeNode(const TreeNode &);
	TreeNode& operator=(const TreeNode &);
private:
	std::string value;
	int *count;
	TreeNode *left;
	TreeNode *right;	
};

class BinStrTree{
public:
	BinStrTree();
	BinStrTree(const BinStrTree &);
	BinStrTree& operator=(const BinStrTree &);
    ~BinStrTree() { delete root; }

private:
	TreeNode *root;	
};
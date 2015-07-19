#pragma once
#include <iostream>
#include "Node.h"
class CBinaryTree
{
public:
	CBinaryTree();
	~CBinaryTree();

	void add(int data);
	CNode *search(int data);
	void deleteAll();

private:
	void destroy_tree(CNode *leaf);
	void insert(int data, CNode *leaf);
	CNode *search(int data, CNode *leaf);

	CNode *root;
};


#include "BinaryTree.h"



CBinaryTree::CBinaryTree(): root(NULL)
{
}


CBinaryTree::~CBinaryTree()
{
	deleteAll();
}

void CBinaryTree::destroy_tree(CNode * leaf)
{
	if (leaf != NULL)
	{
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void CBinaryTree::insert(int data, CNode * leaf)
{
	if (data < leaf->getData())
	{
		if (leaf->left != NULL)
			insert(data, leaf->left);
		else
		{
			leaf->left = new CNode;
			leaf->left->setData(data);
			leaf->left->left = NULL;    //Sets the left child of the child node to null
			leaf->left->right = NULL;   //Sets the right child of the child node to null
		}
	}
	else if (data >= leaf->getData())
	{
		if (leaf->right != NULL)
			insert(data, leaf->right);
		else
		{
			leaf->right = new CNode;
			leaf->right->setData(data);
			leaf->right->left = NULL;  //Sets the left child of the child node to null
			leaf->right->right = NULL; //Sets the right child of the child node to null
		}
	}
}
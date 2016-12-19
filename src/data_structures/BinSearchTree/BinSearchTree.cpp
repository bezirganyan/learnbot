/*
 * =====================================================================================
 *
 *       Filename:  tree.cpp
 *
 *    Description:  BinSearchTree source file
 *
 *        Version:  1.0
 *        Created:  11/02/2016 01:36:14 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Grigor Bezirganyan
 *
 * =====================================================================================
 */
//Headers from standard libraries
#include <iostream>
#include <cassert>

//Headers from this project
#include "BinSearchTree.hpp"

void BinSearchTree::insert(std::string d, int id, Node *&root)
{
	if (root == nullptr || root->data == "") {
		Node *new_node = new Node;
		new_node->data = d;
		root = new_node;
                root->id.push_back(id);
	} else if (root->data.compare(d) < 0) {
		insert(d, id, root->right);
	} else if (root->data.compare(d) > 0) {
		insert(d, id, root->left);
	} else if (root->data.compare(d) == 0) {
                root->id.push_back(id);
        }
}

void BinSearchTree::insert(std::string d, int id)
{
	insert(d, id, m_root);
}

Node* BinSearchTree::getRoot() {
	return m_root;
}

// Most probably only inorder traversal wil be used in our project
//void BinSearchTree::preOrder(Node *root)
//{
//	std::cout << root->data << " ";
//	if (root->left != NULL) {
//		preOrder(root->left);
//	}
//	if (root->right != NULL) {
//		preOrder(root->right);
//	}
//}

void BinSearchTree::inOrder()
{
        inOrder(m_root);
}

void BinSearchTree::inOrder(Node *root)
{
	if (root->left != NULL) {
		inOrder(root->left);
	}
	std::cout << root->data << " ";
	if (root->right != NULL) {
		inOrder(root->right);
	}
}

//void BinSearchTree::postOrder(Node *root)
//{
//	if (root->left != NULL) {
//		postOrder(root->left);
//	}
//	if (root->right != NULL) {
//		postOrder(root->right);
//
//	}
//	std::cout << root->data << " ";
//}

Node* BinSearchTree::find(std::string d)
{
	return find(d, m_root);
}

int BinSearchTree::getHeight(Node* root) {
        if (root == NULL) {
            return -1;
        }
        int left = getHeight(root->left);
        int right = getHeight(root->right);
        if (left >= right) {
            return 1 + left;
        } else {
            return 1 + right;
        }
    }

Node* BinSearchTree::find(std::string d, Node* root)
{
	if (root->data.compare(d) == 0) {
		return root;
	} if (root == NULL || root->data == "") {
		return nullptr;
	} else if (root->data.compare(d) < 0) {
		return find(d, root->right);
	} else if (root->data.compare(d) > 0) {
		return find(d, root->left);
	}
        return nullptr;
}

Node* BinSearchTree::findParent(std::string d, Node* root)
{
	if (nullptr != root->left && root->left->data == d) {
		return root;
	} else if (nullptr != root->right && root->right->data == d) {
                return root;
        } else if (root == NULL || root->data == "") {
		return nullptr;
	} else if (root->data < d) {
		return find(d, root->right);
	} else if (root->data > d) {
		return find(d, root->left);
	}
        return nullptr;
}

Node* BinSearchTree::findMinimum(Node* n)
{
	if (n->left == nullptr) {
		return n;
	} else {
		findMinimum(n->left);
	}
        return 0;
}

int BinSearchTree::getHeight()
{
        return getHeight(m_root);
}
bool BinSearchTree::isLeaf(std::string d)
{
	Node* n = find(d);
        assert(nullptr != n);
	if (n->left == nullptr && n->right == nullptr) {
		return true;
	} else {
		return false;
	}
}

void BinSearchTree::remove(std::string d)
{
        remove(find(d));
}

//Remove by Address
void BinSearchTree::remove(Node* n)
{
	if (isLeaf(n->data)) {
		delete n;
	} else {
		if (n->right == nullptr) {
                        Node* parent = findParent(n->data, m_root);
                        if (n->data < parent->data) {
                                parent->left = n->left;
                        } else {
                                parent->right = n->left;
                        }
			delete n;
		} else if (n->left == nullptr) {
                        Node* parent = findParent(n->data, m_root);
                        if (n->data < parent->data) {
                                parent->left = n->right;
                        } else {
                                parent->right = n->right;
                        }
                        delete n;
		} else {
			Node* min = findMinimum(n->right);
			n->data = min->data;
			remove(min);
		}
	}
}

BinSearchTree::BinSearchTree()
{
	m_root = new Node;
}

BinSearchTree::~BinSearchTree()
{
        delete m_root;
}

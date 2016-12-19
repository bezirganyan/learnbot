/*
 * =====================================================================================
 *
 *       Filename:  node.h
 *
 *    Description:  Node header file
 *
 *        Version:  1.0
 *        Created:  11/07/2016 11:53:42 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Grigor Bezirganyan
 *
 * =====================================================================================
 */

// Headers from te standard library
#include <vector>
#include <string>

class Node
{
	public:
                std::string data;
                std::vector<int> id;
		Node* left;
		Node* right;
        public:
                // Public destructor
                ~Node() {
                        delete left;
                        delete right;
                }
};

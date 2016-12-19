//headers from this project
#include "node.hpp"

class BinSearchTree
{
	private:
		//Private Data Members
		Node* m_root;
	public:
		//Public member functions
		void insert(std::string, int); //overloaded with one argument
		Node* getRoot();
		//void preOrder(Node*);
		void inOrder();
		//void postOrder(Node*);
		Node* find(std::string);
		int getHeight();
		bool isLeaf(std::string);
		void remove(std::string); //Remove by Value
		void remove(Node*); //Remove by Address
	private:
		//Private members functions
		void inOrder(Node*);
		Node* find(std::string, Node*);
		Node* findMinimum(Node*);
		Node* findParent(std::string, Node*);
                int getHeight(Node*);
		void insert(std::string, int, Node*&);

	public:
		//Public constructor and destructor
		BinSearchTree();
		~BinSearchTree();

};

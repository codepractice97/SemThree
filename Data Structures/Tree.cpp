#include <iostream>
using namespace std;

template <class T>
class Tree {
	
	struct Node{
		Node *left, *right;
		T data;
		Node(T d){
			data = d;
			left = right = NULL;
		}	
	};
	
	Node *root;
	
public:
	
	Tree(){
		root = NULL;
	}
	
	Node * getRoot() { return root; }
	
	void insert(T data){
		Node *temp = new Node(data);
		if (root == NULL)
			root = temp;
		else {
			Node *current = root, *parent = NULL;
			while (current != NULL){
				parent = current;
				if (data < current->data)
					current = current->left;
				else
					current = current->right;
			}
			if (data < parent->data)
				parent->left = temp;
			else
				parent->right = temp;
		}
	}
	
	T search(T data){
		if (current != NULL){
			if (current->data == data)
				return true;
			bool found_left = preorderTraversal(current->left);
			bool found_right = preorderTraversal(current->right);
			if (!(found_left || found_right))
				return false;
		}
	}
	
	void preorderTraversal(Node *current){
		if (current != NULL){
			cout << current->data << " ";
			preorderTraversal(current->left);
			preorderTraversal(current->right);
		}
	}
	
	void inorderTraversal(Node *current){
		if (current != NULL){
			preorderTraversal(current->left);
			cout << current->data << " ";
			preorderTraversal(current->right);
		}
	}
	
	void postorderTraversal(Node *current){
		if (current != NULL){
			preorderTraversal(current->left);
			preorderTraversal(current->right);
			cout << current->data << " ";
		}
	}
	
};

int main(){
	Tree <int> tree;
	tree.insert(9);
	tree.insert(10);
	tree.insert(4);
	tree.insert(11);
	tree.preorderTraversal(tree.getRoot());
}

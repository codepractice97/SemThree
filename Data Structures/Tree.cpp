#include <iostream>
#include "StackByLL.cpp"
#include "QueueByLL.cpp"
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
	
public:

	Node *root;

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

	bool search(T data){ return search(data, root); }
	
	bool search(T data, Node * current){
		if (current != NULL){
			if (current->data == data)
				return true;
			bool found_left = search(data, current->left);
			bool found_right = search(data, current->right);
			if (!(found_left || found_right))
				return false;
		}
	}
	
	void preorder(Node *current){
		if (current != NULL){
			cout << current->data << " ";
			preorder(current->left);
			preorder(current->right);
		}
	}
	
	void inorder(Node *current){
		if (current != NULL){
			inorder(current->left);
			cout << current->data << " ";
			inorder(current->right);
		}
	}
	
	void postorder(Node *current){
		if (current != NULL){
			postorder(current->left);
			postorder(current->right);
			cout << current->data << " ";
		}
	}

	void preorder2(){
		Stack<Node *> travStack;
		Node *current = root;
		if (current != NULL){
			travStack.push(current);
			while (!travStack.isEmpty()){
				current = travStack.pop();
				cout << current->data << "";
				if (current->right != NULL)
					travStack.push(current->right);
				if (current->left != NULL)
					travStack.push(current->left);
			}
		}
		cout << endl;
	}

	void inorder2(){
		Stack<Node *> travStack;
		Node *current = root;
		if (root != NULL){
			do {
				while (current != NULL){
					travStack.push(current);
					current = current->left;
				}
				current = travStack.pop();
				cout << current->data << " ";
				current = current->right;
			} while (!travStack.isEmpty() || current != NULL);
		}
		cout << endl;
	}

	void postorder2(){
		Stack<Node *> travStack;
		Node *current = root;
		if (root != NULL){
			do {
				while (current != NULL){
					travStack.push(current);
					if (current->right != NULL)
						travStack.push(NULL);
					current = current->left;
				}
				Node *temp = travStack.pop();
				if (temp != NULL)
					cout << temp->data << " ";
				else {
					current = travStack.peek();
					current = current->right;
				}
			} while (!travStack.isEmpty());
		}
	}

	void deleteByCopy(T data){

	}

	void deleteByMerge(T data){

	}

	/* void deleteByMerge(T data)
	{
		if(root!=NULL)
		{
			BSTNode *current=root,*parent=NULL;
			while(current!=NULL)
			{
				parent=current;
				if(current->data>data)					current=current->left;	
				else if(current->data<data)				current=current->right;	
				else 									break;
			}
			if(current==NULL)
				cout<<"\nData not found\n";
			else
			{
				BSTNode *val;
				if(current->left==current->right)			val=NULL;
				else if(current->left==NULL)				val=current->right;
				else if(current->right==NULL)				val=current->left;
				else
				{					
					BSTNode*temp=current->left;
					while(temp->right!=NULL)
						temp=temp->right;
					if(parent==NULL)						val=current->left;									
					else									val=temp;	
					
					temp->right=current->right;					
				}				
				
				if(parent==NULL)						root=val;
				else if(parent->left==current)			parent->left=val;
				else if(parent->right==current)			parent->right=val;
				delete current;
			}
		}
		else
			throw "Tree empty\n";		
	}

	void deleteByCopy(T data)
	{
		if(root!=NULL)
		{
			BSTNode *current=root,*parent=NULL;
			while(current!=NULL)
			{
				parent=current;
				if(current->data>data)					current=current->left;	
				else if(current->data<data)				current=current->right;	
				else 									break;
			}
			if(current==NULL)
				cout<<"\nData not found\n";
			else
			{
				int flag=0;
				BSTNode *val;
				if(current->left==current->right)			val=NULL;
				else if(current->left==NULL)				val=current->right;
				else if(current->right==NULL)				val=current->left;
				else
				{	
					flag=1;				
					BSTNode*temp=current->left,*temp2=current;
					while(temp->right!=NULL)
					{
						temp2=temp;
						temp=temp->right;
					}
					if(temp2->left==temp)					temp2->left=temp->left;	
					else if(temp2->right==temp)				temp2->right=temp->left;
					current->data=temp->data;
					current=temp;	
				}				
				if(flag==0)
				{
					if(parent==NULL)						root=val;
					else if(parent->left==current)			parent->left=val;
					else if(parent->right==current)			parent->right=val;					
				}		
				delete current;				
			}
		}
		else
			throw "Tree empty\n";		
	}	 */

	void breadthFirst(){
		Queue<Node *> travQueue;
		Node *current = root;
		if (current != NULL){
			travQueue.enqueue(current);
			while (!travQueue.isEmpty()){
				current = travQueue.dequeue();
				cout << current->data << " ";
				if (current->left != NULL)
					travQueue.enqueue(current->left);
				if (current->right != NULL)
					travQueue.enqueue(current->right);
			}
		}
	}

	void count(){
		int t = 0, l = 0;
		count(root, t, l);
		cout << "Total Nodes: " << t << endl;
		cout << "Total leaf nodes: " << l << endl;
	}

	void count(Node * current, int & t, int & l){
		if (current->left != NULL)
			count(current->left, t, l);
		if (current != NULL)
			t++;
		if (current->right != NULL)
			count(current->right, t, l);
		if (current->left == NULL && current->right == NULL)
			l++;
	}

	void height(){
		cout << "Height: " << height(root) << endl;
	}

	int height(Node * current){
		if(current == NULL)
			return -1;
		else {
			int lh = height(current->left);
			int rh = height(current->right);
			return max(lh,rh) + 1;
		}
	}

	void mirror(){
		mirror(root);
	}

	void mirror(Node* p)
	{
		Node *temp;
		temp = p->left;
		p->left = p->right;
		p->right = temp;
		if(p->left != NULL)
			mirror(p->left);
		if(p->right != NULL)
			mirror(p->right);
	}

	void copy(){
		Tree<int> newTree;
		newTree.root = copy(root);
		newTree.inorder(newTree.root);
	}

	Node * copy(Node * current){
		if (current != NULL){
			Node *temp = new Node(current->data);
			temp->left = copy(current->left);
			temp->right = copy(current->right);
			return temp;
		} else return NULL;
	}
	
};

int menu() {
	cout<<"\n\nMENU\n";
	cout<<"1. Insertion\n";
	cout<<"2. Search\n";
	cout<<"3. In Order Traversal\n";
	cout<<"4. In Order Traversal Iterative\n";
	cout<<"5. Pre Order Traversal\n";
	cout<<"6. Pre Order Traversal Iterative\n";
	cout<<"7. Post Order Traversal\n";
	cout<<"8. Post Order Traversal Iterative\n";
	cout<<"9. Level by Level Traversal\n";
	cout<<"10. Count no. of Leaf, Non Leaf & Total nodes\n";
	cout<<"11. Height of tree\n";
	cout<<"12. Mirror of tree\n";
	cout<<"13. Delete by merging\n";
	cout<<"14. Delete by Copy\n";
	cout<<"15. Copy tree\n";
	cout<<"Enter choice\n";
	int ch;
	cin >> ch;
	return ch;
}

int main(){
	Tree <int> tree;
	char choice;
	do {
		try{
			int ch = menu(), data;
			switch(ch) {
				case 1:	cout << "Enter data to insert\n";
						cin >> data;
						tree.insert(data);
					break;
				case 2: cout << "Enter data to search\n";
						cin >> data;
						if(tree.search(data))
							cout << "Data found";
						else
							cout << "Data not found";
					break;
				case 3:	tree.inorder(tree.root);
					break;
				case 4:	tree.inorder2();
					break;		
				case 5:	tree.preorder(tree.root);
					break;
				case 6:	tree.preorder2();
					break;
				case 7:	tree.postorder(tree.root);
					break;
				case 8:	tree.postorder2();
					break;
				case 9:	tree.breadthFirst();
					break;
				case 10: tree.count();
					break;
				case 11: tree.height();
					break;
				case 12: tree.mirror();
					break;
				case 13: cout << "Enter data to Deleted\n";
						 cin >> data;
					     tree.deleteByMerge(data);
					break;
				case 14: cout << "Enter data to Deleted\n";
						 cin >> data;
					     tree.deleteByCopy(data);
					break;
				case 15: tree.copy();
					break;
				default: cout << "Invalid Option\n";
			}
		}
		catch(const char * c){
			cout << c;
		}

		cout << "Enter 'Y' to continue\n";
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');

	return 0;
}

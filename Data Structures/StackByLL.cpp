#include <iostream>
using namespace std;

template <class T>
class Stack{

	struct Node{
		T data;
		Node *next;
		Node(T d){
			data = d;
			next = NULL;
		}
	};
	
	Node *top;
	
public:

	Stack(){
		top = NULL;
	}

	void push(T data){
		Node *temp = new Node(data);
		if (top == NULL)
			top = temp;
		else {
			temp->next = top;
			top = temp;
		}
	}

	T pop(){
		if (top == NULL)
			throw "Stack Underflow";
		else {
			T data = top->data;
			Node *temp = top->next;
			delete top;
			top = temp;
			return data;
		}
	}
	
	T peek(){
		if (top == NULL)
			throw "Stack Underflow";
		else {
			return top->data;
		}
	}
	
	bool isEmpty(){
		return top == NULL;
	}

	int size(){
		int size = 0;
		Node *current = top;
		while(current != NULL){
			size++;
			current = current->next;
		}

		return size;
	}

	void display(){
		Node *current = top;
		while(current != NULL){
			cout << current-> data << "-->";
			current = current->next;
		}
		cout << "NULL" << endl;
	}
	
	void clear(){
		while (!isEmpty())
			pop();
	}
	
};

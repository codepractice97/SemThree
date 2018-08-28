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
	
};

template <class T>
void displayChoice(Stack<T> &stack){
	char choice;
	do {
		cout << "Choose Option:\n1. Push\n2. Pop\n3. Peek\n";
		cout << "4. Print size\n5. Display Stack\n";
		cin >> choice;
		if (choice == '1'){
			do {
				T data;
				cout << "Enter data to push\n";
				cin >> data;
				stack.push(data);

				stack.display();

				cout << "Enter 'Y' to push more\n";
				cin >> choice;
			} while (choice == 'Y' || choice == 'y');
		} else if (choice == '2'){
			do {
				cout << "Element Popped: " << stack.pop() << endl;
				stack.display();

				cout << "Enter 'Y' to pop more\n";
				cin >> choice;
			} while (choice == 'Y' || choice == 'y');
		} else if (choice == '3'){
			cout << "Top Element is: " << stack.peek() << endl;
		} else if (choice == '4'){
			cout << "Size of Stack is: " << stack.size() << endl;
		} else if (choice == '5'){
			stack.display();
		} else
			cout << "Invalid Option\n";

		cout << "Enter 'Y' to continue" << endl;
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
}

int main(){
	Stack<float> list;

	displayChoice<float>(list);

	return 0;
}

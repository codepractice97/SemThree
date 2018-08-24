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

	int length(){
		int size = 0;
		Node *current = head;
		while(current != NULL){
			size++;
			current = current->next;
		}

		return size;
	}
	
};

template <class T>
void displayChoice(Stack<T> &stack){
	char choice;
	do {
		cout << "Choose Option:\n1. Add Elements\n2. Remove Elements\n";
		cout << "3. Print length\n4. Reverse list\n5. Find indexOf\n";
		cout << "6. Concatenate\n7. Display list\n";
		cin >> choice;
		if (choice == '1'){
			do {
				T data;
				cout << "Enter Integer to add\n";
				cin >> data;
				cout << "Choose Method:\n1. addAtBeg(int)\n2. addAtEnd(int)\n3. add(int, int)\n";
				cin >> choice;
				if (choice == '1')
					list.addAtBeg(data);
				else if (choice == '2')
					list.addAtEnd(data);
				else if(choice == '3'){
					cout << "Enter index: ";
					int pos;
					cin >> pos;
					list.add(pos, data);
				} else
					cout << "Invalid Option\n";

				list.display();

				cout << "Enter 'Y' to add more\n";
				cin >> choice;
			} while (choice == 'Y' || choice == 'y');
		} else if (choice == '2'){
			do {
				cout << "Choose Method:\n1. removeAtBeg\n2. removeAtEnd\n3. By Position\n4. By Element\n";
				cin >> choice;
				if (choice == '1')
					cout << list.removeAtBeg() << " removed\n";
				else if (choice == '2')
					cout << list.removeAtEnd() << " removed\n";
				else if (choice == '3'){
					cout << "Enter Position: ";
					int pos;
					cin >> pos;
					cout << list.removeByPos(pos) << " removed\n";
				} else if (choice == '4'){
					cout << "Enter data: ";
					T data;
					cin >> data;
					cout << list.removeByEle(data) << " removed\n";
				} else
					cout << "Invalid Option\n";
				list.display();

				cout << "Enter 'Y' to remove more\n";
				cin >> choice;
			} while (choice == 'Y' || choice == 'y');
		} else if (choice == '3'){
			cout << "Length of list is: " << list.length() << endl;
		} else if (choice == '4'){
			list.reverse();
			cout << "Reverse list is:" << endl;
			list.display();
		} else if (choice == '5'){
			cout << "Enter element";
			T data;
			cin >> data;
			int pos = list.indexOf(data);
			if (pos == -1)
				cout << "Element does not exist in list\n";
			else
				cout << data << " exists at position " << pos << endl;
		}  else if (choice == '6'){
			SinglyLinkedList<T> list1;
			list1.addAtBeg(69);
			list = SinglyLinkedList<T>::concatenate(list, list1);
			cout << "Concatenated List: " << endl;
			list.display();
		} else if (choice == '7')
			list.display();
		else
			cout << "Invalid Option\n";

		cout << "Enter 'Y' to continue" << endl;
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
}

int main(){
	SinglyLinkedList<float> list;

	displayChoice<float>(list);

	return 0;
}

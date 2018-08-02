#include <iostream>
using namespace std;

class SinglyLinkedList{

	class Node{
		public:
			int data;
			Node *next;
			Node(int d){
				data = d;
				next = NULL;
			}
	};
	
	Node *head, *tail;
	
public:

	SinglyLinkedList(){
		head = tail = NULL;
	}
	
	void add(int data){
		Node *temp = new Node(data);
		if (head == NULL)
			head = tail = temp;
		else {
			tail->next = temp;
			tail = temp;
		}
	}
	
	void add(int pos, int data){
		Node *temp = new Node(data);
		if (head == NULL)
			head = tail = temp;
		else if (pos == 0){
			temp->next = head;
			head = temp;
		} else {
			Node *current = head;
			for(int i=1;i<pos;i++){
				if (current->next == NULL)
					break;
				current = current->next;
			}
			if (current->next == NULL)
				tail = temp;
			temp->next = current->next;
			current->next = temp;
		}
	}

	int removeByPos(int pos){
		if(head == NULL)
			throw "List Empty";
		else {
			Node *current = head, *previous = NULL;
			for (int i = 0; i < pos; ++i){
				if(current->next == NULL)
					throw "Out of Bounds";
				previous = current;
				current = current->next;
			}
			if (current == head)
				head = head->next;
			if (current == tail)
				tail = previous;
			if (previous != NULL)
				previous->next = current->next;
			int data = current->data;
			delete current;
			return data;
		}
	}

	int removeByEle(int data){
		int pos = indexOf(data);
		if (pos == -1)
			throw "Element not found";
		else
			removeByPos(pos);
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

	void reverse(){
		if(head == NULL)
			return;
		tail = head;
		Node *current = head, *next = head->next;
		while(next != NULL){
			Node *temp = next->next;
			next->next = current;
			current = next;
			next = temp;
		}
		head->next = NULL;
		head = current;
	}

	int indexOf(int data){
		Node *current = head;
		int pos = 0;
		while (current != NULL){
			if (current->data == data)
				return pos;
			pos++;
			current = current->next;
		}

		return -1;
	}


	
	void display(){
		Node *current = head;
		while(current != NULL){
			cout << current-> data << "-->";
			current = current->next;
		}
		cout << "NULL" << endl;
	}
	
	
};

void displayChoice(SinglyLinkedList &list){
	char choice;
	do {
		cout << "Choose Option:\n1. Add Elements\n2. Remove Elements\n";
		cout << "3. Print length\n4. Reverse list\n5. Find indexOf\n6. Display list\n";
		cin >> choice;
		if (choice == '1'){
			do {
				int data;
				cout << "Enter Integer to add\n";
				cin >> data;
				cout << "Choose Method:\n1. add(int)\n2. add(int, int)\n";
				cin >> choice;
				if (choice == '1')
					list.add(data);
				else if(choice == '2'){
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
				cout << "Choose Method:\n1. By Position\n2. By Element\n";
				cin >> choice;
				if (choice == '1'){
					cout << "Enter Position: ";
					int pos;
					cin >> pos;
					list.removeByPos(pos);
				} else if (choice == '2'){
					cout << "Enter data: ";
					int data;
					cin >> data;
					list.removeByEle(data);
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
			int data;
			cin >> data;
			int pos = list.indexOf(data);
			if (pos == -1)
				cout << "Element does not exist in list\n";
			else
				cout << data << " exists at position " << pos << endl;
		} else if (choice == '6')
			list.display();
		else
			cout << "Invalid Option\n";

		cout << "Enter 'Y' to continue" << endl;
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
}

int main(){
	SinglyLinkedList list;

	displayChoice(list);

	return 0;
}

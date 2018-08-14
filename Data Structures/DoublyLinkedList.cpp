#include <iostream>
//#include <conio.h>
using namespace std;

enum ORDER { LINEAR , REVERSE };

class DoublyLinkedList{

	struct Node{
		int data;
		Node *next, *prev;
		Node(int d){
			next = prev = NULL;
			data = d;
		}
	};
	
	Node *head, *tail;
public:
	
	DoublyLinkedList(){
		head = tail = NULL;
	}
	
	void insertAtBeg(int data){
		Node *temp = new Node(data);
		if(head == NULL)
			head = tail = temp;
		else {
			temp->next = head;
			head->prev = temp;
			head = temp;
		}
	}
	
	void insertAtEnd(int data){
		Node *temp = new Node(data);
		if(head == NULL)
			head = tail = temp;
		else {
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
	}
	
	void insert(int pos, int data){
		Node *temp = new Node(data);
		if (head == NULL)
			head = tail = temp;
		else if (pos == 0){
			insertAtBeg(data);
		}
		else {
			Node *current = head;
			for (int i=0;i<pos;i++){
				if ((current = current->next) == NULL){
					if (i<pos-1)
						throw "Out of Bounds";
					insertAtEnd(data);
					return;
				}
			}
			temp->next = current;
			temp->prev = current->prev;
			current->prev->next = temp;
			current->prev = temp; 
		}
	}

	int deleteFromBeg(){
		if (head == NULL)
			throw "LL empty";
		else if (head == tail){
			int data = head->data;
			delete head;
			head = tail = NULL;
			return  data;
		} else {
			int data = head->data;
			head = head->next;
			delete head->prev;
			head->prev = NULL;
			return data;
		}
	}

	int deleteFromEnd(){
		if (head == NULL)
			throw "LL empty";
		else if (head == tail){
			int data = head->data;
			delete head;
			head = tail = NULL;
			return  data;
		} else {
			int data = tail->data;
			tail = tail->prev;
			delete tail->next;
			tail->next = NULL;
			return data;
		}
	}

	int deleteByPos(int pos){
		if (head == NULL)
			throw "LL empty";
		else if (pos == 0)
			return deleteFromBeg();
		else {
			Node *current = head;
			for (int i = 1; i <= pos; i++) {
				current = current->next;
				if (current == NULL)
					throw "Out Of Bounds";
			}
			if (current == tail)
				return deleteFromEnd();
			else {
				int data = current->data;
				current->prev->next = current->next;
				current->next->prev = current->prev;
				delete current;
				return data;
			}
		}
	}

	int deleteByData(int data){
		if (head == NULL)
			throw "LL empty";
		else {
			Node *current = head;
			while (current->data != data) {
				current = current->next;
				if (current == NULL)
					throw "Out Of Bounds";
			}
			if (current = head)
				return deleteFromBeg();
			else if (current == tail)
				return deleteFromEnd();
			else {
				int data = current->data;
				current->prev->next = current->next;
				current->next->prev = current->prev;
				delete current;
				return data;
			}
		}
	}

	void reverse(){
		if (head == tail || head == NULL)
			return;
		Node *current = head;
		while (current != NULL){
			Node *temp = current->next;
			current->next = current->prev;
			current->prev = temp;
			if (current = tail){
				tail = head;
				head = current;
			}
			current = temp;
		}
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

	int length(){
		int size = 0;
		Node *current = head;
		while(current != NULL){
			size++;
			current = current->next;
		}

		return size;
	}
	
	void display(ORDER order){
		Node *current;
		if (order == LINEAR)
			current = head;
		else
			current = tail;
		cout << "NULL <--";
		while(current!=NULL){
			cout << " " << current->data;
			if (order == LINEAR)
				current = current->next;
			else
				current = current->prev;
			if (current != NULL)
				cout << " <";
			cout << "--> ";
		}
		cout << "NULL" << endl;
	}
	
};

void displayChoice(DoublyLinkedList &list){
	char choice;
	do {
		cout << "Choose Option:\n1. Add Elements\n2. Remove Elements\n";
		cout << "3. Print length\n4. Reverse list\n5. Find indexOf\n";
		cout << "6. Display list\n";
		cin >> choice;
		if (choice == '1'){
			do {
				int data;
				cout << "Enter Integer to add\n";
				cin >> data;
				cout << "Choose Method:\n1. addAtBeg(int)\n2. addAtEnd(int)\n3. add(int, int)\n";
				cin >> choice;
				if (choice == '1')
					list.insertAtBeg(data);
				else if (choice == '2')
					list.insertAtEnd(data);
				else if(choice == '3'){
					cout << "Enter index: ";
					int pos;
					cin >> pos;
					list.insert(pos, data);
				} else
					cout << "Invalid Option\n";

				list.display(LINEAR);

				cout << "Enter 'Y' to add more\n";
				cin >> choice;
			} while (choice == 'Y' || choice == 'y');
		} else if (choice == '2'){
			do {
				cout << "Choose Method:\n1. deleteFromBeg\n2. deleteFromEnd\n3. By Position\n4. By Element\n";
				cin >> choice;
				if (choice == '1')
					cout << list.deleteFromBeg() << " removed\n";
				else if (choice == '2')
					cout << list.deleteFromEnd() << " removed\n";
				else if (choice == '3'){
					cout << "Enter Position: ";
					int pos;
					cin >> pos;
					cout << list.deleteByPos(pos) << " removed\n";
				} else if (choice == '4'){
					cout << "Enter data: ";
					int data;
					cin >> data;
					cout << list.deleteByData(data) << " removed\n";
				} else
					cout << "Invalid Option\n";
				list.display(LINEAR);

				cout << "Enter 'Y' to remove more\n";
				cin >> choice;
			} while (choice == 'Y' || choice == 'y');
		} else if (choice == '3'){
			cout << "Length of list is: " << list.length() << endl;
		} else if (choice == '4'){
			list.reverse();
			cout << "Reverse list is:" << endl;
			list.display(LINEAR);
		} else if (choice == '5'){
			cout << "Enter element";
			int data;
			cin >> data;
			int pos = list.indexOf(data);
			if (pos == -1)
				cout << "Element does not exist in list\n";
			else
				cout << data << " exists at position " << pos << endl;
		} else if (choice == '6'){
			cout << "Choose Method:\n1. LINEAR\n2. REVERSE\n";
			cin >> choice;
			if (choice == '1')
				list.display(LINEAR);
			else if (choice == '2')
				list.display(REVERSE);
			else
				cout  << "Invalid Option\n";
		}
		else
			cout << "Invalid Option\n";

		cout << "Enter 'Y' to continue" << endl;
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
}

int main(){
	DoublyLinkedList dLL;
	displayChoice(dLL);
	
	//getch();
	return 0;
}

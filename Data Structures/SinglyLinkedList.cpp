#include <iostream>
using namespace std;

template <class T>
class SinglyLinkedList{

	struct Node{
		T data;
		Node *next;
		Node(T d){
			data = d;
			next = NULL;
		}
	};
	
	Node *head, *tail;
	
public:

	SinglyLinkedList(){
		head = tail = NULL;
	}

	void addAtBeg(T data){
		Node *temp = new Node(data);
		if (head == NULL)
			head = tail = temp;
		else {
			temp->next = head;
			head = temp;
		}
	}

	void addAtEnd(T data){
		Node *temp = new Node(data);
		if (head == NULL)
			head = tail = temp;
		else {
			tail->next = temp;
			tail = temp;
		}
	}
	
	void add(int pos, T data){
		Node *temp = new Node(data);
		if (head == NULL)
			head = tail = temp;
		else if (pos == 0){
			addAtBeg(data);
		} else {
			Node *current = head, *previous = NULL;
			for(int i=0;i<pos;i++){
				if (current->next == NULL){
					addAtEnd(data);
					return;
				}
				previous = current;
				current = current->next;
			}
			temp->next = current;
			previous->next = temp;
		}
	}

	T removeAtBeg(){
		if (head == NULL)
			throw "List Empty";
		else if (head == tail){
			T data = head->data;
			delete head;
			head = tail = NULL;
			return data;
		} else {
			T data = head->data;
			Node *temp = head->next;
			delete head;
			head = temp;
			return data;
		}
	}

	T removeAtEnd(){
		if (head == NULL)
			throw "List Empty";
		else if (head == tail){
			T data = tail->data;
			delete tail;
			head = tail = NULL;
			return data;
		} else {
			T data = tail->data;
			Node *current = head;
			while(current->next != tail)
				current = current->next;
			current->next = NULL;
			delete tail;
			tail = current;
			return data;
		}
	}

	T removeByPos(int pos){
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
			T data = current->data;
			delete current;
			return data;
		}
	}

	T removeByEle(T data){
		if(head == NULL)
			throw "List Empty";
		else {
			Node *current = head, *previous = NULL;
			while (current->data != data){
				if(current->next == NULL)
					throw "Element not found";
				previous = current;
				current = current->next;
			}
			if (current == head)
				head = head->next;
			if (current == tail)
				tail = previous;
			if (previous != NULL)
				previous->next = current->next;
			T data = current->data;
			delete current;
			return data;
		}
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
		if(head == NULL || head == tail)
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

	int indexOf(T data){
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

	static SinglyLinkedList concatenate(SinglyLinkedList sll1, SinglyLinkedList sll2){
		SinglyLinkedList sll;
		if (sll1.head == NULL){
			sll.head = sll2.head;
			sll.tail = sll2.tail;
		} else if (sll2.head == NULL){
			sll.head = sll1.head;
			sll.tail = sll1.tail;
		} else {
			sll.head = sll1.head;
			sll1.tail->next = sll2.head;
			sll.tail = sll2.tail;
		}
		return sll;
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

template <class T>
void displayChoice(SinglyLinkedList<T> &list){
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

#include <iostream>
using namespace std;

template <class T>
class SortedLinkedList{

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

	SortedLinkedList(){
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
	
	void insert(T data){
		Node *temp = new Node(data);
		if (head == NULL)
			head = tail = temp;
		else {
			Node *current = head, *previous = NULL;
			while(current != NULL){
				if (current->data > data)
					break;
				previous = current;
				current = current->next;
			}
			if (previous == NULL)
				addAtBeg(data);
			else if (current == NULL)
				addAtEnd(data);
			else {
				temp->next = current;
				previous->next = temp;
			}
		}
	}

	T remove(T data){
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
	
	static SortedLinkedList merge(SortedLinkedList<T> list1, SortedLinkedList<T> list2){
		SortedLinkedList list;
		Node *ptr1 = list1.head;
		Node *ptr2 = list2.head;
		
		while (ptr1 != NULL && ptr2 != NULL){
			if (ptr1->data < ptr2->data){
				list.addAtEnd(ptr1->data);
				ptr1 = ptr1->next;
			} else {
				list.addAtEnd(ptr2->data);
				ptr2 = ptr2->next;
			}
		}
		
		while(ptr1 != NULL){
			list.addAtEnd(ptr1->data);
			ptr1 = ptr1->next;
		}
		while(ptr2 != NULL){
			list.addAtEnd(ptr2->data);
			ptr2 = ptr2->next;
		}
		
		return list;
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
void displayChoice(SortedLinkedList<T> &list){
	char choice;
	do {
		cout << "Choose Option:\n1. Add Elements\n2. Remove Elements\n";
		cout << "3. Merge\n4. Print length\n5. Display list\n";
		cin >> choice;
		if (choice == '1'){
			do {
				T data;
				cout << "Enter data to add\n";
				cin >> data;
				
				list.insert(data);

				list.display();

				cout << "Enter 'Y' to add more\n";
				cin >> choice;
			} while (choice == 'Y' || choice == 'y');
		} else if (choice == '2'){
			do {
				T data;
				cout << "Enter data to delete\n";
				cin >> data;
				
				list.remove(data);
				
				list.display();

				cout << "Enter 'Y' to remove more\n";
				cin >> choice;
			} while (choice == 'Y' || choice == 'y');
		} else if (choice == '3'){
			SortedLinkedList<T> list3 = SortedLinkedList<T>::merge(list, list);
			list3.display();
		} else if (choice == '4'){
			cout << "Length of list is: " << list.length() << endl;
		} else if (choice == '5')
			list.display();
		else
			cout << "Invalid Option\n";

		cout << "Enter 'Y' to continue" << endl;
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
}

int main(){
	SortedLinkedList<int> list;

	displayChoice<int>(list);

	return 0;
}

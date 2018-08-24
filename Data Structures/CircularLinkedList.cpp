#include <iostream>
using namespace std;

template <class Type>
class CircularLinkedList{

	struct Node{
		Type data;
		Node *next;
		Node(Type d){
			data = d;
			next = this;
		}
	};
	
	Node *tail;
	
public:

	CircularLinkedList(){
		tail = NULL;
	}

	void addAtBeg(Type data){
		Node *temp = new Node(data);
		if (tail == NULL)
			tail = temp;
		else {
			temp->next = tail->next;
			tail->next = temp;
		}
	}

	void addAtEnd(Type data){
		Node *temp = new Node(data);
		if (tail == NULL)
			tail = temp;
		else {
			temp->next  = tail->next;
			tail->next = temp;
			tail = temp;
		}
	}
	
	void add(int pos, Type data){
		Node *temp = new Node(data);
		if (tail == NULL)
			tail = temp;
		else if (pos == 0){
			addAtBeg(data);
		} else {
			Node *current = tail->next, *previous = NULL;
			for(int i=0;i<pos;i++){
				if (current->next == tail->next){
					if (i+1 < pos)
						throw "Out Of Bounds";
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

	Type removeAtBeg(){
		if (tail == NULL)
			throw "List Empty";
		else if (tail == tail->next){
			Type data = tail->data;
			delete tail;
			tail = NULL;
			return data;
		} else {
			Node *head = tail->next;
			Type data = head->data;
			Node *temp = head->next;
			delete head;
			tail->next = temp;
			return data;
		}
	}

	Type removeAtEnd(){
		if (tail == NULL)
			throw "List Empty";
		else if (tail == tail->next){
			Type data = tail->data;
			delete tail;
			tail = NULL;
			return data;
		} else {
			Type data = tail->data;
			Node *current = tail->next;
			while(current->next != tail)
				current = current->next;
			current->next = tail->next;
			delete tail;
			tail = current;
			return data;
		}
	}

	Type removeByPos(int pos){
		if (tail == NULL)
			throw "List Empty";
		else if (pos == 0)
			return removeAtBeg();
		else {
			Node *current = tail->next, *previous = NULL;
			for (int i = 1; i <= pos; ++i){
				previous = current;
				current = current->next;
				if(current == tail->next)
					throw "Out of Bounds"; 
			}
			if (current == tail)
				return removeAtEnd();
			else {
				Type data = current->data;
				previous->next = current->next;
				delete current;
				return data;
			}
		}
	}

	Type removeByEle(Type data){
		if (tail == NULL)
			throw "List Empty";
		else {
			Node *current = tail->next, *previous = NULL;
			while (current->data != data){
				previous = current;
				current = current->next;
				if(current == tail->next)
					throw "Out of Bounds"; 
			}
			if (current == tail->next)
				return removeAtBeg();
			else if (current == tail)
				return removeAtEnd();
			else {
				Type data = current->data;
				previous->next = current->next;
				delete current;
				return data;
			}
		}
	}

	int length(){
		int size = 0;
		Node *current = tail->next;
		do {
			size++;
			current = current->next;
		} while (current != tail->next);

		return size;
	}

	void reverse(){
		Node *head = tail->next;
		if(tail == NULL || head == tail)
			return;
		tail = head;
		Node *current = head, *next = head->next;
		while(next != head){
			Node *temp = next->next;
			next->next = current;
			current = next;
			next = temp;
		}
		head->next = NULL;
		tail->next = current;
	}

	int indexOf(Type data){
		Node *current = tail->next;
		int pos = 0;
		do {
			if (current->data == data)
				return pos;
			pos++;
			current = current->next;
		} while (current != tail->next);

		return -1;
	}
	
	void display(){
		Node *current = tail->next;
		do {
			cout << current-> data << "-->";
			current = current->next;
		} while (current != tail->next);
		cout << "NULL" << endl;
	}
	
	
};

template <class Type>
void displayChoice(CircularLinkedList<Type> &list){
	char choice;
	do {
		cout << "Choose Option:\n1. Add Elements\n2. Remove Elements\n";
		cout << "3. Print length\n4. Reverse list\n5. Find indexOf\n";
		cout << "6. Display list\n";
		cin >> choice;
		if (choice == '1'){
			do {
				Type data;
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
					Type data;
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
			Type data;
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
	CircularLinkedList<float> list;

	float a =0.6756324;
	cout << a;
	displayChoice<float>(list);
	

	return 0;
}

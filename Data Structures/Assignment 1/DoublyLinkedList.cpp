#include <iostream>
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
					if (i+1 < pos-1)
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

	int length(){
		int size = 0;
		Node *current = head;
		while(current != NULL){
			size++;
			current = current->next;
		}

		return size;
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

	DoublyLinkedList copy(){
		DoublyLinkedList new_DLL;
		Node *current = head;
		while (current != NULL){
			new_DLL.insertAtEnd(current->data);
			current =current->next;
		}
		return new_DLL;
	}

	void clear(){
		Node *current = head, *next;
		while (current != NULL){
			next = current->next;
			delete current;
			current = next;
		}
		head = tail = NULL;
	}

	int sumAll(){
		int sum = 0;
		Node *current = head;
		while (current != NULL){
			sum += current->data;
			current = current->next;
		}
		return sum;
	}

	void deleteAlternate(){
		if (head == NULL || head == tail)
			return;
		else {
			Node *current = head->next, *previous = head;
			int count = 2;
			while (current != NULL){
				if (count % 2 == 0){
					previous->next = current->next;
					if (current == tail)
						tail = previous;
					else
						current->next->prev = previous;
					delete current;
				} else {
					// Previous increments only when node not deleted
					previous = previous->next;
				}
				current = previous->next;
				count++;
			}
		}
	}

	void insertMid(int data){
		int mid = length()/2;
		insert(mid, data);
	}

	int deleteMid(){
		int  mid = length()/2;
		return deleteByPos(mid);
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

	friend ostream & operator << (ostream &out, DoublyLinkedList &DLL);

	static DoublyLinkedList concatenate(DoublyLinkedList dll1, DoublyLinkedList dll2){
		DoublyLinkedList dll;
		if (dll1.head == NULL){
			dll.head = dll2.head;
			dll.tail = dll2.tail;
		} else if (dll2.head == NULL){
			dll.head = dll1.head;
			dll.tail = dll1.tail;
		} else {
			dll.head = dll1.head;
			dll1.tail->next = dll2.head;
			dll.tail = dll2.tail;
		}
		return dll;
	}

	DoublyLinkedList operator + (DoublyLinkedList dll2)	{
		DoublyLinkedList dll;
		if (head == NULL){
			dll.head = dll2.head;
			dll.tail = dll2.tail;
		} else if (dll2.head == NULL){
			dll.head = head;
			dll.tail = tail;
		} else {
			dll.head = head;
			tail->next = dll2.head;
			dll.tail = dll2.tail;
		}
		return dll;
	}

	bool compareTo(DoublyLinkedList sll2){
		Node *current1 = head, *current2 = sll2.head;
		while(current1 != NULL || current2 != NULL){
			if (current1->data != current2->data)
				return false;
			current1 = current1->next;
			current2 = current2->next;
			if (current1 == NULL ^ current2 == NULL)
				return false;
		}
		return true;
	}

	bool operator == (DoublyLinkedList sll2){
		Node *current1 = head, *current2 = sll2.head;
		while(current1 != NULL || current2 != NULL){
			if (current1->data != current2->data)
				return false;
			current1 = current1->next;
			current2 = current2->next;
			// If the size of two lists is different
			if (current1 == NULL ^ current2 == NULL)
				return false;
		}
		return true;
	}
	
};

ostream & operator << (ostream &out, DoublyLinkedList &DLL) {
	DoublyLinkedList::Node *current = DLL.head;
	while (current != NULL){
		out << current->data << "-->";
		current = current->next;
	}
	out << "NULL" << endl;
	return out;
}
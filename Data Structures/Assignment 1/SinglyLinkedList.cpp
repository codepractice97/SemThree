#include <iostream>
using namespace std;

class SinglyLinkedList{

	struct Node{
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

	void addAtBeg(int data){
		Node *temp = new Node(data);
		if (head == NULL)
			head = tail = temp;
		else {
			temp->next = head;
			head = temp;
		}
	}

	void addAtEnd(int data){
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

	int removeAtBeg(){
		if (head == NULL)
			throw "List Empty";
		else if (head == tail){
			int data = head->data;
			delete head;
			head = tail = NULL;
			return data;
		} else {
			int data = head->data;
			Node *temp = head->next;
			delete head;
			head = temp;
			return data;
		}
	}

	int removeAtEnd(){
		if (head == NULL)
			throw "List Empty";
		else if (head == tail){
			int data = tail->data;
			delete tail;
			head = tail = NULL;
			return data;
		} else {
			int data = tail->data;
			Node *current = head;
			while(current->next != tail)
				current = current->next;
			current->next = NULL;
			delete tail;
			tail = current;
			return data;
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
			int data = current->data;
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

	SinglyLinkedList copy(){
		SinglyLinkedList new_SLL;
		Node *current = head;
		while (current != NULL){
			new_SLL.addAtEnd(current->data);
			current = current->next;
		}
		return new_SLL;
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
					delete current;
				} else {
					previous = previous->next;
				}
				current = previous->next;
				count++;
			}
		}
	}

	void insertMid(int data){
		int mid = length()/2;
		add(mid, data);
	}

	int deleteMid(){
		int  mid = length()/2;
		return removeByPos(mid);
	}
	
	void display(){
		Node *current = head;
		while(current != NULL){
			cout << current-> data << "-->";
			current = current->next;
		}
		cout << "NULL" << endl;
	}
	
	friend ostream & operator << (ostream &out, SinglyLinkedList &SLL);

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

	SinglyLinkedList operator + (SinglyLinkedList sll2)	{
		SinglyLinkedList sll;
		if (head == NULL){
			sll.head = sll2.head;
			sll.tail = sll2.tail;
		} else if (sll2.head == NULL){
			sll.head = head;
			sll.tail = tail;
		} else {
			sll.head = head;
			tail->next = sll2.head;
			sll.tail = sll2.tail;
		}
		return sll;
	}

	bool compareTo(SinglyLinkedList sll2){
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

	bool operator == (SinglyLinkedList sll2){
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

ostream & operator << (ostream &out, SinglyLinkedList &SLL){
	SinglyLinkedList::Node *current = SLL.head;
	while (current != NULL){
		out << current->data << "-->";
		current = current->next;
	}
	out << "NULL" << endl;
	return out;
}
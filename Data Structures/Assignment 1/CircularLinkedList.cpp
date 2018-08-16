#include <iostream>
using namespace std;

class CircularLinkedList{

	struct Node{
		int data;
		Node *next;
		Node(int d){
			data = d;
			next = this;
		}
	};
	
	Node *tail;
	
public:

	CircularLinkedList(){
		tail = NULL;
	}

	void addAtBeg(int data){
		Node *temp = new Node(data);
		if (tail == NULL)
			tail = temp;
		else {
			temp->next = tail->next;
			tail->next = temp;
		}
	}

	void addAtEnd(int data){
		Node *temp = new Node(data);
		if (tail == NULL)
			tail = temp;
		else {
			temp->next  = tail->next;
			tail->next = temp;
			tail = temp;
		}
	}
	
	void add(int pos, int data){
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

	int removeAtBeg(){
		if (tail == NULL)
			throw "List Empty";
		else if (tail == tail->next){
			int data = tail->data;
			delete tail;
			tail = NULL;
			return data;
		} else {
			Node *head = tail->next;
			int data = head->data;
			Node *temp = head->next;
			delete head;
			tail->next = temp;
			return data;
		}
	}

	int removeAtEnd(){
		if (tail == NULL)
			throw "List Empty";
		else if (tail == tail->next){
			int data = tail->data;
			delete tail;
			tail = NULL;
			return data;
		} else {
			int data = tail->data;
			Node *current = tail->next;
			while(current->next != tail)
				current = current->next;
			current->next = tail->next;
			delete tail;
			tail = current;
			return data;
		}
	}

	int removeByPos(int pos){
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
				int data = current->data;
				previous->next = current->next;
				delete current;
				return data;
			}
		}
	}

	int removeByEle(int data){
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
				int data = current->data;
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

	int indexOf(int data){
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

	CircularLinkedList copy(){
		CircularLinkedList new_CLL;
		Node *current = tail->next;
		do {
			new_CLL.addAtEnd(current->data);
			current = current->next;
		} while (current != tail->next);
		return new_CLL;
	}

	void clear(){
		Node *current = tail->next, *next;
		do {
			next = current->next;
			delete current;
			current = next;
		} while (current != tail->next);
		tail = NULL;
	}

	int sumAll(){
		int sum = 0;
		Node *current = tail->next;
		do {
			sum += current->data;
			cout << current->data << " ";
			current = current->next;
		} while (current != tail->next);
		return sum;
	}

	void deleteAlternate(){
		if (tail->next == NULL || tail == tail->next)
			return;
		else {
			Node *current = tail->next->next, *previous = tail->next;
			int count = 2;
			do {
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
			} while (current != tail->next);
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
		Node *current = tail->next;
		do {
			cout << current-> data << "-->";
			current = current->next;
		} while (current != tail->next);
		cout << "HEAD" << endl;
	}
	
	friend ostream & operator << (ostream &out, CircularLinkedList &CLL);

	static CircularLinkedList concatenate(CircularLinkedList cll1, CircularLinkedList cll2){
		CircularLinkedList cll;
		if (cll1.tail == NULL){
			cll.tail = cll2.tail;
		} else if (cll2.tail == NULL){
			cll.tail = cll1.tail;
		} else {
			cll.tail = cll2.tail;
			cll.tail->next = cll1.tail->next;
			cll1.tail->next = cll2.tail->next;
		}
		return cll;
	}

	CircularLinkedList operator + (CircularLinkedList cll2)	{
		CircularLinkedList cll;
		if (tail == NULL){
			cll.tail = cll2.tail;
		} else if (cll2.tail == NULL){
			cll.tail = tail;
		} else {
			cll.tail = cll2.tail;
			cll.tail->next = tail->next;
			tail->next = cll2.tail->next;
		}
		return cll;
	}

	bool compareTo(CircularLinkedList cll2){
		Node *current1 = tail->next, *current2 = cll2.tail->next;
		do {
			if (current1->data != current2->data)
				return false;
			current1 = current1->next;
			current2 = current2->next;
			if (current1 == tail->next ^ current2 == cll2.tail->next)
				return false;
		} while(current1 != tail->next || current2 != cll2.tail->next);
		return true;
	}

	bool operator == (CircularLinkedList cll2){
		Node *current1 = tail->next, *current2 = cll2.tail->next;
		do {
			if (current1->data != current2->data)
				return false;
			current1 = current1->next;
			current2 = current2->next;
			if (current1 == tail->next ^ current2 == cll2.tail->next)
				return false;
		} while(current1 != tail->next || current2 != cll2.tail->next);
		return true;
	}

};

ostream & operator << (ostream &out, CircularLinkedList &CLL){
	CircularLinkedList::Node *current = CLL.tail->next;
	do {
		out << current->data << "-->";
		current = current->next;
	} while (current != CLL.tail->next);
	out << "HEAD" << endl;
	return out;
}
#include <iostream>
using namespace std;
class SortedLinkedList {

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

	SortedLinkedList(){
		head = tail = NULL;
	}

	void add(int data){
		Node *temp = new Node(data);
		if (head == NULL)
			head = tail = temp;
		else {
			Node *current = head, *previous = NULL;
			while (current != NULL && current->data < data ){
				previous = current;
				current = current->next;
			}
			temp->next = current;
			if (current == head)
				head = temp;
			else
				previous->next = temp;
			if (current == tail)
				tail = temp;
		}
	}

	int remove(int data){
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

	void merge(SortedLinkedList sll2){
		Node *current = sll2.head;
		while (current != NULL){
			add(current->data);
			current = current->next;
		}
	}

};
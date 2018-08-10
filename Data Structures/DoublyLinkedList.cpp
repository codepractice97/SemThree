#include <iostream>
#include <conio.h>
using namespace std;

enum ORDER { LINEAR , REVERSE };

class DoublyLinkedList{

	struct Node{
		int data;
		Node *next;
		Node *prev;
		Node(int d){
			next = NULL;
			prev = NULL;
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
	
	void insertFromStart(int pos, int data){
		Node *temp = new Node(data);
		if (head = NULL)
			head= tail = temp;
		else if (pos = 0){
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
	
	void insertFromEnd(int pos, int data){
		Node *temp = new Node(data);
		if (head = NULL)
			head= tail = temp;
		else if (pos = 0){
			insertAtEnd(data);	
		}
		else {
			Node *current = tail;
			for (int i=0;i<pos;i++){
				if ((current = current->prev) == NULL){
					if (i<pos-1)
						throw "Out of Bounds";
					insertAtBeg(data);
					return;
				}
			}
			temp->next = current;
			temp->prev = current->prev;
			current->prev->next = temp;
			current->prev = temp; 
		}
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

int main(){
	DoublyLinkedList dLL;
	dLL.insertAtBeg(2);
	dLL.insertAtBeg(4);
	dLL.insertAtBeg(7);
	dLL.insertFromStart(1,22);
	dLL.insertFromEnd(1,11);
	dLL.display(REVERSE); // LINEAR or REVERSE
	
	getch();
	return 0;
}
	

#include <iostream>
using namespace std;

template <class T>
class Queue{

	struct Node{
		T data;
		Node *next;
		Node(T d){
			data = d;
			next = NULL;
		}
	};
	
	Node *front, *rear;
	
public:

	Queue(){
		front = rear = NULL;
	}

	void enqueue(T data){
		Node *temp = new Node(data);
		if (isEmpty())
			front = rear = temp;
		else {
			rear->next = temp;
			rear = temp;
		}
	}

	T dequeue(){
		if (isEmpty())
			throw "Queue Underflow";
		else if (front == rear){
			T data = front->data;
			delete front;
			front = rear = NULL;
			return data;
		} else {
			T data = front->data;
			Node *temp = front->next;
			delete front;
			front = temp;
			return data;
		}
	}
	
	T peek(){
		if (isEmpty())
			throw "Queue Underflow";
		else {
			return front->data;
		}
	}
	
	bool isEmpty(){
		return front == NULL;
	}

	int size(){
		int size = 0;
		Node *current = front;
		while(current != NULL){
			size++;
			current = current->next;
		}

		return size;
	}

	void display(){
		Node *current = front;
		while(current != NULL){
			cout << current-> data << "-->";
			current = current->next;
		}
		cout << "NULL" << endl;
	}
	
	void clear(){
		while(!isEmpty())
			dequeue();
	}
	
};
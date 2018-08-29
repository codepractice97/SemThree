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

template <class T>
void displayChoice(Queue<T> &queue){
	char choice;
	do {
		cout << "Choose Option:\n1. Enqueue\n2. Dequeue\n3. Peek\n";
		cout << "4. Print size\n5. Display Stack\n";
		cin >> choice;
		if (choice == '1'){
			do {
				T data;
				cout << "Enter data to enqueue\n";
				cin >> data;
				queue.enqueue(data);

				queue.display();

				cout << "Enter 'Y' to enqueue more\n";
				cin >> choice;
			} while (choice == 'Y' || choice == 'y');
		} else if (choice == '2'){
			do {
				cout << "Element dequeued: " << queue.dequeue() << endl;
				queue.display();

				cout << "Enter 'Y' to dequeue more\n";
				cin >> choice;
			} while (choice == 'Y' || choice == 'y');
		} else if (choice == '3'){
			cout << "Front Element is: " << queue.peek() << endl;
		} else if (choice == '4'){
			cout << "Size of queue is: " << queue.size() << endl;
		} else if (choice == '5'){
			queue.display();
		} else
			cout << "Invalid Option\n";

		cout << "Enter 'Y' to continue" << endl;
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
}

int main(){
	Queue<float> queue;

	displayChoice<float>(queue);

	return 0;
}

#include <iostream>
using namespace std;

template <class Type>
class Queue {

	Type *A;
	int size, front, rear;

public:

	Queue(int s){
		size = s;
		A = new Type[size];
		front = rear = -1;
	}

	bool isEmpty() { return front == -1; }

	bool isFull() { return (rear+1)%size == front; }

	void enqueue(Type data){
		if (isFull())
			throw "Queue Overflow";
		else {
			rear = (rear+1)%size;
			A[rear] = data;
			if (front == -1)
				front = 0;
		}
	}

	Type dequeue(){
		if (isEmpty())
			throw "Queue Underflow";
		else {
			Type data = A[front];
			if (front == rear)
				front = rear = -1;
			else
				front = (front + 1) % size;
			return data;
		}
	}

	Type peek(){
		if (isEmpty())
			throw "Queue Underflow";
		else
			return A[front];
	}

	void display(){
		if (isEmpty()){
			cout << "Queue Empty";
			return;
		}
		cout << "Queue: ";
		for (int i=front; i != rear; i = (i+1)%size)
			cout << A[i] << " ";
		cout << A[rear] << endl;
	}
	
	void clear(){
		front = rear = -1;
	}
};

int main(){
	Queue<int> queue(50);
	queue.enqueue(11);
	queue.enqueue(12);
	queue.enqueue(13);
	queue.enqueue(14);
	queue.enqueue(145);
	queue.enqueue(16);
	queue.enqueue(18);
	queue.enqueue(69);
	queue.display();
	cout << "Dequeued: " << queue.dequeue() << endl;
	cout << "Dequeued: " << queue.dequeue() << endl;
	cout << "Dequeued: " << queue.dequeue() << endl;
	cout << "Peeked: " << queue.peek() << endl;
	queue.enqueue(6969);
	
	queue.display();
}

#include <iostream>
#include <ctime>
#include <unistd.h>
#include <cstdlib>
using namespace std;

class Buffer{
	int *A, size;
	int front, rear;

public:

	Buffer(){

	}

	Buffer(int s){
		front = rear = -1;
		size = s;
		A = new int[size];
	}

	bool isFull(){
		return (rear+1)%size == front;
	}

	bool isEmpty(){
		return front == -1;
	}

	void enqueue(int data){
		if (isFull())
			throw 0;
		else {
			rear = (rear+1)%size;
			A[rear] = data;
			if (front == -1)
				front = 0;
		}
	}

	int dequeue(){
		if (isEmpty())
			throw 1;
		else {
			int value = A[front];
			front = (front+1)%size;
			if ((rear+1)%size == front)
				front = rear = -1;
			return value;
		}
	}

	void display(){
		if (isEmpty())
			throw 2;
		int index = front;
		int count = 1;
		while(index != rear) {
			cout<<count++<<".\t"<<A[index]<<"\n";
			index = (index+1) % size;
		}
		cout<<count++<<".\t"<<A[rear]<<"\n";
	}
};

class ProducerConsumer{
	Buffer B;
	void input(){
		int size;
		cout << "Enter buffer size: ";
		cin >> size;
		Buffer nB(size);
		B = nB;
	}

	int producer(){
		int a;
		cout << "Enter data to be produced: ";
		cin >> a;
		cout << "Produced: " << a << endl;
		return a;
	}

	void consumer(int x){
		cout << "Consumed: " << x << endl;
	}

public:

	void run(){
		input();
		int ch;
		char y;
		B.enqueue(producer());
		while(true)
		{
			try
			{				
				ch=rand()%2;
				if(ch==0)
					B.enqueue(producer());
				else
					consumer(B.dequeue());
				cout<<"\n\nPress N to exit or Press B to see Buffer else any other key to continue: ";
				cin>>y;
				if(y=='n'||y=='N')
					exit(0);
				if(y=='b'||y=='B')
					B.display();
			}
			catch(int x)
			{
				if(x==0)
					cout<<"\nProduction halted as Buffer is Full";
				else if(x==1)
					cout<<"\nConsumption halted as Buffer is Empty";
				else
					cout<<"\n Buffer is empty";
			}
			usleep(100000);
		}
	}
};

int main() {
	srand(time(NULL));
	ProducerConsumer p;
	p.run();

	return 0;
}


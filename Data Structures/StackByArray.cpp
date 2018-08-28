#include <iostream>
using namespace std;

template <class Type>
class Stack {

	Type *A;
	int size, top;

public:

	Stack(int s){
		size = s;
		A = new Type[size];
		top = -1;
	}

	bool isEmpty() { return top == -1; }

	bool isFull() { return top == size - 1; }

	void push(Type data){
		if (isFull())
			throw "Stack Overflow";
		else {
			top++;
			A[top] = data;
		}
	}

	Type pop(){
		if (isEmpty())
			throw "Stack Underflow";
		else {
			Type data = A[top];
			top--;
			return data;
		}
	}

	Type peek(){
		if (isEmpty())
			throw "Stack Underflow";
		else
			return A[top];
	}

	void display(){
		cout << "Stack: ";
		for (int i=top;i > -1;i--)
			cout << A[i] << " ";
		cout << endl;
	}
};

int main(){
	Stack<int> stack(50);
	stack.push(11);
	stack.push(12);
	stack.push(13);
	stack.push(14);
	stack.push(145);
	stack.push(16);
	stack.push(18);
	stack.push(69);
	stack.display();
	cout << "Popped: " << stack.pop() << endl;
	cout << "Popped: " << stack.pop() << endl;
	cout << "Popped: " << stack.pop() << endl;
	cout << "Peeked: " << stack.peek() << endl;
	stack.push(6969);
	
	stack.display();
}

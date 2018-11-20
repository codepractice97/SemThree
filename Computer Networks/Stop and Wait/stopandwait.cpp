#include <iostream>
using namespace std;

class Receiver {
public:
	int data[50], size, sequenceNumber = 0;

	int set(int data, int sn){
		if (sn == sequenceNumber){
			data[size] == data;
			size++;
			display(data, size);
			return !sequenceNumber;
		} else {
			cout << "Duplicate Frame Discarded" << endl;
			display(data, size);
		}
	}
};

class Sender {
public:
	int data[50], size, sequenceNumber = 0;
	Receiver receiver;

	void transfer(){
		for(int i=0; i < size;){
			try {
				int ack = receiver.set(data[i], sequenceNumber);
				if (ack != sequenceNumber){
					i++; sequenceNumber = !sequenceNumber;
				}
				else
					cout << "Data lost" << endl;
			} catch(const int &requestTimeOut){
				cout << "Acknowledgement lost" << endl;
			}
		}
	}

};

void display(int *A, int size){
	for (int i = 0;i < size; i++)
		cout << A[i] << " ";
	cout << endl;
}


int main(){
	transfer();
}
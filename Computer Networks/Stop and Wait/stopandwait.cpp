#include <iostream>
#include <ctime>
using namespace std;

class Receiver {
public:
	int sequenceNumber = 0;
	string data = "";

	int set(char d, int sn){
		int network_outcome = rand() % 3;
		if (network_outcome == 0) {
			cout << "RECEIVER: Data Received\n";
			if (sn == sequenceNumber){
				data += d;
				sequenceNumber = !sequenceNumber;
			} else {
				cout << "RECEIVER: Duplicate Frame Discarded\n";
			}
			cout << "RECEIVER: Data: " << data << endl;
			return sequenceNumber;
		} else if (network_outcome == 1) {
			cout << "RECEIVER: Data Not Received\n";
			cout << "RECEIVER: Data: " << data << endl;
			throw 0;
		} else if (network_outcome == 2) {
			cout << "RECEIVER: Data Received but Acknowledgement lost\n";
			if (sn == sequenceNumber){
				data += d;
				sequenceNumber = !sequenceNumber;
			} else {
				cout << "RECEIVER: Duplicate Frame Discarded" << endl;	
			}
			cout << "RECEIVER: Data: " << data << endl;
			throw 0;
		}
	}
};

class Sender {
public:
	int size, sequenceNumber = 0;
	string data;
	Receiver receiver;

	void input(){
		cout << "Enter data to transfer:\n";
		cin >> data;
		size = data.length();
	}

	void transfer(){
		for(int i=0; i < size;){
			try {
				cout << "SENDER: Data Sent(" << data.at(i) << ")\n";
				int ack = receiver.set(data.at(i), sequenceNumber);
				if (ack != sequenceNumber){
					i++;
					sequenceNumber = !sequenceNumber;
				}
			} catch(const int &requestTimeOut){
				cout << "SENDER: Data/Acknowledgement lost" << endl;
			}
		}
	}

};


int main(){
	srand(time(NULL));

	Sender sender;
	sender.input();
	sender.transfer();

	return 0;
}
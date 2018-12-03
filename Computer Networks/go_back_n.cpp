// -1 stored in ack to simulate when acknowledgement does not reach sender 
// It has been assumed that the window size is 2BD + 1
#include <iostream>
#include <deque>
#include <cmath>
#include <ctime>
using namespace std;

struct Frame{
	int seq, ack;
	char data;
	Frame(int s, char d){
		seq = s;
		data = d;
	}
	void setAck(int a){
		ack = a;
	}
};

class Receiver{
	string data = "";
	int seq = 0;
public:
	int seq_size;

	int receive(Frame frame){
		int network_outcome = rand() % 10;
		if (network_outcome >= 4) {
			cout << "RECEIVER: Data Received\n";
			if (frame.seq == seq){
				data += frame.data;
				seq = (seq + 1) % seq_size;
				cout << "RECEIVER: " << data << endl;
				return seq;
			} else {
				cout << "RECEIVER: Data Discarded\n";
				cout << "RECEIVER: " << data << endl;
				return (frame.seq + 1) % seq_size;
			}
		} else if (network_outcome > 2) {
			cout << "RECEIVER: Data Not Received\n";
			cout << "RECEIVER: " << data << endl;
			return -1;
		} else if (network_outcome >= 0) {
			cout << "RECEIVER: Data Received but Acknowledgement lost\n";
			if (frame.seq == seq){
				data += frame.data;
				seq = (seq + 1) % seq_size;
				cout << "RECEIVER: " << data << endl;
				return -1;
			} else {
				cout << "RECEIVER: Data Discarded\n";
				cout << "RECEIVER: " << data << endl;
				return -1;
			}
		}
	}
} receiver;

class Sender{
	deque <Frame> window;
	int w_size, seq_size;
	string data;
public:
	void transfer(){
		int i = 0;
		do {
			while (window.size() < w_size && i < data.length()){
				Frame frame(i % seq_size, data.at(i));
				cout << "SENDER: " << "Frame Sent(" 
					<< frame.seq << ", " << frame.data << ")" << endl;
				frame.setAck(receiver.receive(frame));
				window.push_back(frame);
				i++;
			}
			if ((window.front()).ack ==  ((window.front()).seq + 1) % seq_size){
				window.pop_front();
			} else {
				cout << "SENDER: " << "Timeout for frame("
					<< (i - window.size()) << ")" << endl;
				for (int j = 0; j < window.size(); j++){
					cout << "SENDER: " << "Frame Sent(" << (window.at(j)).seq 
						<< ", " << (window.at(j)).data << ")\n";
					(window.at(j)).setAck(receiver.receive(window.at(j)));
				}
			}
		} while (window.size() != 0);

	}

	void input(){
		cout << "Enter data to be transfered (Each Frame is of 1 bit)\n";
		cin >> data;
		cout << "Enter number of bits of sequence: ";
		int m;
		cin >> m;
		seq_size = pow(2, m);
		w_size = seq_size - 1;
		receiver.seq_size = seq_size;
	}

} sender;

int main(){
	srand(time(NULL));
	sender.input();
	sender.transfer();

	return 0;
}
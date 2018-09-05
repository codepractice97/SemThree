#include <iostream>
using namespace std;

struct Process{
	string p_name;
	int b_time, arr_time, ta_time, wait_time, priority;
};

struct Processes{
	int size;
	Process *p;
	Processes(int s){
		size = s;
		p = new Process[s];
	}
	Process* proc(int i) { return &p[i]; }
};

void displayProcesses(Processes *P){
	cout << "PID\tBurst Time\tArrival Time\t";
	cout << "Wait Time\tTurn Aroud Time\tPriority" << endl;
	for (int i=0; i<P->size; i++){
		cout << P->proc(i)->p_name << "\t\t";
		cout << P->proc(i)->b_time << "\t\t";
		cout << P->proc(i)->arr_time << "\t\t";
		cout << P->proc(i)->wait_time << "\t\t";
		cout << P->proc(i)->ta_time << "\t\t";
		cout << P->proc(i)->priority << endl;
	}
}

void displayResults(Processes *P){
	float avg_ta_time, avg_wait_time;
	for (int i=0; i<P->size; i++){
		avg_wait_time += P->proc(i)->wait_time;
		avg_ta_time += P->proc(i)->ta_time;
	}
	avg_ta_time /= P->size;
	avg_wait_time /= P->size;
	cout << "Average turn around time: " << avg_ta_time << endl;
	cout << "Average waiting time: " << avg_wait_time << endl;

}

class Scheduler{
public:

	void FCFS(Processes *P){
		cout << "OK1";
		int time_spent = 0;
		for (int i=0; i<P->size; i++){
			if (P->proc(i)->arr_time < time_spent)
				P->proc(i)->wait_time = time_spent - P->proc(i)->arr_time;
			else
				P->proc(i)->wait_time = 0;
			
			if (P->proc(i)->arr_time < time_spent)
				P->proc(i)->ta_time = time_spent + P->proc(i)->b_time - P->proc(i)->arr_time;
			else
				P->proc(i)->ta_time = P->proc(i)->b_time;

			time_spent += P->proc(i)->b_time;
		}
		cout << "OK2";
		
		displayProcesses(P);
		displayResults(P);
	}

	void SRJF(Processes *P){
		
	}
	
	void SJF(Processes *P){
		sort(P);
		FCFS(P);
	}
	
	void sort(Processes *P){
		Process temp;
		int time_spent = 0;
		for(int i=0;i<P->size;i++) {
			for(int j=0;j<P->size-1;j++) {
				if( P->proc(j+1)->b_time < P->proc(j)->b_time || 
						P->proc(j)->arr_time > time_spent ){
					temp = P->p[j+1];
					P->p[j+1] = P->p[j];
					P->p[j] = temp;
				}
			}
			time_spent += P->proc(i)->b_time;
		}
	}
	
};

Processes input(){
	cout << "Enter number of processes to enter: ";
	int size;
	cin >> size;
	Processes processes(size);
	for(int i=0;i<size;i++){
		//cout << "Enter process name: ";
		cin >> processes.proc(i)->p_name;
		//cout << "Enter burst time: ";
		cin >> processes.proc(i)->b_time;
		//cout << "Enter arrival time: ";
		cin >> processes.proc(i)->arr_time;
	}
	return processes;
}

int main(){
	Processes p = input();
	
	Scheduler S;
	S.FCFS(&p);
	S.SJF(&p);
}

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
			calculateProcessExecution(P->proc(i), time_spent);
		}
		cout << "OK2";
		displayProcesses(P);
		displayResults(P);
	}

	void SRJF(Processes *P){
		sortJobsArrivalAscending(P);
		int time_spent = 0;
		Processes *activeP = new Processes(P->size);
		activeP->size = 0;
		int execute_count = 0;
		for (int i=0; i< P->size ; i++){
			int current_arrival_time = P->proc(activeP->size)->arr_time;
			for (int j=activeP->size; j< P->size &&
				 P->proc(j)->arr_time <= current_arrival_time; j++){
				cout << "Hello\n";
				activeP->p[activeP->size] = *P->proc(j);
				activeP->size++;
			}
			sortJobsBurstAscending(activeP);
			calculateProcessExecution(&activeP->p[execute_count], time_spent);
			execute_count++;
		}
		
		displayProcesses(activeP);
		displayResults(activeP);
	}
	
	void SJF(Processes *P){
		sortJobsBurstAscending(P);
		FCFS(P);
	}
	
	void sortJobsBurstAscending(Processes *P){
		Process temp;
		for(int i=0;i<P->size;i++) {
			for(int j=0;j<P->size-1;j++) {
				if( P->proc(j+1)->b_time < P->proc(j)->b_time ){
					temp = P->p[j+1];
					P->p[j+1] = P->p[j];
					P->p[j] = temp;
				}
			}
		}
	}

	void sortJobsArrivalAscending(Processes *P){
		Process temp;
		for(int i=0;i<P->size;i++) {
			for(int j=0;j<P->size-1;j++) {
				if( P->proc(j+1)->arr_time < P->proc(j)->arr_time ){
					temp = P->p[j+1];
					P->p[j+1] = P->p[j];
					P->p[j] = temp;
				}
			}
		}
	}
	
	void calculateProcessExecution(Process *P, int &time_spent){
		cout << "Time SPent: " << time_spent <<endl;
		if (P->arr_time < time_spent){
			P->wait_time = time_spent - P->arr_time;
			P->ta_time = time_spent + P->b_time - P->arr_time;
		}
		else{
			P->wait_time = 0;
			P->ta_time = P->b_time;
		}
		
		time_spent += P->b_time;
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
	S.SRJF(&p);
}

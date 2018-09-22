#include <iostream>
#include <deque>
using namespace std;

struct Process{
	int p_name;
	int b_time, arr_time, ta_time, wait_time, priority;
	int progress;
};

void displayProcesses(deque <Process> &P){
	cout << "PID\tBurst Time\tArrival Time\t\t";
	cout << "Wait Time\tTurn Aroud Time\tPriority" << endl;
	for (int i = 0; i < P.size(); i++){
		Process process = P.at(i);
		cout << process.p_name << "\t\t";
		cout << process.b_time << "\t\t";
		cout << process.arr_time << "\t\t";
		cout << process.wait_time << "\t\t";
		cout << process.ta_time << "\t\t";
		cout << process.priority << endl;
	}
}

void displayResults(deque <Process> &P){
	float avg_ta_time = 0.0f, avg_wait_time = 0.0f;
	for (int i = 0; i < P.size(); i++){
		Process process = P.at(i);
		avg_wait_time += process.wait_time;
		avg_ta_time += process.ta_time;
	}
	avg_ta_time /= P.size();
	avg_wait_time /= P.size();
	cout << "Average turn around time: " << avg_ta_time << endl;
	cout << "Average waiting time: " << avg_wait_time << endl;
}

class Scheduler{
public:

	void FCFS(deque <Process> &P){
		sortJobsArrivalAscending(P);
		int time_spent = 0;
		for (int i=0; i<P.size(); i++){
			if (time_spent < P.at(i).arr_time)
				 time_spent = P.at(i).arr_time;
			calculateProcessExecution(P.at(i), time_spent, P.at(i).b_time);
		}
		displayProcesses(P);
		displayResults(P);
	}

	void SJF(deque <Process> &P){
		sortJobsArrivalAscending(P);
		int time_spent = 0;
		for (int i=0; i < P.size();i++){
			if (time_spent < P.at(i).arr_time)
				 time_spent = P.at(i).arr_time;
			int active_processes = 0;
			for (int j = i; (j < P.size()) && (P.at(j).arr_time <= time_spent); j++){
				active_processes++;
			}
			sortJobsRemainingBurstAscending(P, i, active_processes + i);
			calculateProcessExecution(P.at(i), time_spent, P.at(i).b_time);
		}
		displayProcesses(P);
		displayResults(P);
	}

	void SRJF(deque <Process> &P){
		sortJobsArrivalAscending(P);
		int time_spent = 0;
		for (int i=0; i < P.size();i++){
			if (time_spent < P.at(i).arr_time)
				time_spent = P.at(i).arr_time;
			int active_processes = 0, j;
			for (j = i; j < P.size() && P.at(j).arr_time <= time_spent; j++)
				active_processes++;
			sortJobsRemainingBurstAscending(P, i, active_processes + i);

			int burst_time = P.at(i).b_time;
			// Find pre-emptive burst time
			if (j < P.size()){
				int active_processes2 = 0, time_spent_temp = P.at(j).arr_time;
				for (int k = j; k < P.size() && P.at(k).arr_time <= time_spent_temp; k++)
					active_processes2++;
				sortJobsRemainingBurstAscending(P, j, active_processes2 + j);
				burst_time = P.at(j).arr_time - time_spent;
			}
			if ( !calculateProcessExecution(P.at(i), time_spent, burst_time) )
				i--; // Re process the process if not complete
		}
		displayProcesses(P);
		displayResults(P);
	}

	void roundRobin(deque <Process> &P, int quantum){
		sortJobsArrivalAscending(P);
		int processes_complete = 0;
		int time_spent = P.at(0).arr_time;
		for (int i = 0; i < P.size(); i++){
			if (time_spent < P.at(i).arr_time) {
				 i = 0;
			}
			if (P.at(i).progress != P.at(i).b_time){
				if ( calculateProcessExecution(P.at(i), time_spent, quantum) )
					processes_complete++;
			}
			if ( i == P.size() - 1 && processes_complete < P.size() )
				i = 0;
		}
		displayProcesses(P);
		displayResults(P);
	}

	void priorityScheduling(deque <Process> &P){
		sortPriority(P);
		int time_spent = 0;
		for (int i=0; i<P.size(); i++){
			if (time_spent < P.at(i).arr_time)
				 time_spent = P.at(i).arr_time;
			calculateProcessExecution(P.at(i), time_spent, P.at(i).b_time);
		}
		displayProcesses(P);
		displayResults(P);
	}

	void sortPriority(deque <Process> &P){
		Process temp;
		for(int i=0; i < P.size(); i++) {
			for(int j=0; j < P.size() - 1; j++) {
				if( P.at(j+1).priority < P.at(j).priority ){
					temp = P.at(j+1);
					P.at(j+1) = P.at(j);
					P.at(j) = temp;
				}
			}
		}
	}
	
	void sortJobsRemainingBurstAscending(deque <Process> &P, int start, int end){
		Process temp;
		for(int i = start; i < end ; i++) {
			for(int j = start; j < end - 1; j++) {
				if( P.at(j+1).b_time - P.at(j+1).progress < P.at(j).b_time - P.at(j).progress){
					temp = P.at(j+1);
					P.at(j+1) = P.at(j);
					P.at(j) = temp;
				}
			}
		}
	}

	void sortJobsArrivalAscending(deque <Process> &P){
		Process temp;
		for(int i=0; i < P.size(); i++) {
			for(int j=0; j < P.size() - 1; j++) {
				if( P.at(j+1).arr_time < P.at(j).arr_time ){
					temp = P.at(j+1);
					P.at(j+1) = P.at(j);
					P.at(j) = temp;
				}
			}
		}
	}
	
	bool calculateProcessExecution(Process &P, int &time_spent, int burst_cycle){
		if ( P.progress + burst_cycle > P.b_time)
			burst_cycle = P.b_time - P.progress;
		time_spent += burst_cycle;

		P.wait_time = time_spent - P.b_time - P.arr_time;
		P.ta_time = time_spent - P.arr_time;

		P.progress += burst_cycle;
		// Return if process execution is complete
		return (P.progress == P.b_time);
	}
	
};

deque <Process> input(){
	cout << "Enter number of processes to enter: ";
	int size;
	cin >> size;
	deque <Process> processes;
	for(int i=0;i<size;i++){
		Process process;
		process.p_name = i;
		cout << "Enter Process " << i << " details" << endl;
		cout << "Arrival time: ";
		cin >> process.arr_time;
		cout << "Burst time: ";
		cin >> process.b_time;
		process.priority = 0;
		process.progress = 0;
		processes.push_back(process);
	}
	return processes;
}

int main(){
	deque <Process> processes = input();
	
	Scheduler S;
	char choice;
	cout << "Choose Scheduling Method: \n1. FCFS\n2. SJF\n3. SRJF\n";
	cout << "4. Round Robin\n5. Priority\n";
	cin >> choice;
	if (choice == '1')
		S.FCFS(processes);
	else if (choice == '2')
		S.SJF(processes);
	else if (choice == '3')
		S.SRJF(processes);
	else if (choice == '4'){
		cout << "Enter quantum size: ";
		int q; cin >> q;
		S.roundRobin(processes, q);
	} else if (choice == '5'){
		cout << "Enter priorities of processes\n";
		cout << "Lower values corresponding to higher priority\n";
		for(int i = 0; i < processes.size(); i++){
			cout << "Enter Process " << i << " priority" << endl;
			cin >> processes.at(i).priority;
		}
		S.priorityScheduling(processes);
	} else {
		cout << "Invalid Option, running SRJF scheduling\n";
		S.SRJF(processes);
	}

	return 0;
}
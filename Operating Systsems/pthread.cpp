#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;

int sum;
void *runner(void *parm);

int main(int argc, char *argv[]){
	pthread_t tid;
	pthread_attr_t attr;

	if (argc != 2){
		cout << "Invalid number of arguments\n";
		exit(0);
	}
	if (atoi(argv[1]) < 0){
		cout << "number should be greater than equal to zero\n";
		exit(0);
	}

	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, runner, argv[1]);
	pthread_join(tid, NULL);

	cout << "Sum is: " << sum << endl;
}

void *runner(void *parm){
	int i = 1, j = atoi((char*)parm);
	sum = 0;
	for (; i <= j; i++)
		sum += i;
	pthread_exit(0);
}
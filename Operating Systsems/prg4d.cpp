#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
using namespace std;

int main(){
		pid_t a = fork();
		cout << a << "\n";
		
		if (a < 0)
			cout << "New process not created" << endl;
		else if (a==0){
			cout << "New Process: " << getpid() << endl;
			execlp("/bin/pwd","pwd", NULL);
			cout << endl;
		}
		else{
			wait(NULL);
			cout << "Old Process: " << getpid() << endl;	
		}
			
		return 0;
}

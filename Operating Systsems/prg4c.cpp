#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main(){
		pid_t a = fork();
		cout << a << "\n";
		
		if (a < 0)
			cout << "New process not crated" << endl;
		else if (a==0){
			cout << "New Process: " << getpid() << endl;
			execlp("/bin/pwd","pwd", NULL);
			cout << endl;
		}
		else 
			cout << "Old Process: " << getpid() << endl;
			
		return 0;
}

#include <iostream>
#include <sys/types.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
using namespace std;

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(){
	char write_msg[BUFFER_SIZE] = "Hello";
	char read_msg[BUFFER_SIZE];

	int fd[2];
	pid_t pid;
	if (pipe(fd) == -1){
		cout << "Pipe Failed";
		exit(0);
	}

	pid = fork();

	if (pid < 0){
		cout << "Fork Failed";
		exit(0);
	}
	if (pid > 0){ // Parent Process
		close(fd[READ_END]);
		write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
		close(fd[WRITE_END]);
	}
	else { // Child Process
		close(fd[WRITE_END]);
		read(fd[READ_END], read_msg, BUFFER_SIZE);
		cout << "Message Received: " << read_msg << endl;
		close(fd[READ_END]);
	}

	return 0;
}	
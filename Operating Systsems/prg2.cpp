#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h> // For sysytem types
#include <sys/stat.h> // For getting file informatio
#include <unistd.h> // For close method
#include <fcntl.h> // For File handling
using namespace std;

int main(int argc, char **argv){
	struct stat s;
	int fd;
	if(argc != 2){
		cout << "Wrong number of argumnets";
		exit(0);
	}

	fd = open(argv[1], O_RDONLY);
	
	fstat(fd, &s);

	close(fd);

	cout << "\nUser ID of owner: " << s.st_uid;
	cout << "\nGroup ID of owner: " << s.st_gid;
	cout << "\nDevice ID: " << s.st_rdev;
	cout << "\nNumber of hard links: " << s.st_nlink;
	cout << "\nSize: " << s.st_size;
	cout << "\nAcces Permission: " << s.st_mode;
	cout << "\nLast Access: " << s.st_atime;
}
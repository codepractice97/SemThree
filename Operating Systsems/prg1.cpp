#include <iostream>
#include <sys/sysinfo.h>
#include <sys/vfs.h>
#include <sys/utsname.h>
#include <cstring>
using namespace std;

int main(){
	int r1, r2, r3;
	struct sysinfo a;
	struct statfs b;
	struct utsname c;
	r1 = sysinfo(&a);
	r2 = statfs("/", &b);
	r3 = uname(&c);
	if(r1 == 0 && r3 == 0){
		int mb = 1024*1024;
		int gb = mb*1024;
		cout << "Information\tDetails\n";
		cout << "OS:\t\t" << c.sysname << " " << c.release;
		cout << "\nMachine:\t" << c.machine;
		cout << "\nTotal Ram:\t" << a.totalram/mb << "MB";
		cout << "\nDisk Size:\t" << b.f_bsize*b.f_blocks/gb << "GB\n";
	} else
		cout << "Something went wrong!\n";
}

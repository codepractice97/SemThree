#include <iostream>
using namespace std;

float pow(float b, int p){
	if (p < 0)
		return pow(1/b, (-1)*p);
	else if (p==0)
		return 1;
	return b*pow(b, p-1);
}

int main(){
	cout << "Enter base: ";
	float b;int p;
	cin >> b;
	cout << "Enter power: ";
	cin >> p;
	cout << "Result is: " << pow(b, p) << endl;
}

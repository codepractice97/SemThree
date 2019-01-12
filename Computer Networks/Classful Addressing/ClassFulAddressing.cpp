#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

bool checkSectionInRange(int s, int start, int end){
	return ( s <= end && s >= start);
}

int convertToInteger(char *token){
	int pos = 0, num = 0;
	while (token[pos] != NULL){
		int digit = token[pos] - 48;
		if (digit < 0 || digit > 9)
			throw "Invalid IP Address";
		num = (pow(10,pos) * num) + digit;
		pos++;
	}

	if (num != 0 && token[0] == 48)
		throw "Invalid IP Address";
	return num;
}

int * input(){
	char s[30];
	cout << "Enter the IP address\n";
	cin >> s;

	int *IP = new int[4];
	char *token = strtok(s, ".");
	for (int i=0; i<4; i++){
		if (token == NULL)
			throw "Invalid IP Address";
		IP[i] = convertToInteger(token);
		if (!checkSectionInRange(IP[i], 0, 255))
			throw "Invalid IP Address";
		token = strtok(NULL, ".");
	}

	return IP;
}

char calculateClass(int a){
	if (checkSectionInRange(a, 0, 127))
		return 'A';
	else if (checkSectionInRange(a, 128, 191))
		return 'B';
	else if (checkSectionInRange(a, 192, 223))
		return 'C';
	else if (checkSectionInRange(a, 224, 239))
		return 'D';
	else if (checkSectionInRange(a, 240, 255))
		return 'E';
	else return '\0';
}

int main(){
	int *IP;
	try {
		IP = input();
		cout << "Class of IP: " << calculateClass(IP[0]) << endl;
	} catch (const char *str){
		cout << str << endl;
	}
	return 0;
}
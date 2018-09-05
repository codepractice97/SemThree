#include <iostream>
#include <cstring>
#include "StackByLL.cpp"

using namespace std;

void input(Stack<int> &s1, Stack<int> &s2){
	cout << "Enter first number\n";
	char num1[50];
	cin >> num1;
	int size1= strlen(num1);
	for (int i=0; i<size1; i++){
		int n = num1[i] - 48;
		if (n >= 0 && n <= 9 )
			s1.push(n);
		else
			throw "Invalid Input";
	}
	cout << "Enter second number\n";
	char num2[50];
	cin >> num2;
	int size2= strlen(num2);
	for (int i=0; i<size2; i++){
		int n = num2[i] - 48;
		if (n >= 0 && n <= 9 )
			s2.push(n);
		else
			throw "Invalid Input";
	}
}

Stack<int> add(Stack<int> &s1, Stack<int> &s2){
	Stack<int> s;
	
	int carry = 0;
	
	while (!s1.isEmpty() && !s2.isEmpty()){
		int num1, num2;
		if (!s1.isEmpty())
			num1 = s1.pop();
		else 
			num1 = 0;
		if (!s2.isEmpty())
			num2 = s2.pop();
		else 
			num2 = 0;
		int sum = carry + num1 + num2;
		carry = sum / 10;
		s.push(sum%10 + 48);
	}
	
	if (carry != 0){
		s.push(carry + 48)
	}
	
	return s;
}

int main(){
	Stack<int> s1, s2;
	
	try{
		input(s1, s2);
	} catch(const char c){
		cout << c;
	}
	
}

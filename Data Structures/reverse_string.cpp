#include <iostream>
using namespace std;

string reverse(string str, int lastIndex){
	if (lastIndex < 0)
		return "";
	return ( str.at(lastIndex) +  reverse(str, lastIndex - 1));
}

string reverse(string str){
	return reverse(str, str.length()-1);
}

int main(){
	cout << "Enter string to reverse: ";
	string s;
	cin >> s;
	cout << "Reverse is:\n" << reverse(s) << endl;
}

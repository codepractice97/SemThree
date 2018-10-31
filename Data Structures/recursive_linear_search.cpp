#include <iostream>
using namespace std;

int linear(int a[], int key, int index){
	if (index == -1)
		return -1;
	else if (a[index] == key)
		return index;
	return linear(a, key, index -1);
}

int main(){
	cout << "Enter size of array: ";
	int s, key;
	cin >> s;
	int a[s];
	cout << "Enter elements\n";
	for (int i = 0;i<s;i++)
		cin >> a[i];
	cout << "Enter element to search: ";
	cin >> key;
	int pos = linear(a, key, s-1);
	if (pos == -1)
		cout << key << " not found\n";
	else
		cout << key << " found at posiiton " << pos << endl;
}

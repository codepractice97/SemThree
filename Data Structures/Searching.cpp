#include<iostream>
using namespace std;
class Searching{
	
public:
	
	int *A, size;
	
	void input(){
		cout << "Enter size of array";
		cin >> size;
		A = new int[size];
		for(int i=0;i<size;i++)
			cin >> A[i];
		cout << "Inputted array:\n";
		display();		
	}
	
	int linearSearch(int data){
		for (int i=0;i<size; i++){
			if (A[i] == data)
				return i;
		}
		return -1;
	}
	
	int binarySearch(int data, int l, int r){
		if (l<=r){
			int middle = l + (r-l)/2;
			if (data == A[middle])
				return middle;
			else if (data < A[middle])
				return binarySearch(data, l, middle -1);
			else
				return binarySearch(data, middle + 1, r);	
		} return -1;
	}
		
	bool checkSorted(){
		for (int i=0;i<size-1;i++){
			if (A[i] > A[i+1])
				return false;
		}
		return true;
	}
	
private:
	
	void display(){
		for(int i=0;i<size;i++)
			cout << A[i] << " ";
		cout << endl;
	}
	
};

int main(){
	Searching s;
	char choice;
	do {
		s.input();
		cout << "Enter element to search: ";
		int data;
		cin >> data;
		cout << "Choose method of Searching:\n";
		cout << "1. Linear\n2. Binary\n";
		cin >> choice;
		int pos = -1;
		
		if (choice == '1')
			pos = s.linearSearch(data);
		else if (choice == '2'){
			if (!s.checkSorted()){
				cout << "Array is not sorted, cannot search by binary method";	
			} else
				pos = s.binarySearch(data, 0, s.size-1);
		}
		else
			cout << "Invalid Option" << endl;
		
		
		if (pos == -1)
			cout << data + " not found in array\n";
		else
			cout << data + " found at position: " << pos << endl;

		cout << "Press y to continue\n";
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');

	return 0;
}

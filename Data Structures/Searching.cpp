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
		if (!checkSorted()){
			throw "Array is not sorted, cannot search";
		}
		if (l<r){
			int middle = l + (r-l)/2;
			if (data == A[middle])
				return middle;
			else if (data < A[middle])
				return binarySearch(data, l, middle -1);
			else
				return binarySearch(data, middle + 1, r);	
		} return -1;
	}
	
	
private:
	
	void display(){
		for(int i=0;i<size;i++)
			cout << A[i] << " ";
		cout << endl;
	}
	
	bool checkSorted(){
		for (int i=0;i<size-1;i++){
			if (A[i] > A[i+1])
				return false;
		}
		return true;
	}
	
};

int main(){
	Searching S;
	S.input();
	try {
		cout << "Pos: " << S.binarySearch(3, 0, S.size-1) << endl;
	} catch(const char *msg){
		cout << msg << endl;
	}
	
	return 0;
}

#include<iostream>
using namespace std;
class Sorting{
	
	int *A, size;
	
public:
	
	void input(){
		cout << "Enter size of array";
		cin >> size;
		A = new int[size];
		for(int i=0;i<size;i++)
			cin >> A[i];
		display();		
	}
	
	void bubbleSort(){
		int temp;
		for(int i=0;i<size;i++)
		{
			for(int j=0;j<size-i-1;j++)
			{
				if(A[j+1]<A[j]){				
					temp=A[j+1];
					A[j+1]=A[j];
					A[j]=temp;
				}
				
			}
		}
		display();	
	}
	
	void insertionSort(){
		for(int i=1;i<size;i++){
			int key = A[i], j = i-1;
			while(j>=0 && key<A[j]){
				A[j+1]=A[j];
				j--;
			}
			A[j+1]=key;
		}
		display();
	}
	
	void selectionSort(){
		for(int i=0;i<size;i++){
			int min = i;
			for(int j=i+1;j<size;j++){
				if(A[j]<A[min])
					min = j;
			}
			int temp = A[i];
			A[i] = A[min];
			A[min] = temp;
		}
		display();
	}
	
	
private:
	
	void display(){
		for(int i=0;i<size;i++)
			cout << A[i] << " ";
		cout << endl;
	}
	
};

int main(){
	Sorting S;
	S.input();
	//S.bubbleSort();
	//S.insertionSort();
	S.selectionSort();
	
	return 0;
}

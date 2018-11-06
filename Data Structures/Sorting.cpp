#include<iostream>
using namespace std;
class Sorting{
	
	int *A, size;
	
public:
	
	void input(){
		cout << "Enter size of array: ";
		cin >> size;
		A = new int[size];
		cout << "Enter array: \n";
		for(int i=0;i<size;i++)
			cin >> A[i];
		display();
	}
	
	void bubbleSort(){
		int temp;
		for(int i=0;i<size;i++) {
			for(int j=0;j<size-i-1;j++) {
				if(A[j+1]<A[j]){				
					temp=A[j+1];
					A[j+1]=A[j];
					A[j]=temp;
				}
			}
		}
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
	}

	void quickSort(){
		quickSort(0, size-1);
	}

	void quickSort(int left, int right){
		if (left < right){
			int p = parititon(left, right);
			quickSort(left, p-1);
			quickSort(p+1, right);
		}
	}

	int parititon(int left, int right){
		int key = A[right];

		int j = right;
		for (int i = left; i < j; ){
			if (A[i] > key){
				j--;
				swap(i, j);
			} else i++;
		}
		swap(j, right);
		return j;
	}

	void swap(int i, int j){
		int temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}

	void mergeSort(){
		A = mergeSort(A, 0, size - 1);
	}

	int* mergeSort(int *arr,int l, int r){
		if (l < r){
			int m = l + (r-l)/2;
			int *left = mergeSort(arr, l, m);
			int *right = mergeSort(arr, m+1, r);
			return merge(left, right, l, m, r);
		} else {
			return new int[1]{arr[l]};
		}
	}

	int* merge(int *left, int *right, int l, int m, int r){
		int *arr = new int[r-l+1];
		int i = 0, j = 0, k = 0;
		while (i <= m - l && j <= r - m - 1){
			if (left[i] <= right[j]){
				arr[k] = left[i];
				i++; k++;
			} else {
				arr[k] = right[j];
				j++; k++;
			}
		}
		while (i <= m - l){
			arr[k] = left[i];
			i++; k++;
		}
		while (j <= r - m - 1){
			arr[k] = right[j];
			j++; k++;
		}
		return arr;
	}

	void display(){
		for(int i=0;i<size;i++)
			cout << A[i] << " ";
		cout << endl;
	}
		
};

int main(){
	Sorting s;
	char choice;
	do {
		s.input();
		cout << "Choose method of sorting:\n1. Bubble\n";
		cout << "2. Insertion\n3. Selection\n4. Merge\n5. Quick\n";
		cin >> choice;
		if (choice == '1')
			s.bubbleSort();
		else if (choice == '2')
			s.insertionSort();
		else if (choice == '3')
			s.selectionSort();
		else if (choice == '4')
			s.mergeSort();
		else if (choice == '5')
			s.quickSort();
		else
			cout << "Invalid Option" << endl;

		s.display();

		cout << "Press y to continue\n";
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');

	return 0;
}

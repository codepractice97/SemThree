#include <iostream>
using namespace std;

template <class Type>
class DiagonalMatrix{

	int size;
	Type *A;
public:
	DiagonalMatrix(int m, int n){
		if (m != n || m < 0 || n < 0)
			throw "Invalid Matrix size.";
		size = m;
		A = new Type[size];
	}
	~DiagonalMatrix() { delete A; }

	void set(int i, int j, Type value){
		if (i < 0 || j < 0 || i > size - 1 || j > size - 1)
			throw "Matrix Index Out Of Bounds.";

		if (i == j)
			A[i] = value;
		else if (value != 0)
			throw "Non Diagonal Values must be zero";
	}

	Type get(int i, int j){
		if (i < 0 || j < 0 || i > size - 1 || j > size - 1)
			throw "Matrix Index Out Of Bounds.";

		if (i == j)
			return A[i];
		else return 0;
	}
};

// Row Major data arrangement
template <class Type>
class LowerTriangularMatrix{
	int size;
	Type *A;
public:
	LowerTriangularMatrix(int m, int n){
		if (m != n || m < 0 || n < 0)
			throw "Invalid Matrix size.";
		size = m*(m+1)/2;
		A = new Type[size];
	}
	~LowerTriangularMatrix() { delete A; }

	void set(int i, int j, Type value){
		if (i < 0 || j < 0 || i > size - 1 || j > size - 1)
			throw "Matrix Index Out Of Bounds.";

		if (i >= j)
			A[i * (i+1) / 2 + j] = value;
		else if (value != 0)
			throw "Elements not in lower triangle must be zero";
	}

	Type get(int i, int j){
		if (i < 0 || j < 0 || i > size - 1 || j > size - 1)
			throw "Matrix Index Out Of Bounds.";

		if (i >= j)
			return A[i * (i+1) / 2 + j];
		else return 0;
	}
};

// Column Major Data Arrangement
template <class Type>
class UpperTriangularMatrix{
	int size;
	Type *A;
public:
	UpperTriangularMatrix(int m, int n){
		if (m != n || m < 0 || n < 0)
			throw "Invalid Matrix size.";
		size = m*(m+1)/2;
		A = new Type[size];
	}
	~UpperTriangularMatrix() { delete A; }

	void set(int i, int j, Type value){
		if (i < 0 || j < 0 || i > size - 1 || j > size - 1)
			throw "Matrix Index Out Of Bounds.";

		if (i <= j)
			A[j * (j+1) / 2 + i] = value;
		else if (value != 0)
			throw "Elements not in upper triangle must be zero";
	}

	Type get(int i, int j){
		if (i < 0 || j < 0 || i > size - 1 || j > size - 1)
			throw "Matrix Index Out Of Bounds.";

		if (i >= j)
			return A[j * (j+1) / 2 + i];
		else return 0;
	}
};

// Using lower traingle and row major data representation
template <class Type>
class SymmetricMatrix{
	int size;
	Type *A;
public:
	SymmetricMatrix(int m, int n){
		if (m != n || m < 0 || n < 0)
			throw "Invalid Matrix size.";
		size = m*(m+1)/2;
		A = new Type[size];
	}
	~SymmetricMatrix() { delete A; }

	void set(int i, int j, Type value){
		if (i < 0 || j < 0 || i > size - 1 || j > size - 1)
			throw "Matrix Index Out Of Bounds.";

		if (i <= j)
			A[i * (i+1) / 2 + j] = value;
		else
			A[j * (j+1) / 2 + i] = value;
	}

	Type get(int i, int j){
		if (i < 0 || j < 0 || i > size - 1 || j > size - 1)
			throw "Matrix Index Out Of Bounds.";

		if (i >= j)
			return A[i * (i+1) / 2 + j];
		else return A[j * (j+1) / 2 + i];
	}
};

void input(){

}

int manin(){
	char choice;
	do {
		cout << "Enter choice: \n1. Diagonal Matrix\n";
		cout << "2. Lower Triangular Matrix\n3. Upper Triangular Matrix\n"
		cout << "4. Symmetric Matrix\n";
		cin >> choice;
		cout << "Enter row count of the matrix: ";
		int i, j, temp;
		cin >> i;
		cout << "Enter Column count of the matrix: "
		cin >> j;
		cout << "Enter the matrix in row major form:\n";
		if (choice == '1'){
			DiagonalMatrix diagonalMatrix(i, j);
			for (int k = 0;k < i; k++){
				for (int l = 0;l < j;l++){
					cin >> temp;
					diagonalMatrix.set(k, l, temp);
				}
			}
			cout << "Stored matrix: \n";
			for (int k = 0;k < i; k++){
				for (int l = 0;l < j;l++){
					cin >> temp;
					diagonalMatrix.set(k, l, temp);
				}
			}
		}
	} while (chocie == 'Y' || chocie == 'y');
	return 0;
}
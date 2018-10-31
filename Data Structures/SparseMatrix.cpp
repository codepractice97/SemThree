#include <iostream>
using namespace std;

template <class Type>
class SparseMatrix{
public:
	int size;
	Type *A;
	SparseMatrix(int m, int n, int s){
		if (m != n || m < 0 || n < 0)
			throw "Invalid Matrix size.";
		size = s;
		A = new Type[size];
	}
	~SparseMatrix() { delete A; }
	virtual void set(int i, int j, Type value);
	virtual Type get(int i, int j);
};

template <class Type>
class DiagonalMatrix: public SparseMatrix<Type>{

public:
	DiagonalMatrix(int m, int n): SparseMatrix<Type>(m, n, m){}

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
class LowerTriangularMatrix: public SparseMatrix<Type> {
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
class UpperTriangularMatrix: public SparseMatrix<Type> {
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
class SymmetricMatrix: public SparseMatrix<Type> {
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

int manin(){
	char choice;
	do {
		try {
			cout << "Enter choice: \n1. Diagonal Matrix\n";
			cout << "2. Lower Triangular Matrix\n3. Upper Triangular Matrix\n";
			cout << "4. Symmetric Matrix\n";
			cin >> choice;
			cout << "Enter row count of the matrix: ";
			int i, j, temp;
			cin >> i;
			cout << "Enter Column count of the matrix: ";
			cin >> j;
			cout << "Enter the matrix:\n";
			SparseMatrix<int> *matrix;
			DiagonalMatrix<int> diagonalMatrix(i,j);
			if (choice == '1'){
				matrix = &diagonalMatrix;
			}
			for (int k = 0;k < i; k++){
				for (int l = 0;l < j;l++){
					cin >> temp;
					matrix->set(k, l, temp);
				}
			}
			cout << "Stored matrix: \n";
			for (int k = 0;k < i; k++){
				for (int l = 0;l < j;l++){
					cin >> temp;
					matrix->get(k, l);
				}
			}
		} catch (const char m[]){
			cout << m << endl;
		}
		
		cout << "Enter 'Y' to continue" << endl;
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
	return 0;
}

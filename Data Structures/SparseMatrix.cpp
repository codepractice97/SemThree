#include <iostream>
using namespace std;

template <class Type>
class SparseMatrix{
public:
	virtual void set(int i, int j, Type value) = 0;
	virtual Type get(int i, int j) = 0;
};

template <class Type>
class DiagonalMatrix: public SparseMatrix<Type>{
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
class LowerTriangularMatrix: public SparseMatrix<Type> {
	int size;
	Type *A;
public:
	LowerTriangularMatrix(int m, int n){
		if (m != n || m < 0 || n < 0)
			throw "Invalid Matrix size.";
		size = m;
		A = new Type[m*(m+1)/2];
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
		size = m;
		A = new Type[m*(m+1)/2];
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
		size = m;
		A = new Type[m*(m+1)/2];
	}
	~SymmetricMatrix() { delete A; }

	void set(int i, int j, Type value){
		if (i < 0 || j < 0 || i > size - 1 || j > size - 1)
			throw "Matrix Index Out Of Bounds.";

		if (i >= j)
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

// Stored in order: center diagonal, lower diagonal, upper diagonal
template <class Type>
class TridiagonalMatrix: public SparseMatrix<Type> {
	int size;
	Type *A;
public:
	TridiagonalMatrix(int m, int n){
		if (m != n || m < 0 || n < 0)
			throw "Invalid Matrix size.";
		size = m;
		A = new Type[3 * m - 2];
	}
	~TridiagonalMatrix(){ delete A; }

	void set(int i, int j, Type value){
		if (i < 0 || j < 0 || i > size - 1 || j > size - 1)
			throw "Matrix Index Out Of Bounds.";

		if (i - j == -1) {
			A[2 * size - 1 + i] = value;
		} else if (i - j == 0) {
			A[i] = value;
		} else if (i - j == 1) {
			A[size + j] = value;
		} else if (value != 0)
			throw "Elements not in tridiagonal must be zero";
	}

	Type get(int i, int j){
		if (i < 0 || j < 0 || i > size - 1 || j > size - 1)
			throw "Matrix Index Out Of Bounds.";

		if (i - j == -1) {
			return A[2 * size - 1 + i];
		} else if (i - j == 0) {
			return A[i];
		} else if (i - j == 1) {
			return A[size + j];
		} else
			return 0;
	}
};


int main(){
	char choice;
	do {
		try {
			cout << "Enter choice: \n1. Diagonal Matrix\n";
			cout << "2. Lower Triangular Matrix\n3. Upper Triangular Matrix\n";
			cout << "4. Symmetric Matrix\n5. Tridiagonal Matrix\n";
			cin >> choice;
			if (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5') {
				cout << "Invalid Option" << endl;
				cout << "Enter 'Y' to continue" << endl;
				cin >> choice;
				break;
			}
			cout << "Enter row count of the matrix: ";
			int i, j, temp;
			cin >> i;
			cout << "Enter Column count of the matrix: ";
			cin >> j;
			cout << "Enter the matrix:\n";
			SparseMatrix<int> *matrix;
			if (choice == '1')
				matrix = new DiagonalMatrix<int>(i, j);
			else if (choice == '2')
				matrix = new LowerTriangularMatrix<int>(i, j);
			else if (choice == '3')
				matrix = new UpperTriangularMatrix<int>(i, j);
			else if (choice == '4')
				matrix = new SymmetricMatrix<int>(i, j);
			else if (choice == '5')
				matrix = new TridiagonalMatrix<int>(i, j);
			for (int k = 0;k < i; k++){
				for (int l = 0;l < j;l++){
					cin >> temp;
					matrix->set(k, l, temp);
				}
			}
			cout << "Stored matrix: \n";
			for (int k = 0;k < i; k++){
				for (int l = 0;l < j;l++)
					cout << matrix->get(k, l) << " ";
				cout << endl;
			}
		} catch (const char m[]){
			cout << m << endl;
		}
		
		cout << "Enter 'Y' to continue" << endl;
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');

	return 0;
}

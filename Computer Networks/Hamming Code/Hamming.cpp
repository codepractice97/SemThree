#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

struct DataBundle{ 
	int *data, size;
	DataBundle(int s){
		size = s;
		data = new int[size];
	}
	~DataBundle() { delete data; }
};

class HammingCode{

	bool valueIsPowerOf2(int i){
		for (int j=0;j<i;j++){
			if (i == pow(2,j))
				return true;
		}
		return false;
	}

	int **binaryMatrix;

	void createBinarymatrix(int r){
		int size = pow(2,r);
		binaryMatrix = new int*[size];
		for (int i = 0;i< size;i++)
			binaryMatrix[i] = new int[r];

		for (int i=1;i<=size;i++){
			for (int j=0;j<r;j++){
				if (( 1 << j) & i )
					binaryMatrix[i-1][r-j-1] = 1;
			}
		}
	}

	int findParityBit(DataBundle &dB, int bit_pos){
		int parity_value = 0;
		for (int i = 0; i < dB.size; i++){
			if (binaryMatrix[i][bit_pos] == 1)
				parity_value = parity_value ^ dB.data[i];
		}
		cout << "Parity Value: " << parity_value << endl;
		return parity_value;
	}
	
public:
	DataBundle encode(DataBundle dB){
		// Calculate the number of parity bits
		int r = 0;
		while (pow(2,r) <= r + dB.size + 1)
			r++;
		cout << "R: " << r << endl;
		
		// Store data bits at appropriate positions
		int new_size = r + dB.size;
		DataBundle new_dB(new_size);
		int p_count = 0;
		for (int i = 0; i < new_size; i++){
			if (valueIsPowerOf2(i+1)){
				
				p_count++;
			} else
				new_dB.data[i] = dB.data[i - p_count];
		}

		createBinarymatrix(r);

		// Store parity bits at appropriate positions
		p_count = 0;
		for (int i = 0; i < new_size; i++){
			if (valueIsPowerOf2(i+1)){
				new_dB.data[i] = findParityBit(dB, r-p_count-1);
				p_count++;
			}
		}
		return new_dB;
	}

	DataBundle decode(DataBundle dB){

	}
	
	void display(DataBundle *dB){
		for(int i=0;i<dB->size;i++)
			cout << dB->data[i] << " ";
		cout << endl;
	}
	
};

DataBundle input(){
	char data_temp[64];
	printf("%s\n", "Enter data");
	scanf("%s", data_temp);

	int size = strlen(data_temp);
	DataBundle dB(size);
	for (int i = 0; i < size; ++i){
		dB.data[i] = data_temp[i] - 48;
		if (dB.data[i] != 0)
			dB.data[i] = 1;
	}
	return dB;
}

int main(){
	HammingCode H;
	DataBundle dB = input();
	H.display(&dB);
	DataBundle encodedData = H.encode(dB);
	H.display(&encodedData);
	
	return 0;
}

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

	int findParityBit(DataBundle &dB, int skip){
		int parity_value = 0;
		for (int i = -1; i < dB.size;){
			i+= skip;
			for(int j = i+skip; i< j,i<dB.size;i++){
				parity_value = parity_value ^ dB.data[i];
				cout << dB.data[i] << " ";
			}
				
		}
		cout << "Parity Value: " << parity_value << endl;
		return parity_value;
	}
	
public:

	DataBundle encode(DataBundle &dB){
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
			if (valueIsPowerOf2(i+1))	
				p_count++;
			else
				new_dB.data[i] = dB.data[i - p_count];
		}

		// Store parity bits at appropriate positions
		p_count = 0;
		for (int i = 0; i < new_size; i++){
			if (valueIsPowerOf2(i+1)){
				new_dB.data[i] = findParityBit(new_dB, pow(2,p_count));
				p_count++;
			}
		}
		return new_dB;
	}

	DataBundle decode(DataBundle &dB){

	}
	
};

void display(DataBundle *dB){
	for(int i=0;i<dB->size;i++)
		cout << dB->data[i] << " ";
	cout << endl;
}

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
	display(&dB);
	DataBundle encodedData = H.encode(dB);
	display(&encodedData);
	
	return 0;
}

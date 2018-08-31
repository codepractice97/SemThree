#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace std;

struct DataBundle{ 
	int *data, size;
	DataBundle(int s){
		size = s;
		data = new int[size];
	}
	~DataBundle() { delete data; }
};

void display(DataBundle *dB){
	for(int i=0;i<dB->size;i++)
		cout << dB->data[i] << " ";
	cout << endl;
}

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
			i = i + skip;
			for(int j = i+skip; i < j && i < dB.size;i++){
				parity_value = parity_value ^ dB.data[i];
			}
		}
		return parity_value;
	}

	int checkParity(DataBundle &dB, int skip){
		int parity_value = 0;
		for (int i = -1; i < dB.size;){
			i = i + skip;
			for(int j = i+skip; i < j && i < dB.size;i++){
				parity_value = parity_value ^ dB.data[i];
			}
		}
		return parity_value;
	}
	
public:

	DataBundle computeHammingCode(DataBundle &dB){
		// Calculate the number of parity bits
		int r = 0;
		while (pow(2,r) < r + dB.size + 1)
			r++;
		
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
				int parity_value = findParityBit(new_dB, pow(2,p_count));
				cout << "Parity Value(" << (p_count+1) << "): " 
					<< parity_value << endl;
				new_dB.data[i] = parity_value;
				p_count++;
			}
		}

		return new_dB;
	}

	bool checkDataIntegrity(DataBundle &dB){
		// Check if XOR of particular bits is 0 or not
		// and store the XOR'd values
		int pos[10];
		int p_count = 0;
		for(int i=0; i<dB.size; i++){
			if (valueIsPowerOf2(i+1)){
				pos[p_count] = checkParity(dB, pow(2,p_count));
				p_count++;
			}
		}

		// Convert XOR'd binary into decimal
		int position = 0;
		for (int i = 1; i <= dB.size; i++){
			bool decimalMatches = true;
			for (int j = 0; j < p_count; j++){
				if (pos[j] == 1){
					if (!((1 << j) & i))
						decimalMatches = false;
				} else {
					if ((1 << j) & i)
						decimalMatches = false;
				}
			}
			if (decimalMatches){
				position = i;
				break;
			}
		}

		if (position == 0){
			cout << "No Error\n";
			return true;
		}
		else {
			cout << "Error found at: " << position << endl;
			if (dB.data[position-1] == 0)
				dB.data[position-1] = 1;
			else
				dB.data[position-1] = 0;
			return false;
		}

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
	cout << "Entered data:\n";
	display(&dB);
	DataBundle encodedData = H.computeHammingCode(dB);
	cout << "Hamming Code:\n";
	display(&encodedData);

	// Induce Error
	srand(time(0));
	int pos = rand() % encodedData.size;
	encodedData.data[pos] = 0;
	cout << "Transmitted Data:\n";
	display(&encodedData);

	H.checkDataIntegrity(encodedData);
	cout << "Error Corrected Data:\n";
	display(&encodedData);

	
	return 0;
}
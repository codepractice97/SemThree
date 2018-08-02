#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
//#include <conio.h>
using namespace std;

struct DataBundle {

	int *data, *key;
	int data_size, key_size;

};

class CRC {	

public:

	DataBundle* encodeData(DataBundle *dB){
		DataBundle *new_dB = new DataBundle();
		new_dB->key = dB->key;
		new_dB->key_size = dB->key_size;
		new_dB->data_size = dB->data_size + dB->key_size - 1;
		int *new_data = new int[new_dB->data_size];

		// Add dB->key_size - 1 0's at end of data
		for(int i = 0;i<new_dB->data_size; i++){
			if (i < dB->data_size)
				new_data[i] = dB->data[i];
			else
				new_data[i] = 0;
		}

		new_dB->data = new_data;

		int *remainder = mod2Division(new_dB);
		
		delete new_data;
		new_data = new int[new_dB->data_size];

		for (int i = 0; i < new_dB->data_size; ++i) {
			if (i < dB->data_size)
				new_data[i] = dB->data[i];
			else
				new_data[i] = remainder[i - dB->data_size];
		}

		new_dB->data = new_data;

		return new_dB;
	}

	bool checkIntegrity(DataBundle *dB){
		DataBundle *new_dB = new DataBundle();
		new_dB->key = dB->key;
		new_dB->key_size = dB->key_size;
		new_dB->data_size = dB->data_size;

		int *data = new int[dB->data_size];
		for (int i = 0; i < dB->data_size; ++i)
				data[i] = dB->data[i];
		new_dB->data = data;

		int *remainder = mod2Division(new_dB);
		for (int i = 0; i < dB->key_size-1; ++i) {
			if (remainder[i] != 0)
				return false;
		}
		return true;
	}

	int* mod2Division(DataBundle *dB){

		int divisor_size = dB->key_size;
		int dividend_size = dB->data_size;
		int *divisor = dB->key;
		int *dividend = dB->data;
		int *remainder = new int[divisor_size];

		for(int i=0; i < dividend_size - divisor_size + 1;i++){

			if (dividend[i] == 0)
				continue;

			// XOR one step and put the result in dividend
			for (int j = 0; j < divisor_size; j++){
				remainder[j] = dividend[i+j] ^ divisor[j];
				dividend[i+j] = remainder[j];
			}
		}

		int *new_rem = new int[divisor_size-1];
		for(int j=0;j<divisor_size-1;j++) // Extract the remainder excluding first bit
			new_rem[j] = remainder[j+1];

		return new_rem;
	}

};

void load(DataBundle *dataBundle){
	char data_temp[64], key_temp[64];
	printf("%s\n", "Enter data");
	scanf("%s", data_temp);
	printf("%s\n", "Enter Key");
	scanf("%s", key_temp);

	dataBundle->data_size = strlen(data_temp);
	dataBundle->key_size = strlen(key_temp);
	dataBundle->data = new int[dataBundle->data_size];
	dataBundle->key = new int[dataBundle->key_size];
	for (int i = 0; i < dataBundle->data_size; ++i){
		dataBundle->data[i] = data_temp[i] - 48;
		if (dataBundle->data[i] != 0)
			dataBundle->data[i] = 1;
	}
	for (int i = 0; i < dataBundle->key_size; ++i){
		dataBundle->key[i] = key_temp[i] - 48;
		if (dataBundle->key[i] != 0)
			dataBundle->key[i] = 1;
	}
}

void corruptData(DataBundle *dB){
	srand(time(NULL));
	int randomPos = rand() % (dB->data_size * 2);
	if (randomPos > dB->data_size) // Do not corrupt the data
		return;
	if (dB->data[randomPos] == 1)
		dB->data[randomPos] = 0;
	else
		dB->data[randomPos] = 1;
}

void display(DataBundle *dataBundle){
	cout << "Data(" << dataBundle->data_size << "): ";
	for (int i = 0; i<dataBundle->data_size; ++i)
		cout << dataBundle->data[i];
	cout << endl << "Key(" << dataBundle->key_size << "): ";
	for (int i = 0; i<dataBundle->key_size; ++i)
		cout << dataBundle->key[i];
	cout << endl;
}

int main(){
	DataBundle *dataBundle = new DataBundle();
	load(dataBundle);
	cout << "Initial Data:" << endl;
	display(dataBundle);

	CRC crc;
	DataBundle *encodedData = crc.encodeData(dataBundle);
	cout << "Encoded Data:" << endl;
	display(encodedData);

	corruptData(encodedData);
	cout << "Final Data:" << endl;
	display(encodedData);
	cout << ( crc.checkIntegrity(encodedData) ? "Data Intact" : "Data lost" ) << endl;
	
	//getch();
	return 0;
}
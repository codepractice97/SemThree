#include <iostream>
#include <stdio.h>
#include <string.h>
//#include <conio.h>
using namespace std;

struct DataBundle {

	int *data, *key;
	int data_size, key_size;

};

class CRC {

	

public:

	DataBundle* encodeData(DataBundle *dB){
		return new DataBundle();
	}

	bool checkIntegrity(DataBundle *dB){
		return true;
	}

	void mod2Division(DataBundle *dB){
		
	}

};

void load(DataBundle *dataBundle){
	char data_temp[32], key_temp[32];
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

void display(DataBundle *dataBundle){
	cout << "Data: ";
	for (int i = 0; i<dataBundle->data_size; ++i)
		cout << dataBundle->data[i];
	cout << endl << "Key: ";
	for (int i = 0; i<dataBundle->key_size; ++i)
		cout << dataBundle->key[i];
	cout << endl;
}

int main(){
	DataBundle *dataBundle;
	load(dataBundle);
	display(dataBundle);

	CRC crc;
	crc.encodeData(dataBundle);
	cout << ( crc.checkIntegrity(dataBundle) ? "Data Intact" : "Data lost" ) << endl;
	
	//getch();
	return 0;
}

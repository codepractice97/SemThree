#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <conio.h>
using namespace std;

struct DataBundle{ int *data, size; };

class HammingCode{
	
	int findParityBit(int p_index){
		return -1;
	}
	
public:
	DataBundle* encode(DataBundle *dB){
		// Calculate the number of parity bits
		int r = 0;
		while (pow(2,r) <= r + dB->size + 1)
			r++;
		cout << "R: " << r << endl;
		
		// Store bits at appropriate positions
		int new_size = r + dB->size;
		DataBundle *new_dB = new DataBundle();
		new_dB->size = new_size;
		new_dB->data = new int[new_size];
		int p_count = 0;
		for (int i=0;i<= new_size; i++){
			if (i+1 == pow(2,i)){
				new_dB->data[i] = findParityBit(i);
				p_count++;
			} else
				new_dB->data[i] = dB->data[i - p_count];
		}
		return new_dB;
	}
	
	void display(DataBundle *dB){
		for(int i=0;i<dB->size;i++)
			cout << dB->data[i] << " ";
		cout << endl;
	}
	
};

void load(DataBundle *dataBundle){
	char data_temp[64];
	printf("%s\n", "Enter data");
	scanf("%s", data_temp);

	dataBundle->size = strlen(data_temp);
	dataBundle->data = new int[dataBundle->size];
	for (int i = 0; i < dataBundle->size; ++i){
		dataBundle->data[i] = data_temp[i] - 48;
		if (dataBundle->data[i] != 0)
			dataBundle->data[i] = 1;
	}
}

int main(){
	HammingCode H;
	DataBundle *dB = new DataBundle();
	load(dB);
	H.display(dB);
	DataBundle *encodedData = H.encode(dB);
	H.display(encodedData);
	
	getch();
	return 0;
}

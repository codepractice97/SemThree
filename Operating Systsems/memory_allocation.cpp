#include<iostream>
#include<cstdlib>
using namespace std;
struct Processes{
	int PID,Memory,MID;
};
struct MemoryUnit{
	int MID,Block;
};
class MemoryFit{
	public:
	Processes* process;
	MemoryUnit* memory;
	int nProcess,nMemory;
	
	void operator=(MemoryFit ob)
	{
		nProcess=ob.nProcess;
		nMemory=ob.nMemory;
		process=new struct Processes [nProcess];
		for(int i=0;i<nProcess;i++)
			process[i]=ob.process[i];
		memory=new struct MemoryUnit [nMemory];
		for(int i=0;i<nMemory;i++)
			memory[i]=ob.memory[i];
	}
	
	void input()
	{
		cout<<"\nEnter the no. of processes\n";
		cin>>nProcess;
		process=new struct Processes[nProcess];
		for(int i=0;i<nProcess;i++)
		{
			cout<<"Process ID "<<i+1;
			process[i].PID=i+1;
			cout<<"\nEnter Memory size of Process ";
			cin>>process[i].Memory;	
			process[i].MID=-1;		
		}
		cout<<"\nEnter the no. of Memory Blocks\n";
		cin>>nMemory;
		memory=new struct MemoryUnit[nMemory];
		for(int i=0;i<nMemory;i++)
		{
			cout<<"Memory Block ID "<<i+1;
			memory[i].MID=i+1;
			cout<<"\nEnter Memory Block size ";
			cin>>memory[i].Block;			
		}
	}
	
	void display()
	{
		MemoryIDSort();
		cout<<"Process ID\tMemory Size\tMemory Block ID\n";
		for(int i=0;i<nProcess;i++)
		{
			cout<<process[i].PID<<"\t\t"<<process[i].Memory<<"\t\t";
			if(process[i].MID!=-1)
				cout<<process[i].MID<<"\n";	
			else
				cout<<"Not Allocated"<<"\n";	
		}
		cout<<"Memory Block ID\tFree Memory Block Size\n";
		for(int i=0;i<nMemory;i++)
			cout<<memory[i].MID<<"\t\t"<<memory[i].Block<<"\n";
	}
	
	void MemoryBlockSort(bool asc_desc)
	{
		MemoryUnit temp;
		for(int i=0;i<nMemory;i++)
		{
			for(int j=i;j<nMemory;j++)
			{
				if(asc_desc==0)
				{
					if(memory[i].Block>memory[j].Block)
					{
					temp=memory[i];
					memory[i]=memory[j];
					memory[j]=temp;	
					}	
				}
				else
				{
					if(memory[i].Block<memory[j].Block)
					{
					temp=memory[i];
					memory[i]=memory[j];
					memory[j]=temp;	
					}
				}
				
			}
		}
	}
	
	void MemoryIDSort()
	{
		MemoryUnit temp;
		for(int i=0;i<nMemory;i++)
		{
			for(int j=i;j<nMemory;j++)
			{
				if(memory[i].MID>memory[j].MID)
				{
					temp=memory[i];
					memory[i]=memory[j];
					memory[j]=temp;	
				}				
			}
		}
	}
	
	
	void firstFit()
	{
		for(int i=0;i<nProcess;i++)
		{
			for(int j=0;j<nMemory;j++)
			{
				if(process[i].Memory<=memory[j].Block)
				{
					memory[j].Block-=process[i].Memory;
					process[i].MID=memory[j].MID;
					break;
				}
			}
		}
	}
	
	void Best_WorstFit(bool BW)
	{	
		MemoryBlockSort(BW);
		firstFit();
	}
	
	int menu()
	{
		cout<<"\nMENU\n";
		cout<<"1. Enter/Re-Enter Process & Memory Information\n";
		cout<<"2. View Process & Memory Information\n";
		cout<<"3. First Fit\n";
		cout<<"4. Best Fit\n";
		cout<<"5. Worst Fit\n";
		cout<<"6. EXIT\n";
		cout<<"Enter Choice\n";
		int ch;
		cin>>ch;
		return ch;
	}	
	
	void prog()
	{
		MemoryFit  duplicate;
		int ch=0;
		nProcess=nMemory=0;
		while(true)
		{
			ch=menu();
			if(ch!=1&&nProcess==0)
			{
				cout<<"No Data Provided, Enter Data to Proceed\n";
				ch=1;
			}
			if(nProcess!=0)
				*this=duplicate;
			switch(ch)
			{
				case 1: input();
						duplicate=*this;
				break;
				case 2: display();
				break;
				case 3: firstFit();
				break;
				case 4: Best_WorstFit(0);
				break;
				case 5: Best_WorstFit(1);
				break;
				case 6: exit(0);
				break;
				default:cout<<"Wrong choice\n"; 
						exit(0);
			}
			if(ch!=1&&ch!=2)
			display();	
		}		
	}
};

int main()
{
	MemoryFit m;
	m.prog();
	
	retrun 0;
}

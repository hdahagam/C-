#include<thread>
#include<iostream>
#include<mutex>
#include<stdlib.h>
#include <condition_variable>
std::mutex mutx;
std::condition_variable cond_var1;
std::condition_variable cond_var2;
using namespace std;

class Parts {
public:
	int A, B, C;
	Parts() {
		A=0;
		B=0;
		C= 0;
	};
	Parts(int a, int b, int c) {
		A = a;
		B = b;
		C = c;
	};

};
void PartWorker(int i);
void ProductWorker(int i);
void inBuffer(Parts& parts, int category, int high);
void outBuffer(Parts& parts, int category);
Parts buffer;

void PartWorker(int i)
{
	int set = 0;
	Parts possibilities[10] = { Parts(1,1,1), Parts(3,0,0) , Parts(0,0,3), Parts(0,3,0), Parts(1,2,0) ,
		Parts(1,0,2), Parts(2,0,1), Parts(2,1,0), Parts(0,1,2) , Parts(0,2,1) };
	srand(set);
	set++;
	while (true)
	{
		Parts parts = possibilities[rand() % 10];
		std::unique_lock<std::mutex> lock(mutx);
		do
		{
			cout << "PartWorker ID:" << i << "\n";
			cout << "Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << ")\n";
			cout << "Place Request: (" << parts.A << "," << parts.B << "," << parts.C << ")\n";
			inBuffer(parts, 0, 6);
			inBuffer(parts, 1, 5);
			inBuffer(parts, 2, 4);
			cout << "Updated Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << ")\n";
			cout << "Updated Place Request: (" << parts.A << "," << parts.B << "," << parts.C << ")\n\n";
			if (parts.A != 0) {
				while (buffer.A == 6) {
					cond_var1.wait(lock);
				}
				cond_var2.notify_one();
				continue;
			}
			if (parts.B != 0) {
				while (buffer.B == 5) {
					cond_var1.wait(lock);
				}
				cond_var2.notify_one();
				continue;
			}
			if (parts.C != 0) {
				while (buffer.C == 4) {
					cond_var1.wait(lock);
				}
				cond_var2.notify_one();
				continue;
			}
			if (parts.A == 0 && parts.B == 0 && parts.C == 0) {
				cond_var2.notify_one();
				break;
			}
		} while (buffer.A < 6 || buffer.B < 5 || buffer.C < 4);

	}
}

void ProductWorker(int i)
{
	int set = 0;
	Parts possibilities[9] = { Parts(1,3,0) , Parts(1,0,3) ,
		Parts(3,1,0) , Parts(3,0,1), Parts(0,1,3), Parts(0,3,1), Parts(2,2,0),
		Parts(2,0,2), Parts(0,2,2) };
	srand(set);
	set++;
	possibilities[rand() % 9];
	while (true)
	{
		Parts parts = possibilities[rand() % 9];
		std::unique_lock<std::mutex> lock(mutx);
		do
		{
			cout << "ProductWorker ID:" << i << "\n";
			cout << "Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << ")\n";
			cout << "PickUp Request: (" << parts.A << "," << parts.B << "," << parts.C << ")\n";
			outBuffer(parts, 0);
			outBuffer(parts, 1);
			outBuffer(parts, 2);
			cout << "Updated Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << ")\n";
			cout << "Updated PickUp Request: (" << parts.A << "," << parts.B << "," << parts.C << ")\n\n";
			if (parts.A != 0) {
				while (buffer.A == 0) {
					cond_var2.wait(lock);
				}
				cond_var1.notify_one();
				continue;
			}
			if (parts.B != 0) {
				while (buffer.B == 0) {
					cond_var2.wait(lock);
				}
				cond_var1.notify_one();
				continue;
			}
			if (parts.C != 0) {
				while (buffer.C == 0) {
					cond_var2.wait(lock);
				}
				cond_var1.notify_one();
				continue;
			}
			if (parts.A == 0 && parts.B == 0 && parts.C == 0) {
				cond_var1.notify_one();
				break;
			}
		} while (buffer.A > 0 || buffer.B > 0 || buffer.C > 0);
	}
}


void inBuffer(Parts & parts, int category, int high)
{
	int latest;
	int latestBuffer;
	if (category == 0) {
		latest = parts.A;
		latestBuffer = buffer.A;
	}
	else if (category == 1) {
	latest = parts.B;
	latestBuffer = buffer.B;
	}
	else {
		latest = parts.C;
		latestBuffer = buffer.C;
	}
	if (latest + latestBuffer <= high) {
		latestBuffer += latest;
		latest = 0;
	}
	else {
		int tmp = latestBuffer;
		latestBuffer = high;
		latest -= (high - tmp);
	}
	if (category == 0) {
		parts.A = latest;
		buffer.A = latestBuffer;
	}
	else if (category == 1) {
		parts.B = latest;
		buffer.B = latestBuffer;
	}else{
		parts.C = latest;
		buffer.C = latestBuffer;
	}
}

void outBuffer(Parts & parts, int category)
{
	int latest;
	int latestBuffer;
	if (category == 0) {
		latest = parts.A;
		latestBuffer = buffer.A;
	}
	else if (category == 1) {
		latest = parts.B;
		latestBuffer = buffer.B;
	} 
	else {
		latest = parts.C;
		latestBuffer = buffer.C;
	}
	if (latestBuffer - latest >= 0) {
		latestBuffer -= latest;
		latest = 0;
	}
	else {
		latest -= latestBuffer;
		latestBuffer = 0;
	}
		if (category == 0) {
			parts.A = latest;
			buffer.A = latestBuffer;
		}
		else if(category == 1) {
			parts.B = latest;
			buffer.B = latestBuffer;
		}
		else if (category == 2) {
			parts.C = latest;
		buffer.C = latestBuffer;
	}
}

int main() {
	thread partW[10];
	thread prodW[7];
	for (int i = 0; i < 7; i++) {
		partW[i] = thread(PartWorker, i);
		prodW[i] = thread(ProductWorker, i);
	}
	for (int i = 7; i<10; i++) {
		partW[i] = thread(PartWorker, i);
	}
	/* Join the threads to the main threads */
	for (int i = 0; i < 7; i++) {
		partW[i].join();
		prodW[i].join();
	}
	for (int i = 7; i<10; i++) {
		partW[i].join();
	}
	cout << "Finish!" << endl;
	return 0;
}

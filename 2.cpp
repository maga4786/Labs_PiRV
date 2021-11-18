#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::mutex locker;

int a = 10000;
int b = 0;

int allPicks = 0;
int picks[] = { 0, 0, 0 };

void threadA() {
	while (true) {
		int count = rand() % 101;
		locker.lock();
		if (count > a) count = a;
		if (a > 0) {
			a -= count;
			b += count;
			locker.unlock();
		}
		else {
			break;
		}
	}
	locker.unlock();
}

void threadB(int num) {
	while (true) {
		locker.lock();
		if (b > 0) {
			b--;
			allPicks++;
			picks[num]++;
			locker.unlock();
		}
		else {
			break;
		}
	}
	locker.unlock();
}

int main() {
	thread A1 = thread(threadA);
	thread A2 = thread(threadA);
	thread B1 = thread(threadB, 0);
	thread B2 = thread(threadB, 1);
	thread B3 = thread(threadB, 2);

	A1.join(); A2.join();
	B1.join(); B2.join(); B3.join();

	cout << picks[0] << '\n';
	cout << picks[1] << '\n';
	cout << picks[2] << '\n';
	cout << '\n';
	cout << allPicks << '\n';
}
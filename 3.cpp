#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
using namespace chrono;

const int phils = 10;
const milliseconds tThink = 100ms;
const milliseconds tEat = 50ms;
const milliseconds allTime = 10000ms;

milliseconds allTimeDuration = 0ms;
milliseconds* eatTimes = new milliseconds[phils];
mutex* forks = new mutex[phils];

void think(int number) {
	this_thread::sleep_for(tThink);
}

void eat(int number) {
	int left = number;
	int right = (number + 1) % phils;

	if (forks[left].try_lock())
	{
		if (forks[right].try_lock())
		{
			this_thread::sleep_for(tEat);
			eatTimes[number] += tEat;
			allTimeDuration += tEat;
			forks[right].unlock();
		}
		else
		{
			think(number);
		}
		forks[left].unlock();
	}
	else
	{
		think(number);
	}
}

void philos(int number) {
	while (1) {
		bool isEat = rand() % 2;
		if (isEat) {
			eat(number);
		}
		else {
			think(number);
		}
	}
}

int main() {
	for (int i = 0; i < phils; i++) eatTimes[i] = 0ms;

	thread* philosofers = new thread[phils];
	for (int i = 0; i < phils; i++) {
		philosofers[i] = thread(philos, i);
	}
	
	this_thread::sleep_for(allTime);

	for (int i = 0; i < phils; i++) {
		philosofers[i].detach();
	}

	for (int i = 0; i < phils; i++) {
		cout << eatTimes[i].count() / (double)allTimeDuration.count() << '\n';
	}
}
#include <iostream>
#include <cstdlib>

#include "time.h"
#include <thread>
#include <vector>

void genMatrix (int **arr, int size)
{

for (int i = 0; i < size; i++)
{
arr[i] = new int[size];

for (int j = 0; j < size; j++)
{
arr[i][j] = rand() % 1000;

}
}
}

void printMatrix(int** arr, int size)
{

for (int i = 0; i < size; i++)
{
for (int j = 0; j < size; j++)

{
std::cout << arr[i][j] << " ";
}

std::cout << "\n";
}
}

int main()
{

int n;
setlocale(LC_ALL, "Russian");

std::cout << "Введите количество строк/столбцов: "; std::cin >> n;

int** A, ** B, ** C;

A = new int* [n];
B = new int* [n];
C = new int* [n];

genMatrix(A, n);
genMatrix(B, n);

for (int i = 0; i < n; i++) {
C[i] = new int[n];
}

unsigned int hc = std::thread::hardware_concurrency(); std::cout << hc << " - количество доступных потоков.\n";

double countThread;
std::cout << "Введите количество используемых потоков: ";

std::cin >> countThread;

int step = ceil(n / countThread);
int startPosition;

int endPosition = 0;

std::vector <std::thread> multipliers;

multipliers.resize(countThread);

for (int currentThread = 0; currentThread < countThread; currentThread++)

{
startPosition = endPosition;
endPosition += step;

if (endPosition > n) endPosition = n;

multipliers[currentThread] = std::thread([](int** A, int** B, int** C, int startPosition, int endPosition, int size)
{
for (int i = startPosition; i < endPosition; i++)

{
for (int j = 0; j < size; j++)
{

C[i][j] = 0;
for (int k = 0; k < size; k++)
{

C[i][j] += A[i][k] * B[k][j];
}
}

}
}, A, B, std::ref(C), startPosition, endPosition, n);
};

clock_t time = clock();
for (int currentThread = 0; currentThread < countThread; currentThread++)

{
multipliers[currentThread].join();
}

time = clock() - time;
std::cout << "Время вычисления: " << time << "\n";

}
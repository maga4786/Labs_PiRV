#include <iostream>
#include <cstdlib>

#include <omp.h>

void genMatrix(int** arr, int size)
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

unsigned int hc = omp_get_num_procs();
std::cout << hc << " - количество доступных потоков.\n";

double countThread;

std::cout << "Введите количество используемых потоков: ";
std::cin >> countThread;

omp_set_num_threads(countThread);

#pragma omp parallel

#pragma omp master

{
std::cout << "\nПотоков: " << omp_get_num_threads();

}

double time_start = omp_get_wtime();

#pragma omp parallel for

for (int i = 0; i < n; i++)

{
for (int j = 0; j < n; j++)

{

C[i][j] = 0;
for (int k = 0; k < n; k++)

{

C[i][j] += A[i][k] * B[k][j];
}

}

}

std::cout << "\nВремя вычисления: " << omp_get_wtime() - time_start << "\n";

}
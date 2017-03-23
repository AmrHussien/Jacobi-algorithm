#include <omp.h>
#include <iostream>
#include<cmath>
#include<time.h>
using namespace std;
#define RHS 10
#define Array_Size 10
#define EPSILON 0.0000001
#define MAX_PRINT_ITERS 333
void Serial_JacobiAlgorithm()
{
	int k, n;
	float x[Array_Size], M[Array_Size][Array_Size], rhs[Array_Size], sum[Array_Size];

	
	printf("Enter matrix size : ");
	cin >> n;
	
	printf("Enter matrix (row by row) : \n");
	for (int i = 0; i<n; i++) {
		x[i] = 0;
		for (int j = 0; j<n; j++) {
			cin >> M[i][j];
		}
	}

	printf("Enter right hand side : \n");
	for (int i = 0; i<n; i++) {
		cin >> rhs[i];
	}
	 
	k = 1;
	while (k <= MAX_PRINT_ITERS && k>EPSILON)
	{
		for (int i = 0; i < n; i++) {
			sum[i] = rhs[i];
			for (int j = 0; j < n; j++) {
				if (i != j) {
					sum[i] = sum[i] - M[i][j] * x[j];
				}
			}
		}
		for (int i = 0; i < n; i++) {
			x[i] = sum[i] / M[i][i];
		}
		k++;
	}
	 
	 
	printf("Solution : \n");
	
	for (int i = 0; i < n; i++) {
		printf("X[%d] = %f\n", i,x[i]);
	}
		
	
}
void Parallel_JacobiAlgorithm()
{ 

	int nthreads, tid, i,j, n,N, k;
	float x[Array_Size], M[Array_Size][Array_Size], rhs[Array_Size], sum[Array_Size];
	printf("Enter matrix size : ");
	cin >> n;
	N = n;
	printf("Enter matrix (row by row) : \n");
	for (i = 0; i<n; i++) {
		x[i] = 0;
		for (j = 0; j<n; j++) {
			cin >> M[i][j];
		}
	}
	printf("Enter right hand side : \n");
	for (i = 0; i<n; i++) {
		cin >> rhs[i];
	}
	printf("Enter number of threads : ");
	cin >> nthreads;
	omp_set_num_threads(nthreads);

#pragma omp parallel  private(i,j)	
	{
		k = 1;
		while (k <= MAX_PRINT_ITERS && k > EPSILON)
		{

#pragma  for collapse(2) 
			for (i = 0; i < n; i++) {
				sum[i] = rhs[i];
				for (j = 0; j < n; j++) {
					if (i != j) {
						sum[i] = sum[i] - M[i][j] * x[j];
					}
				}
			}
#pragma omp parallel for  
			for (i = 0; i < n; i++) {
				x[i] = sum[i] / M[i][i];
			}
 
			k++;
		}
	}
	printf("Solution : \n");
	for (int m = 0; m <N; m++) {
		printf("X[%d] = %f\n", m, x[m]);
	}
}		
/*
Note :
The output & time are varies with every run
*/
int main()
{
	int method_number ;
	
 
		printf("Enter the execution method (0-Serial, 1-Parallel) : ");
		cin >> method_number;
		if (method_number == 0)
		{
			
			const clock_t begin_time = clock();
		Serial_JacobiAlgorithm();
			float time = float(clock() - begin_time) / CLOCKS_PER_SEC;
			cout << "\nTime : " << time << endl;
		}
		else if (method_number == 1)
		{
			const clock_t begin_time = clock();
			Parallel_JacobiAlgorithm();
			float time = float(clock() - begin_time) / CLOCKS_PER_SEC;
			cout << "\nTime : " << time<< endl;
		}
	 
}
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
long long comparisons=0;
long long swaps=0;

int Partition(int A[], int p, int r) {
	int x = A[p];
	int i = p;
	int j = r;
	while(1) {
		while(A[i]>x){
		    comparisons++;
		    i++;
		}
		while(A[j]<x){
		    comparisons++;
		    j--;
		}
		if(i<j) {
			int temp = A[i];
			A[i] = A[j];
			A[j] = temp;
			swaps++;
			i++;
			j--;
		} else return j;
	}
}

void QsortIterative(int A[], int p, int r) {
	int *stack=malloc(sizeof(int)*(r-p+1));
	int top = -1;
	stack[++top] = p;
	stack[++top] = r;
	while(top>=0) {
		r = stack[top--];
		p = stack[top--];
		int q = Partition(A, p, r);
		if(q>p) {
			stack[++top]=p;
			stack[++top]=q;
		}
		if(q+1<r) {
			stack[++top]=q+1;
			stack[++top]=r;
		}
	}
	free(stack);
}

int main()
{
    int n;
    scanf("%d", &n);
    int *arr=malloc(sizeof(int)*n);
	for(int i=0; i<n; i++){
	    scanf("%d", &arr[i]);
	}
    // 1. Get the frequency of the high-res timer (ticks per second)
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 2. Capture the start tick
	LARGE_INTEGER start;
	QueryPerformanceCounter(&start);

	// --- YOUR CODE TO MEASURE ---
	QsortIterative(arr, 0, n - 1);
	// ----------------------------

	// 3. Capture the end tick
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);

	// 4. Calculate elapsed time in seconds
	double elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	
    printf("Posortowana tablica:\n");
	for(int i=0; i<n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
    printf("Liczba porównań: %lld \n",comparisons);
    printf("Liczba zamian: %lld\n",swaps);
    printf("Czas: %.10f\n", elapsed);
	free(arr);
	return 0;
}

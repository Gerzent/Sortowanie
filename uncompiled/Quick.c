#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
long long comparisons=0;
long long swaps=0;

int Partition(int A[], int p, int r){
    int x = A[p];
    int i = p;
    int j = r;
    while(1){
        while(A[i]>x){
		    comparisons++;
		    i++;
		}
        while(A[j]<x){
		    comparisons++;
		    j--;
		}
        if(i<j){
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
			swaps++;
            i++; j--;
        } else return j;
    }
}

void Qsort(int A[], int p, int r){
    if(p<r){
        int q = Partition(A, p, r);
        Qsort(A, p, q);
        Qsort(A, q+1, r);
    }
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
    Qsort(arr, 0, n-1);
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
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
long long comparisons=0;
long long swaps=0;
void Shell(int arr[], int n) {
    int przyrost=1,kMax=1;
    while (przyrost<n) {
        przyrost=(pow(3,kMax)-1)/2;
        kMax++;
    }
    if (przyrost>=n) {
        przyrost=(pow(3,kMax--)-1)/2;
    }//uzyskiwanie maksymalnego dla nas przyrostu
    while (przyrost>0) {

        for (int i=przyrost;i<n;i++) {
            int key=arr[i];
            int j=i;

            while (j >= przyrost) {
                comparisons++;
                if (arr[j - przyrost]<key) {
                    swaps++;
                    arr[j]=arr[j-przyrost];
                    j-=przyrost;
                }else {
                    break;
                }
            }
            swaps++;
            arr[j]=key;

        }
        przyrost=(pow(3,kMax--)-1)/2;

    }
    }

int main() {
    int n=10;
    scanf("%d", &n);
    int *arr=malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    // 1. Get the frequency of the high-res timer (ticks per second)
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 2. Capture the start tick
	LARGE_INTEGER start;
	QueryPerformanceCounter(&start);

	// --- YOUR CODE TO MEASURE ---
    Shell(arr, n);
	// ----------------------------

	// 3. Capture the end tick
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);

	// 4. Calculate elapsed time in seconds
	double elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    
    printf("Posortowana tablica:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Liczba prównań: %lld \n",comparisons);
    printf("Liczba zamian: %lld \n",swaps);
    printf("Czas: %.10f\n", elapsed);
    free(arr);
    return 0;
}

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
long long comparisons=0;
long long swaps=0;
void restoreHeap(int arr[], int length,int initialRoot) {
    int indexOfSmallest=initialRoot;
    int left=2*indexOfSmallest+1;
    int right=2*indexOfSmallest+2;
    if (left<length ) {
        comparisons++;
        if (arr[left] < arr[indexOfSmallest]) {
            indexOfSmallest = left;
        }
    }
    if (right<length) {
        comparisons++;
        if (arr[right] < arr[indexOfSmallest]) {
            indexOfSmallest = right;
        }
    }//szukanie najmniejszego
    if (indexOfSmallest !=initialRoot) {
        swaps++;
        int tmp = arr[initialRoot];
        arr[initialRoot] = arr[indexOfSmallest];
        arr[indexOfSmallest] = tmp;// jak był jakiś mniejszy to podmieniamy
        restoreHeap(arr, length, indexOfSmallest);//rekurencyjne wywoływanie
    }
}
void buildHeap(int arr[], int length) {
    for (int i=length/2-1;i>=0;i--) {
        restoreHeap(arr, length, i);//dla każdego nie korzenia naprawamy stos
    }
}
void heapSort(int arr[], int length) {
    for (int i = length - 1; i > 0; i--) {//i robi za ostatni index nieprzesortowanej czesci i za to żeby wywołało się n razy
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        swaps++;
        restoreHeap(arr, i, 0);
    }

}

int main() {
    int n;
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
    buildHeap(arr, n);
    heapSort(arr,n);
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
    printf("Liczba zamian: %lld\n",swaps);
    printf("Czas: %.10f\n", elapsed);
    free(arr);
    return 0;
}
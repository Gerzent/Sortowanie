#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
long long comparisons=0;
void merge(int arr[],int leftIndex,int midlle,int rightIndex) {
    int i=0,j=0,k=leftIndex;

    int lenghtOfLeft= midlle - leftIndex + 1;
    int lenghtOfRight= rightIndex - midlle;

    int *LeftSubArray=malloc(sizeof(int) * lenghtOfLeft);
    int *RightSubArray=malloc(sizeof(int) * lenghtOfRight);

    for (i=0;i<lenghtOfLeft;i++) {
        LeftSubArray[i]=arr[leftIndex+i];
    }

    for (j=0;j<lenghtOfRight;j++) {
        RightSubArray[j]=arr[midlle+j+1];
    }
    i = 0;
    j = 0;//wypełnianie subarrays

    while (i < lenghtOfLeft && j < lenghtOfRight) {
        comparisons++;
        if (LeftSubArray[i] > RightSubArray[j]) {
            arr[k++] = LeftSubArray[i++];
        } else {
            arr[k++] = RightSubArray[j++];
        }
    }

    while (i < lenghtOfLeft) {
        arr[k++] = LeftSubArray[i++];
    }

    while (j < lenghtOfRight) {
        arr[k++] = RightSubArray[j++];
    }

    free(LeftSubArray);
    free(RightSubArray);

}

void mergeSort(int arr[], int leftIndex,int rightIndex){
    if (leftIndex < rightIndex) {
        int midlle=leftIndex+(rightIndex-leftIndex)/2;
        mergeSort(arr,leftIndex,midlle);
        mergeSort(arr,midlle+1,rightIndex);
        merge(arr,leftIndex,midlle,rightIndex);

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
    mergeSort(arr,0,n-1);
	// ----------------------------

	// 3. Capture the end tick
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);

	// 4. Calculate elapsed time in seconds
	double elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Posortowana tablica:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    printf("Liczba prównań: %lld \n",comparisons);
    printf("Czas: %.10f\n", elapsed);
    free(arr);
    return 0;

}
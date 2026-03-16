#include <stdio.h>
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
	int arr[n];
	for(int i=0; i<n; i++){
	    scanf("%d", &arr[i]);
	}
    Qsort(arr, 0, n-1);
    printf("Posortowana tablica:\n");
	for(int i=0; i<n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
    printf("Liczba porównań: %lld \n",comparisons);
    printf("Liczba zamian: %lld",swaps);
    return 0;
}